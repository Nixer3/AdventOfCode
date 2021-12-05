#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <math.h>
using namespace std;
enum OPT {A, B};
#define MYOPT B
vector<string> split(const string& s, char sep) {
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;
    while (i != s.size()) {
        while (i != s.size() && s[i] == sep)
            ++i;
        string_size j = i;
        while (j != s.size() && s[j] != sep)
            j++;
        if (i != j) {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}
vector<int> range(int start, int end, int step) {
    vector<int> out;
    if (start < end) {
        for (; start <= end; start += step)
            out.push_back(start);
    }
    else {
        for (; start >= end; start -= step)
            out.push_back(start);
    }
    return out;
}
//must call delete2d
int** allocate2d(int w, int h) {
    int** a = new int* [h];
    for (int i = 0; i < h; ++i)
        a[i] = new int[w];
    return a;
}
void delete2d(int** arr, int h) {
    for (int i = 0; i < h; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

class Point {
public:
    int x;
    int y;
    Point() {};
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    };
};

class Line {
public:
    Point start;
    Point end;
    Line(Point start, Point end) {
        this->start = start;
        this->end = end;
    }
    bool isStraight() const {
        return start.x == end.x ||
            start.y == end.y;
    }
};

class Plain {
public:
    int **plain;
    int width, height;

    Plain(int **p, int w, int h) {
        width = w;
        height = h;
        plain = p;
    }
    void fillPlain(int what) {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                plain[i][j] = what;
    }
    void drawLine(const Line &line){
        if (!line.isStraight()) {
            drawLineBresenhaam(line);
            return;
        }
        if(line.start.x != line.end.x)
            for(int x : range(line.start.x, line.end.x,1)) //if same not gonna happen
                plain[line.start.y][x]++;
        if(line.start.y != line.end.y)
            for (int y : range(line.start.y, line.end.y, 1))
                plain[y][line.start.x]++;

    }
    //code from chad Avi https://stackoverflow.com/a/16405254
    //find this is also an acomplishment
    void drawLineBresenhaam(const Line &line){
        int x1 = line.start.x;
        int y1 = line.start.y;
        int x2 = line.end.x;
        int y2 = line.end.y;

        int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
        dx = x2 - x1;
        dy = y2 - y1;
        dx1 = fabs(dx);
        dy1 = fabs(dy);
        px = 2 * dy1 - dx1;
        py = 2 * dx1 - dy1;
        if (dy1 <= dx1){
            if (dx >= 0){
                x = x1;
                y = y1;
                xe = x2;
            } else {
                x = x2;
                y = y2;
                xe = x1;
            }
            plain[y][x]++;
            for (i = 0; x < xe; i++){
                x = x + 1;
                if (px < 0){
                    px = px + 2 * dy1;
                } else {
                    if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                        y = y + 1;
                    else
                        y = y - 1;
                    px = px + 2 * (dy1 - dx1);
                }
                plain[y][x]++;
            }
        } else {
            if (dy >= 0) {
                x = x1;
                y = y1;
                ye = y2;
            } else {
                x = x2;
                y = y2;
                ye = y1;
            }
            plain[y][x]++;
            for (i = 0; y < ye; i++){
                y = y + 1;
                if (py <= 0)
                    py = py + 2 * dx1;
                else {
                    if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                        x = x + 1;
                    else
                        x = x - 1;
                    py = py + 2 * (dx1 - dy1);
                }
                plain[y][x]++;
            }
        }
    }
    void printPlain() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << setw(2) << (plain[i][j] != 0 ? to_string(plain[i][j]) : ".");
            }
            cout << endl;
        }
    }

    //counts numbers in plain, plain[i][j] >= min
    int getDangerous(int min) {
        int count = 0;;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (plain[i][j] >= min)
                    count++;
        return count;
    }       
};


int main() {
    
    string in;
    ifstream infile("inputs.txt");
    vector<Line> lines;
    //parsing file
    while (getline(infile, in)) {
        in.replace(in.find("->"),2, ","); // '1,2 -> 2,3'  => 1,2,2,3
        auto points = split(in, ',');
        Point start(stoi(points[0], 0, 10), stoi(points[1], 0, 10)); // Point(1,2)
        Point   end(stoi(points[2], 0, 10), stoi(points[3], 0, 10)); // Point(2,3)
        lines.push_back(Line(start, end)); 
    }
    //find max coordinates
    int width = 0;
    for (auto& l : lines) {
        if (width < max(l.start.x, l.end.x))
            width = max(l.start.x, l.end.x);
    }
    int height = 0;
    for (auto& l : lines) {
        if (height < max(l.start.y, l.end.y))
            height = max(l.start.y, l.end.y);
    }
    width  += 1;
    height += 1;

    int** p = allocate2d(width, height);
    Plain plain(p, width, height);
    plain.fillPlain(0);
    for (const Line &l : lines) {
        if (!l.isStraight() && MYOPT == A)
            continue;
        plain.drawLine(l); 
        
    }
    cout << plain.getDangerous(2) << endl;

    delete2d(p, height);

    return 0;
}


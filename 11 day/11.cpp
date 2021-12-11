#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <queue>
using namespace std;

enum COLOR { RESET, BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
const char* COLORS[] = {
 "\033[0m" ,      /* Reset*/
 "\033[30m",      /* Black */
 "\033[31m",      /* Red */
 "\033[32m",      /* Green */
 "\033[33m",      /* Yellow */
 "\033[34m",      /* Blue */
 "\033[35m",      /* Magenta */
 "\033[36m",      /* Cyan */
 "\033[37m"      /* White */
};
//C == for both
#define OPT_A 1 
#define OPT_B 2
#define OPT (OPT_A | OPT_B)
#define STEPS 100
#define SYNC_LIMIT 1000


class Point {
public: int y; int x; char c; bool light = false;
      string color = COLORS[CYAN];
      Point() {};
      Point(int x, int y, char c) : x{ x }, y{ y }, c{ c } {};
      bool operator<(const Point& a) const { return c < a.c; }
      bool operator<(int a) const { return c < a; }
      bool operator>(const Point& a) const { return c > a.c; }
      bool operator>(int a) const { return c > a; }
      bool operator>=(const Point& a) const { return c >= a.c; }
      bool operator>=(int a) const { return c >= a; }
      int operator+(const Point& a) const { return c - '0' + a.c - '0'; }
      int operator+(int a) const { return c - '0' + a; }
      int operator-(const Point& a) const { return c - '0' - a.c - '0'; }
      int operator-(int a) const { return c - '0' - a; }
      char inc() {        return ++c; }
      char operator++() { return c++; }


      friend ostream& operator<<(ostream& os, const Point& t);
};
ostream& operator<<(ostream& os, const Point& t) {
    if (t.c > '9')
        os << COLORS[RED] << t.c << COLORS[RESET];
    else if(t.c == '9')
        os << COLORS[CYAN] << t.c << COLORS[RESET];
    else if (t.c == '0')
        os << COLORS[BLUE] << t.c << COLORS[RESET];
    else
        os << string() + COLORS[RESET] + t.c + COLORS[RESET];
    return os;
}
//try to get as many neightbours as possible, clockwise
vector<Point*> getAdj(vector<vector<Point*>> &land, Point *p) {
    vector<Point*> out;
    try { out.push_back(land.at(p->y - 1).at(p->x)); }     catch (...) {};
    try { out.push_back(land.at(p->y - 1).at(p->x + 1)); } catch (...) {};
    try { out.push_back(land.at(p->y)    .at(p->x + 1)); } catch (...) {};
    try { out.push_back(land.at(p->y + 1).at(p->x + 1)); } catch (...) {};
    try { out.push_back(land.at(p->y + 1).at(p->x)); }     catch (...) {};
    try { out.push_back(land.at(p->y + 1).at(p->x - 1)); } catch (...) {};
    try { out.push_back(land.at(p->y)    .at(p->x - 1)); } catch (...) {};
    try { out.push_back(land.at(p->y - 1).at(p->x - 1)); } catch (...) {};
    return out;
}
//
template<typename T>
void print2dVec(const vector<vector<T*>>& vec, int gen) {
    int tmp = gen;
    string offs;
    int off = 0;
    if (gen >= 0) {//count digit in gen
        do { 
            ++off;
            tmp /= 10;
        } while (tmp);
        offs  = string(' ', (size_t)gen);
        cout << gen << " ";
    }
    cout<< COLORS[MAGENTA] << ' ';
    for (int i = 0; i < vec.size(); i++)
        cout << i;
    cout << COLORS[RESET] << endl;
    for (int i = 0; i < vec.size(); i++) {
        cout << offs<<COLORS[MAGENTA] << i << " " << COLORS[RESET];
        for (int j = 0; j < vec[i].size(); j++)
            cout << *vec[i][j];
        cout << endl;
    }
}

void incAdj(vector<vector<Point*>> &land, Point *p) {
    system("CLS");
    print2dVec(land,-1);
    for (Point *adjp : getAdj(land,p)) {
        if (!adjp->light && adjp->inc() > '9' ) {
            adjp->light = true;
            incAdj(land, adjp);
        }
    }
    
}
unsigned int step(vector<vector<Point*>>& land) {
    unsigned int flashes = 0;
    for (auto& l : land) //increment
        for (auto p : l)
            (*p).inc();
    vector<Point*> over9;
    for (auto& l : land) { // get if lighing
        for (auto& p : l) {
            if ((*p) > '9')
                over9.push_back(p);
        }
    }
    for (auto& p : over9) {
        if (p->light)
            continue;
        p->light = true;
        incAdj(land, p);
    }
    for (auto& l : land) {
        for (auto& p : l) {
            if (*p > '9') {
                p->c = '0';
                p->light = false;
                flashes++;
            }
        }
    }
    return flashes;
}
int main() {
    ifstream infile("inputs");
    string in;
    vector<vector<Point*>> land;
    int y = 0;
    while (getline(infile, in)) {
        vector<Point*> l;
        int x = 0;
        for (char& c : in)
            l.push_back(new Point(x++, y, c));
        land.push_back(l);
        y++;
    }
    infile.close();
    print2dVec(land,-1);
    cout << endl << endl;

    if (OPT & OPT_A) {
        cout << "OPT_A" << endl;
        unsigned int total = 0;
        for (int i = 1; i <= STEPS;i++) {
            total += step(land);
        }
        cout << "total flashes" << total << endl;
    }

    if (OPT & OPT_B) {
        unsigned int total = 0;
        for (int i = 1; i < SYNC_LIMIT; i++) {
            total += step(land);
            bool allnull = true;
            for (auto& a : land)
                for (auto* b : a)
                    if ((*b).c != '0')
                        allnull = false;
            if (allnull) {
                if (OPT & OPT_A) 
                    i += STEPS;
                cout << "synced at step: " << i <<endl;
                cout << "total flashes" << total << endl;
                goto end;
            }
        }
        cout << "SYNC_LIMIT"<<SYNC_LIMIT<<" reached";
    }
end: 
    for (auto v : land)
        for (Point* p : v)
            delete p;

    return 0;
}
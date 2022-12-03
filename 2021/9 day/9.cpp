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

enum COLOR {RESET, BLACK,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE};
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

#define TOP 3
class Point {
public: int x; int y; char c;
      bool marked =false;
      string color = COLORS[CYAN];
      Point() {};
      Point(int x, int y, char c) : x{ x }, y{ y }, c{ c } {};
      Point(int x, int y, char c, bool marked) : x{ x }, y{ y }, c{ c }, marked{ marked } {};
      bool operator<(const Point& a) const{ return c < a.c;}
      bool operator<(int a) const { return c < a; }
      bool operator>(const Point& a) const { return c > a.c;} 
      bool operator>(int a) const { return c > a; }
      bool operator>=(const Point& a) const { return c >= a.c;}
      bool operator>=(int a) const { return c >= a; }
      int operator+(const Point& a) const { return c-'0' + a.c-'0';}
      int operator+(int a) const { return c - '0' + a;}
      int operator-(const Point& a) const { return c - '0' - a.c - '0'; }
      int operator-(int a) const { return c - '0' - a; }

      friend ostream& operator<<(ostream &os, const Point &t);
};

ostream &operator<<(ostream &os, const Point &t){
    if (t.marked)
        os << t.color + t.c + COLORS[RESET];
    else
        os << string() + COLORS[RESET] + t.c + COLORS[RESET];
    return os;
}
//try to get as many neightbours as possible
vector<Point> getAdj(vector<vector<Point>> &land, Point &p) {
    vector<Point> out;
    try { out.push_back(land.at(p.y - 1).at(p.x)); }
    catch (...) {};
    try {  out.push_back(land.at(p.y).at(p.x - 1)); }
    catch (...) {};
    try {  out.push_back(land.at(p.y + 1).at(p.x)); }
    catch (...) {};
    try {  out.push_back(land.at(p.y).at(p.x + 1)); }
    catch (...) {};
    return out;
}
//finding lowest point in land respective to neighbours
vector<Point> lowstAdjs(vector<vector<Point>> &land) {
    vector<Point> out;
    for (size_t i = 0; i < land.size(); i++) {
        for (size_t j = 0; j < land[i].size(); j++) {
            vector<Point> tocmp = getAdj(land, land[i][j]);
            unsigned int count = 0;
            for (Point c : tocmp) {
                if (land[i][j] < c)
                    count++;
            }
            if (count == tocmp.size()) {
                land[i][j].marked = true;
                out.push_back(land[i][j]);
            }
        }
    }
    return out;
}
//filter neighbours !marked && !9 && no bigger step up than 1
vector<Point> findAdjHigher(vector<vector<Point>> &land, Point& a) {
    vector<Point> tocmp = getAdj(land, a);
    tocmp.erase(remove_if(tocmp.begin(), tocmp.end(), [](const Point& t) {return t.marked; }), tocmp.end());
    tocmp.erase(remove_if(tocmp.begin(), tocmp.end(), [a](const Point& t) {return t.c =='9' || a >= t || a < t-2; }), tocmp.end());
    return tocmp;
}
//finding Adjacent points Hiher than &a
//if found fAHrec(,&b) and continues from it recurively
vector<Point> fAHrec(vector<vector<Point>> &land, Point &a) {
    auto look = findAdjHigher(land, a);
    if (look.size() == 0) {
        return look;
    }
    vector<Point> out;
    for (auto& p : look) {
        land[p.y][p.x].marked = true;
        out.push_back(land[p.y][p.x]);
        int count = 1;
        auto rec = fAHrec(land, land[p.y][p.x]);
        for (auto& t : rec)
            out.push_back(t);
    }
    return out;
}
template<typename T>
void print2dVec(const vector<vector<T>> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++)
            cout << vec[i][j];
        cout << endl;
    }
}

int main() {
    ifstream infile("inputs");
    string in;
    vector<vector<Point>> land;
    int y=0;
    while (getline(infile, in)) {
        vector<Point> l;
        int x = 0;
        for (char& c : in)
            l.push_back(Point(x++,y,c));
        land.push_back(l);
        y++;
    }
    infile.close();
    vector<Point> lowestPoints = lowstAdjs(land);
    print2dVec(land);
    cout << endl << endl;
    
    if(OPT & OPT_B){
        /*debug
        auto cmp = [](vector<Point> &a, vector<Point> &b) { return a.size() < b.size(); };
        priority_queue<vector<Point>,vector<vector<Point>>, decltype(cmp)> top(cmp);
        */
        priority_queue<int> top;
        for (auto &p : lowestPoints) {
            //cout << "looking from: " << p << endl;
            vector<Point> basinPoints = fAHrec(land, p);
            basinPoints.push_back(p);
            //print2dVec(land);
            //cout << endl << endl;
            top.push(basinPoints.size());//debug top.push(basinPoints);
        }
        print2dVec(land);
        unsigned int product = 1;
        for (int i = 0; i < TOP && !top.empty(); i++) {
        //    for (auto& p : top.top())  //debug tagging
        //        land[p.y][p.x].color = COLORS[RED];  // setting color
            product *= top.top();
            cout << top.top() << " * " ;
            top.pop();
        }
        cout <<"= product: " << product << endl;
        
        cout << endl;
    }
    if (OPT & OPT_A) {
        unsigned int sum = 0;
        for (auto& n : lowestPoints)
            sum += n + 1;
        cout << "lowest points count: "<< sum <<endl<< endl;
    }
    return 0;
}
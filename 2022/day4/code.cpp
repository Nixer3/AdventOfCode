#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>
#include <ctype.h>
#include <utility>

#include <vector>
#include <set>
#include <iterator>

using namespace std;

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

#define inRange(a,b,x) (x>=a&&x<=b)

int main(){
    ifstream infile("input");
    string in;
    int count=0;
    while (getline(infile, in)) {
        int a,b,c,d;
        auto s = split(in,',');
        auto p = split(s[0],'-');
        auto q = split(s[1],'-');
        a = stoi(p[0]);
        b = stoi(p[1]);
        c = stoi(q[0]);
        d = stoi(q[1]);
        // if(a<=c && b>=d || c<=a && d>=b) // A
        if(inRange(a,b,c) || inRange(a,b,d)  || inRange(c,d,a)  ||inRange(c,d,b) ) //B
            count++;
    }
    cout<<count<<endl;

    return 0;
}

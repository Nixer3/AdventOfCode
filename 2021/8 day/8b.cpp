#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
/**
*    t{Y} any combinationf of Y lit up segments
*    + - are set operations union/diff
*    0step:
*        t{2} => 1
*        t{3} => 7
*        t{4} => 4
*        t{7} => 8
*    1step:
*        t{5} - get(4) => if{7} => 2
*        t{5} - get(7) => if{2} => 3
*        t{6} - get(4) => if{2} => 9
*    2step:
*        t{6} - get(1) => if{4} - get(4) => if{3} => 0
*        t{5} - get(1) => if{4} - get(4) => if{2} => 5
*/
typedef set<char>(*detret) (vector<set<char>>& a);
set<char> det1(vector<set<char>>& a) { return *find_if(a.begin(), a.end(), [](set<char> t) {return t.size() == 2; }); }
set<char> det4(vector<set<char>>& a) { return *find_if(a.begin(), a.end(), [](set<char> t) {return t.size() == 4; }); }
set<char> det7(vector<set<char>>& a) { return *find_if(a.begin(), a.end(), [](set<char> t) {return t.size() == 3; }); }
set<char> det8(vector<set<char>>& a) { return *find_if(a.begin(), a.end(), [](set<char> t) {return t.size() == 7; }); }
set<char> det6(vector<set<char>>& a) {
    set<char> s7 = det7(a);
    set<char> diff;
    for (auto& t : a) {
        if (t.size() == 6) {
            diff.clear();
            set_union(s7.begin(), s7.end(), t.begin(), t.end(), inserter(diff, diff.end()));
            if (diff.size() == 7)
                return t; // its 7
        }
    }
    throw new exception("it's impossible 6");
}

set<char> det2(vector<set<char>>& a) {
    set<char> s4 = det4(a);
    for (auto& t : a) {
        if (t.size() == 5) {
            set<char> diff;
            set_union(s4.begin(), s4.end(), t.begin(), t.end(), inserter(diff, diff.end()));
            if (diff.size() == 7)
                return t; // its 2
        }
    }
    throw new exception("it's impossible 2");
}
set<char> det0(vector<set<char>>& a) {
    set<char> s1 = det1(a);
    set<char> s4 = det4(a);

    //Firs: original, Second: filtered
    vector<pair<set<char>, set<char>>> candidates;
    for (auto& t : a) {
        if (t.size() == 6) {
            set<char> diff;
            set_difference(t.begin(), t.end(), s1.begin(), s1.end(), inserter(diff, diff.end()));
            if (diff.size() == 4)
                candidates.push_back(pair<set<char>, set<char>>(t, diff)); // its 0
        }
    }

    //filtered to options
    for (auto& t : candidates) {
        set<char> diff;
        set_difference(t.second.begin(), t.second.end(), s4.begin(), s4.end(), inserter(diff, diff.end()));
        if (diff.size() == 3)
            return t.first;
    }
    throw new exception("it's impossible 0");
}
set<char> det3(vector<set<char>>& a) {
    set<char> s7 = det7(a);
    for (auto& t : a) {
        if (t.size() == 5) {
            set<char> diff;
            set_difference(t.begin(), t.end(), s7.begin(), s7.end(),  inserter(diff, diff.end()));
            if (diff.size() == 2)
                return t; // its 3
        }
    }
    throw new exception("it's impossible 3");
}
set<char> det5(vector<set<char>>& a) {
    set<char> s7 = det7(a);
    set<char> s4 = det4(a);
    set<char> s1 = det1(a);
    //Firs: original, Second filtered
    vector<pair<set<char>, set<char>>> candidates;
    for (auto& t : a) {
        if (t.size() == 5) {
            set<char> diff;
            set_difference(t.begin(), t.end(), s1.begin(), s1.end(),  inserter(diff, diff.end()));
            if (diff.size() == 4) {
                candidates.push_back(pair<set<char>, set<char>>(t, diff));
            }
        }
    }
    //filtered to options
    for (auto& t : candidates) {
        set<char> diff;
        set_difference(t.second.begin(), t.second.end(), s4.begin(), s4.end(),  inserter(diff, diff.end()));
        if (diff.size() == 2)
            return t.first;
    }
    throw new exception("it's impossible 5");
}
set<char> det9(vector<set<char>>& a) {
    set<char> s4 = det4(a);
    for (auto& t : a) {
        if (t.size() == 6) {
            set<char> diff;
            set_difference(t.begin(), t.end(), s4.begin(), s4.end(),  inserter(diff, diff.end()));
            if (diff.size() == 2)
                return t; // its 9
        }
    }
    throw new exception("it's impossible 9");
}

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
int main() {
    string in;
    ifstream infile("inputs");
    int counter = 0;
    detret det[] = { det0,det1,det2,det3,det4,det5,det6,det7,det8,det9 };

    uint64_t sum = 0;
    while (getline(infile, in)) {
        vector<string> tmp = split(in, '|');
        vector<string> lside = split(tmp[0], ' ');
        vector<string> rside = split(tmp[1], ' ');

        vector<set<char>> linputs; // 10 strings like: fdgacbe cefdb cefbgd gcbe
        for (auto& s : lside) {
            set<char> a;
            for (auto c : s) {
                a.insert(c);
            }
            linputs.push_back(a);
        }
        map<set<char>, int> m;
        for (int i = 0; i < 10; i++) {
            m.insert(pair<set<char>, int>(det[i](linputs), i));
        }
        uint64_t tmpsum = 0;
        for (int i = 0; i < 4; i++) {
            set<char> digit(rside[i].begin(), rside[i].end());
            int digIT = (*m.find(digit)).second;
            tmpsum += digIT * pow(10, 3 - i);
        }
        sum += tmpsum;
    }
    std::cout << sum << endl;
    infile.close();
    return 0;
}


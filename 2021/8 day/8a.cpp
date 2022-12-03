#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> split(const string & s, char sep) {
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
    ifstream infile("inputs_test");
    int counter = 0;
    while (getline(infile, in)) {
        vector<string> tmp = split(in, '|');
        vector<string> lside = split(tmp[0],' ');
        vector<string> rside = split(tmp[1], ' ');
        for (string rs : rside) {
            switch (rs.length()) {
            case 2:
            case 3:
            case 4:
            case 7: counter++;
            }
        }
        rside.clear();
        lside.clear();
    }
    cout << counter<<endl;
    infile.close();
    return 0;
}
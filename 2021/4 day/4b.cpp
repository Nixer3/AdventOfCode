#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <sstream>
using namespace std;


class Bnum {
public:
    int number = -1;
    bool marked = false;
    Bnum() {};
    Bnum(int num) {
        number = num;
    }
};

class Bsquare {
public:
    static const int size = 5;
    Bnum nums[size][size] = { -1 };
    int nunmarked = size * size;
    bool bingo = false;
    Bsquare(vector<vector<int>> matrix) {
        if (matrix.size() != size)
            throw new exception("riperino");

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                nums[i][j].number = matrix[i][j];
    }
    //marks num in square, if true if bingo occured
    bool mark(int num) {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (nums[i][j].number == num)
                    if (!nums[i][j].marked) //if new mark
                        nunmarked -= nums[i][j].marked = true; //count it
        return bingo = checkBingo();

    }
    //sums unmarked numbers
    int sumUnmarked() {
        int sum = 0;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (!nums[i][j].marked)
                    sum += nums[i][j].number;
        return sum;
    }
    bool checkBingo() {
        //rows
        for (int i = 0; i < size; i++) {
            int nmark = 0;
            for (int j = 0; j < size; j++) {
                if (nums[i][j].marked)
                    nmark++;
            }
            if (nmark == size) return bingo = true;
        }
        //columns
        for (int i = 0; i < size; i++) {
            int nmark = 0;
            for (int j = 0; j < size; j++) {
                if (nums[j][i].marked)
                    nmark++;
            }
            if (nmark == size) return bingo = true;
        }
        return bingo = false;
    }
};
vector<string> split(const string& s, char sep);

int main() {
    vector<int> row;
    vector<vector<int>> tmpSq;
    vector<Bsquare> table;
    vector<int> seq;
    string in;
    ifstream infile("inputs.txt");
    getline(infile, in);
    stringstream l1(in);

    for (auto a : split(in, ',')) {
        seq.push_back(stoi(a, 0, 10));
    }
    while (getline(infile, in)) {
        row.clear();
        if (in.size() > 2) {
            for (auto s : split(in, ' '))
                row.push_back(stoi(s, 0, 10)); //parse rows
            tmpSq.push_back(row);
        }
        else {          //parse last 5 rows comlumns as another rows
            table.push_back(tmpSq);
            tmpSq.clear();
        }
    }
    for (auto it = seq.begin(); it < seq.end(); it++) {
        for (auto& sq : table)
            sq.mark(*it);
        if (table.size() == 1) {
            if (table[0].bingo) {
                cout << "result: " << table[0].sumUnmarked() * *it << endl;
                return 0;
            }
        }
        else {
            table.erase(remove_if(table.begin(), table.end(), [](const Bsquare& x) {return x.bingo; }), table.end());
        }
    }
    return 0;
}
/*
int findMsq(vector<vector<Bnum>>& allcombs, int ignoreSq) {
    for (auto i = 0; i < allcombs.size(); i++) {
        if (i / 10 == ignoreSq) {
            i += 9;
            continue;
        }
        int nmark = 0;
        for (auto n : allcombs[i]) {
            if (n.marked) nmark++;
        }
        if (nmark == 5) return i / 10;
    }
    return -1;
}
int sumSquareUnmark(vector<vector<Bnum>>& allcombs, int sq) {
    auto start = allcombs.begin() + sq * 10;
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        for (auto n : *start) {
            if (!n.marked)
                sum += n.number;
        }
        start++;
    }
    return sum;
}*/

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
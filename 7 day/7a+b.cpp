#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

enum OPT {A,B};
#define OPTION B

int main() {
    string in;
    ifstream infile("inputs");
    vector<int> crabs;
    //parsing file
    while (getline(infile, in, ',')) {
        crabs.push_back(stoi(in, 0, 10));
    }
    infile.close();

    // set of pair<int,int> with comparing function of the pair.second
    auto cmp = [](pair<int, unsigned int> a, pair<int, unsigned int> b) { return a.second < b.second; };
    set<pair<int, unsigned int>, decltype(cmp)> rating(cmp);
    //alignment can be any int from a->b
    int lowerb = *min_element(crabs.begin(), crabs.end());
    int upperb = *max_element(crabs.begin(), crabs.end());
    //go through all possible good alignments
    for (int i = lowerb; i <= upperb; i++) {
        unsigned int diffsum = 0;
        for (int c : crabs) { //calculate (sum) rating
            int r = abs(i - c);
            if (OPTION == B)
                r = (r - 0 + 1)* (r + 0) / 2; // sum range 0->r
            diffsum += r;
        }
        rating.insert(pair<int, unsigned int>(i, diffsum));
    }
    cout << "best number is " << (*rating.begin()).first<<" with total cost of " << (*rating.begin()).second << endl;
    
    return 0;
}


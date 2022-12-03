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

template<class Stream, class Vector, class Begin = decltype(std::begin(std::declval<Vector>()))>
inline Stream& operator<<(Stream& stream, const Vector& vect) {
	const char* dlm = "";
	for(const auto& i : vect) { stream << dlm << i; dlm = ""; }
	return stream;
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

#define l2v(x) (islower(x) ? (x-'a'+1) : (x-'A'+27))    //letter to value

int A(ifstream& input){
    set<char> rucksack;
    int sum = 0;
    //parsing file
    string in;
    while (getline(input, in)) {
        int len = in.length();
        int half = len/2;
        set<char> rucksack(begin(in), begin(in)+half);
        for(int i=half; i<len; i++){
            auto it = rucksack.find(in[i]); // look for letter in first half
            if(it != rucksack.end()){ //found
                sum += l2v(in[i]);
                break;      // we suppose there is exactly one repeated item
            }
        }
    }
    return sum;
}


int B(ifstream& input){
    set<char> rucksack;
    int sum = 0;
    //parsing file
    string in;
    while (1) {
        string in;
        set<char> group[3]; //group of lines(elves)
        for(int i=0; i<3;i++){
            if(!getline(input,in))
                return sum;
            group[i] = set<char>(begin(in), end(in)); // line as set of chars
        }
        set<char> base(group[0]); //set first elf as base for reducing
        for(int i=1; i<3;i++){ //leave out the base
            set<char> intersect; //reduced by new line
            set_intersection(base.begin(), base.end(), 
                             group[i].begin(), group[i].end(),
                             inserter(intersect, intersect.begin()));
            base = intersect; //save the reduced set  ... after 3 iteration there shall be only one elem
        }
        sum+= l2v(*base.begin());
    }
    return sum;
}

int main(){
    
    ifstream infile("input");
    int sum = B(infile);
    cout<<"sum = "<<sum<<endl;
    infile.close();
}
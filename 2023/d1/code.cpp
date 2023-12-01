// streams
#include <iostream>
#include <fstream>
// algo
#include <algorithm>
#include <ctype.h>
// data structs
#include <iterator>
#include <string>
#include <set>
#include <map>

using std::cout,
    std::endl,
    std::ifstream,
    std::getline,
    std::string,
    std::unordered_map;
typedef unsigned char digit;

template <typename Iter>
char findDigit(Iter begin, Iter end, const unordered_map<string, char>& numberWords) {
    string temp;
    for (auto it = begin; it != end; ++it) {
        char ch = *it;
        if (isalpha(ch)) {
            temp += tolower(ch); // Append current alphabetic character
            // Check all possible ending substrings of temp
            for (size_t i = 0; i < temp.size(); ++i) {
                string subTemp = temp.substr(i);
                auto wordIt = numberWords.find(subTemp);
                if (wordIt != numberWords.end()) {
                    return wordIt->second; // Return corresponding digit for worded number
                }
            }
        } else {
            if (isdigit(ch)) {
                return ch; // Return numeric digit
            }
            temp.clear(); // Clear temp for next potential worded number
        }
    }

    return '\0'; // Return '\0' if no digit or worded number is found
}
const unordered_map<string, char> numberWords {
    {"zero", '0'}, {"one", '1'}, {"two", '2'}, {"three", '3'}, {"four", '4'},
    {"five", '5'}, {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'}
};
//more linear search
const unordered_map<string, char> rnumberWords {
    {"orez", '0'}, {"eno", '1'}, {"owt", '2'}, {"eerht", '3'}, {"ruof", '4'},
    {"evif", '5'}, {"xis", '6'}, {"neves", '7'}, {"thgie", '8'}, {"enin", '9'}
};

int main(){
    ifstream infile("input.txt");
    string in;
    int sum=0;
    
    while (getline(infile, in)) {
        string numbers;
        digit firstDigit = findDigit(in.begin(),  in.end(),  numberWords)  - '0';
        digit lastDigit  = findDigit(in.rbegin(), in.rend(), rnumberWords) - '0';
        sum += (firstDigit * 10) + (lastDigit * 1);
    }
    cout << sum << endl;

    return 0;
}



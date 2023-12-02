// streams
#include <iostream>
#include <fstream>
#include <sstream>
// algo
#include <algorithm>
#include <ctype.h>
// data structs
#include <iterator>
#include <string>
#include <vector>
#include <map>

using std::cout,
    std::endl,
    std::ifstream,
    std::getline,
    std::string,
    std::vector,
    std::istringstream,
    std::unordered_map;
typedef unsigned char digit;
#define COLOR_TEST(r,g,b) (r <= 12 && g <= 13 && b <= 14)

class ColorSet {
public:
    int red = 0;
    int green = 0;
    int blue = 0;

    ColorSet(const std::string& colorData) {
        std::istringstream stream(colorData);
        int value;
        std::string color;

        while (stream >> value >> color) {
	  cout<<"c: '"<<color<<"'="<<value<<endl;
	  if (color.find("red") != string::npos) {
                red = value;
            } else if (color.find("green") != string::npos) {
                green = value;
            } else if (color.find("blue") != string::npos) {
                blue = value;
            }
        }
    }
};

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(){
    ifstream infile("input.txt");
    string in;
    int sumA=0;
    int sumB=0;
    while (getline(infile, in)) {
        cout<< "line: "<< in<<endl;
        vector<string> line = split(in,':');
        vector<string> pulls = split(line[1],';');
        bool imposGame = false;
  
        int maxR = 0;
        int maxG = 0;
        int maxB = 0;

	for(string colors :  pulls){
	    cout<<" parsing colors: "<<colors<<endl;
	    ColorSet cset(colors);
	    if(! COLOR_TEST(cset.red,cset.green,cset.blue))
	      imposGame = true; // must be all zeros
  
  	    // find max values
  	    if(maxR < cset.red)    maxR = cset.red;
  	    if(maxG < cset.green)  maxG = cset.green;
  	    if(maxB < cset.blue)   maxB = cset.blue;
  	    cout << " Red: " << cset.red << ", Green: " << cset.green << ", Blue: " << cset.blue << endl;
	}
	int power = maxR * maxG * maxB;   // calculate power
	istringstream gameStream(line[0]);
	string tmp; int gameNr;
	gameStream>>tmp>>gameNr;  // save Game number
	sumA += imposGame ? 0 : gameNr;  // save impossible games
	sumB += power;                  // save powers
    }
    cout <<"sum A: "<< sumA << endl; //2600
    cout<<"sum B: "<<sumB<<endl;  //86036

    return 0;
}

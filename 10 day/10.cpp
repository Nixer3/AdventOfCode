#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stack>
#include <queue>
using namespace std;
#define findInMap(m,elem) ((*m.find(elem)).second)

bool isParanthesis(char p) {
	return string("{(<[]>)}").find(p) != string::npos ? true : false;
}
char findOppo(char p) {
	char ind = string("{(<[").find(p);
/*	in AoC unnecessry
	if (ind == string::npos) {
		char ind2 = string("})>]").find(p);
		if (ind2 == string::npos)
			return 0;
	//	throw string("unexpected AoC case");
		return "{(<["[ind2];
	}
*/
	return "})>]"[ind];
}
bool isOppo(char open, char close) {
	char ind = string("{(<[").find(open);
	char ind2 = string("})>]").find(close);
	if (ind == (int)string::npos)return false; //not found
	return ind == ind2;
}
bool isOpen(char open) {
	return string("{(<[").find(open) != (int)string::npos;
}

stack<char> areParenthesisPaired(const string& line){
	stack<char> ps; //paranthesis stack
	for (char c : line) {
		if (ps.size()) { //not empty stack			
			if (isOppo(ps.top(), c))
				ps.pop(); // removing like tetris
			else if(isOpen(c))
				ps.push(c);//otherwise add to stack
			else 
				throw c; //unexpected ending
		}
		else { //empty stack
			ps.push(c); //add P
		}
	}
	return ps; //everything should be poped, returning leftovers 
}
string antiPstring(string s) {
	string oppo;
	for (char c : s)
		oppo.append(string(1, findOppo(c)));
	return oppo;
}
string getStackString(stack<char> st) {
	string str;
	while (!st.empty()) {
		str.append(string(1,st.top()));
		st.pop();
	}
	return str;
}
typedef unsigned int uint;
int main() {
    string in;
    ifstream infile("inputs");
	map<char, int> pointmap( { {')',3},{']',57},{'}',1197},{'>',25137}});
	map<char, int> pointmapB({ {')',1},{']',2},{'}',3},{'>',4} });
	priority_queue<uint64_t> scoreboard; //heap would be faster I guess
	uint sumA = 0;
	while (getline(infile, in)) {
		stack<char> st;
		//cout << in;
		try {st = areParenthesisPaired(in);}
		catch (char c) {
			cout << " unexpected: " << c;
			int points = findInMap(pointmap,c);
			cout << "points '" << points <<"' " << endl;
			sumA += points;
		}
		if (!st.empty()) {
			cout << " remaining: ";
			string finish;
            //stack reversingorder automatically
			cout<< (finish = antiPstring(getStackString(st)));
			uint64_t tmpSum = 0;
			for (char c : finish) {
				tmpSum = tmpSum * 5 + findInMap(pointmapB, c);
			}
			cout << " tmpSum: " << tmpSum<<endl;
			scoreboard.push(tmpSum);
		}
	}
	cout <<"sumA :" << sumA << endl;
	//go to mid queue
	int iniQlen = scoreboard.size() / 2;
	for (int i = 0; i < iniQlen; i++) {
		scoreboard.pop();
	}
	cout << "midB :" << scoreboard.top() << endl;

    infile.close();
    return 0;
}


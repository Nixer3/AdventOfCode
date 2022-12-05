#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>
#include <ctype.h>
#include <utility>

#include <vector>
#include <stack>
using namespace std;

template<class Stream, class Vector, class Begin = decltype(std::begin(std::declval<Vector>()))>
inline Stream& operator<<(Stream& stream, const Vector& vect) {
	const char* dlm = "";
	for(const auto& i : vect) { stream << dlm << i; dlm = "\n"; }
	return stream;
}
ostream & operator<<(ostream & os, stack<char> stak){
    while(!stak.empty()) //body
    {
        os << stak.top() << " ";
        stak.pop();
    }
    return os;
}
void printStorage(vector<stack<char>> storage){
    cout<<"STORAGE:---------"<<endl;
    for(int i = 0; i< storage.size();i++){
        cout<<"-->"<<storage[i]<<endl;
    }
}
int main(){
    ifstream infile("input");
    string in;
    int count=0;
    vector<string> arr;
    while (getline(infile, in)) {
        if(in == "") //empty line, escape to parse moves
            break;
        arr.push_back(in);
    }
    reverse(arr.begin(),arr.end());
    vector<stack<char>> storage;

    cout<<"height/width   "<<arr.size()<<"/"<<arr[0].length()<<endl; 

    for(int col = 0; col < arr[0].length(); col++){
        if(isdigit(arr[0][col])){
            stack<char> crates;
            for(int row = 1; row < arr.size(); row++){
                if(arr[row][col] != ' ')
                    crates.push(arr[row][col]);
            }
            cout<<"crates "<<arr[0][col]<<"   "<<crates<< "top = "<<crates.top()<<endl;
            storage.push_back(crates);
            
        }
    }
    printStorage(storage);
    int m,f,t; //m=amount,  f/t = from/to  stack
    char crate;

    while (getline(infile, in)) {
        cout<<"parsing >"<<in<<endl;
        sscanf(in.c_str(),"move %d from %d to %d\n", &m,&f,&t ); //parse move
        f-=1;  //input is 1-n
        t-=1;
        stack<char> tmp;
        for(int i=0; i < m; i++){  //picking up
            tmp.push(storage[f].top());
            storage[f].pop();
        }
        for(int i=0; i < m; i++){  //picking up
            storage[t].push(tmp.top());
            tmp.pop();
        }
        printStorage(storage);
    }

    for(auto s : storage){
        cout<<s.top();
    }
    cout<<endl;

    return 0;
}

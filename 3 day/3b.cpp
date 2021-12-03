#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string filter(vector<string> in,unsigned int const off, bool const upper){
    int ones = 0; 
    int won = 0;
    if(off > in[0].length() || in.size() < 2)
        return in[0];
    for(auto str : in)
        if(str[off] == '1')
            ones++;
    if(upper)
        won = ones >= in.size()/2.0 ? 1:0;
    else 
        won = ones >= in.size()/2.0 ? 0:1;
    in.erase(remove_if( in.begin(), in.end(), [off,won](const string& x) { 
        return x[off] != '0'+ won;    
        }), in.end());
    return filter(in, off+1,upper);
}

int main(){
    std::ifstream infile("inputs");  
    vector<string> vec;
    string tmp;
    while (infile >> tmp)
        vec.push_back(tmp);
    string out1 = filter(vec,0,false);
    string out0 = filter(vec,0,true);
    cout<<stoi(out1,0,2) * stoi(out0,0,2) <<endl;
    return 0;
}
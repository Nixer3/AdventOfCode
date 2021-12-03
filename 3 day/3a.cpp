#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define LENGTH 1000
#define WIDTH 12
int main(){

    std::ifstream infile("inputs");  
    string num;
    int zeros[WIDTH]{0}; 
    int i=0;
    while (infile >> num){
        for(int a=0; a < WIDTH; a++){
            if(num[a] == '1')
                zeros[i]++;
            i++;
        }
        i=0;
    }
    char s[WIDTH+1]; s[WIDTH]=0;
    char s1[WIDTH+1]; s1[WIDTH]=0;
    for(int i =0; i < WIDTH; i++){
        s[i] = '0'+(zeros[i] > LENGTH/2);
        s1[i] = '0'+(zeros[i] < LENGTH/2);
    }
    cout<<s<<endl<<s1<<endl;

    int out = stoi(s, 0, 2);
    int out1 = stoi(s1, 0, 2);
    cout<<endl<<out*out1<<endl;
    return 0;
}
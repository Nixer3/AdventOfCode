#include <iostream>
using namespace std;
#include <fstream>


int main(){
    std::ifstream infile("inputs");
    int absX=0;
    int absY=0;
    string dir;
    int i;
    while (infile >> dir >> i){
        if(dir == "forward")
            absX+=i;
        if(dir =="down")
            absY+=i;
        if(dir =="up")
            absY-=i; 
    }
    cout<< absY*absX<<endl;


    return 0;
}


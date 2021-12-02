#include <iostream>
using namespace std;
#include <fstream>


int main(){
    std::ifstream infile("inputs");
    int down=0;
    int fw=0;
    int aim=0;

    string dir;
    int i;
    while (infile >> dir >> i){
        if(dir == "forward")
            aim+=down*i;
        if(dir =="down")
            down+=i;
        if(dir =="up")
            down-=i; 
    }
    cout<< aim*fw <<endl;


    return 0;
}


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;
#define A
#define NEW_FTIMER 8
#define OLD_FTIMER 6

#ifdef B
typedef unsigned long long uintL;
#define GENERATIONS 256
#else //A
typedef unsigned int uintL;
#define GENERATIONS 80
#endif// B /A

void arrRotate(uintL arr[], unsigned int n){
    uintL temp = arr[0];
    for (unsigned int i = 0; i < n - 1; i++)
        arr[i] = arr[i + 1];
    arr[n - 1] = temp;
}

int main() {
    string in;
    ifstream infile("inputs");
    uintL m[NEW_FTIMER + 1];
    memset(m, 0, sizeof(m));

    //parsing file
    while (getline(infile, in, ',')) {
        m[stoi(in, 0, 10)]++;;
    }
    for (int i = 0; i <= GENERATIONS; i++) {
        //arr[0:old]
        arrRotate(m, OLD_FTIMER+1);
        //arr[old:new]
        arrRotate(m + OLD_FTIMER+1, NEW_FTIMER - OLD_FTIMER);
    //age 012345  67
        //234501* 87-
        //7- should move down, and add to 1*, but 1* must create new fish at 8th age
        uintL makingnew = m[OLD_FTIMER];
        m[OLD_FTIMER] += m[NEW_FTIMER];
        m[NEW_FTIMER] = makingnew;
    }
    uintL sum = 0;
    for (int i = 0; i < NEW_FTIMER; i++)
        sum += m[i];
    cout << "count after " << GENERATIONS << " days: " << sum << endl;
    
    return 0;
}


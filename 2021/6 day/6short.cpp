#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
#define GENERATIONS 80
#define NEW_FTIMER 8
#define OLD_FTIMER 6

void arrRotate(uint64_t arr[], unsigned int n){
    uint64_t temp = arr[0];
    for (unsigned int i = 0; i < n - 1; i++)
        arr[i] = arr[i + 1];
    arr[n - 1] = temp;
}
int main() {
    string in;
    ifstream infile("inputs");
    uint64_t m[NEW_FTIMER + 1];
    memset(m, 0, sizeof(m));
    //parsing file
    while (getline(infile, in, ',')) {
        m[stoi(in, 0, 10)]++;;
    }
    for (int i = 0; i <= GENERATIONS; i++) {
        arrRotate(m, OLD_FTIMER+1);
        arrRotate(m + OLD_FTIMER+1, NEW_FTIMER - OLD_FTIMER);
        uint64_t makingnew = m[OLD_FTIMER];
        m[OLD_FTIMER] += m[NEW_FTIMER];
        m[NEW_FTIMER] = makingnew;
    }
    uint64_t sum = 0;
    for (int i = 0; i < NEW_FTIMER; i++)  sum += m[i]; //sum array
    cout << "count after " << GENERATIONS << " days: " << sum << endl;
    
    return 0;
}


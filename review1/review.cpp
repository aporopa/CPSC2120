#include <iostream>
#include "review.h"

using namespace std;

void ReadStdIn(){
    int integer;
    double number;
    string word;

    cin >> integer >> number >> word;
    cout << integer << "\n"
         << number << "\n"
         << word << endl;
}
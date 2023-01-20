#include <iostream>
#include "review.h"

using namespace std;

int WriteOut(string output){
    cout << output << endl;
    return 1;
}

int WriteOut(int output){
    cout << output << endl;
    return 2;
}

int WriteOut(double output){
    cout << output << endl;
    return 3;
}
#include <iostream>
#include "review.h"

using namespace std;

void ReadStdIn2(){
    string input;
    int count = 0;

    cin >> input;

    while(input != "q"){
        count++;
        cin >> input;
    }

    cout << count;
}
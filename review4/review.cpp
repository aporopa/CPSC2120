#include "review.h"
#include <iostream>

using namespace std;

void ReadWrite(){
    string input;
    vector<string> sentence;
    int count = 0;

    cin >> input;

    while(input != "q"){
        sentence.push_back(input);
        cin >> input;
    }

    for(string s : sentence){
        cout << s << " ";
    }

    cout << endl;
}
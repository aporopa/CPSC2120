/*
 * Name: Abigail Poropatich
 * Date Submitted: 1 March 2023
 * Lab Section: 003
 * Assignment Name: Spell Checker Using a Hash Table
 */
 
 #include "stringset.h"
 #include <iostream>
 #include <fstream>
 
 //void testStringset(Stringset& words);
 void loadStringset(Stringset& words, string filename);
 vector<string> spellcheck(const Stringset& words, string word);

 using namespace std;

 void loadStringset(Stringset& words, string filename)
 {
    ifstream infile(filename);
    string userInput;

    //insert users input to a hash line by line
    while(getline(infile, userInput)){if(userInput.length() > 0){words.insert(userInput);}}
 }
 
 vector<string> spellcheck(const Stringset& words, string word)
 {
    int length = word.length();
    string altString = word;
    vector<string> altSpellings;

    //loop through the string and change the i-th character to j
    //and see if it is a real word
    //if it is, add it to the alternative spelling vector
    for(unsigned int i = 0; i < length; i++){
        for(char j = 'a'; j <= 'z'; j++){
            altString[i] = j;
            if(words.find(altString) && (word != altString)) {altSpellings.push_back(altString);}
            altString = word;
        }
    }

    //return all alternative words that varried by one character
    return altSpellings;
 }
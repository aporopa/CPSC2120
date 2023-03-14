/*
 * Name: Abigail Poropatich
 * Date Submitted: 14 March 2023
 * Assignment Name: Anagram Finder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> loadWordlist(string filename);

/*Implement the following function:
  anagram() takes a word (string) and a wordlist of all words (vector of strings)
  and builds a dictionary/map where the key is a specific number of times each
  letter occurs in a word and the associated value is a vector of strings
  containing all words using those letters (anagrams).
  The value returned is a vector of strings containing the corresponding
  set of anagrams
*/
vector<string> anagram(string word, vector<string> wordlist);

int main()
{
    vector<string> words;
    vector<string> anagrams;
    string inputWord;
    words=loadWordlist("wordlist.txt");
    cout << "Find single-word anagrams for the following word: ";
    cin >> inputWord;
    anagrams = anagram(inputWord, words);
    for (int i=0; i<anagrams.size(); i++)
    {
        cout << anagrams[i] << endl;
    }
    return 0;
}

vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

//Implement this function
vector<string> anagram(string word, vector<string> wordlist)
{
    unordered_map<string, vector<string>> dictionary;
    vector<string> key;
    string sorted;

    //Creating the dictionary from the input list
    for(int i = 0; i < wordlist.size(); i++){
        sorted = wordlist[i];
        sort(sorted.begin(), sorted.end());

        dictionary[sorted].push_back(wordlist[i]);
    }

    //Finding the anagrams of the input word
    sorted = word;
    sort(sorted.begin(), sorted.end());
    if(dictionary.find(sorted) != dictionary.end()){
        vector<string> anagramed = dictionary[sorted];
        key.insert(key.end(), anagramed.begin(), anagramed.end());
    }

    return key;
}
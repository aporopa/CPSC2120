/*
 * Name: Abigail Poropatich
 * Date Submitted: 28 April 2023
 * Assignment Name: Word Ladder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type
unordered_map<string, vector<string>> nextTo;
unordered_map<string, string> before;
unordered_map<string, int> length;
unordered_map<string, int> allDone;
//Implement breadth-first search, refer to Lab 10
int FindingPath(const string& stringStart, const string& stringEnd, vector<string>& stringPath);

void wordLadder(string s, string t, int &steps, vector<string> &p){
  ifstream file ("wordlist05.txt");
  string word = "";

  //put all the words into a vector
  while(file >> word) V.push_back(word);
  for(auto text : V){
    for(int i = 0; i < text.length(); i++){
      for(int character = 'a'; character <= 'z'; character++){
        if(character == text.at(i)) continue;
        string modified = text;
        modified.replace(i, 1, 1, character);
        nextTo[text].push_back(modified);
      }
    }
  }

  //keeps track of the shortest path from the starting word
  length[s] = 0;
  //keeps track of whether or not the node has been visited
  allDone[s] = 1;
  queue<string> thisOne;
  thisOne.push(s);

  //driver loop to find the shortest path
  while(thisOne.empty() == 0){
    string node = thisOne.front();
    thisOne.pop();

    //checking all nodes that are near the current node
    for(auto s : nextTo[node]){
      //hasn't been visited yet
      if(allDone[s] == 0){
        //sort the reachable nodes
        before[s] = node;
        length[s] = length[node] + 1;
        allDone[s] = 1;

        //add the reachable nodes to queue
        thisOne.push(s);
      }
    }
  }

  steps = FindingPath(s,t,p);
}

int FindingPath(const string& stringStart, const string& stringEnd, vector<string>& stringPath){
  //catches any seg faults
  if(before.count(stringEnd) == 0) return 0;
  stringPath.clear();

  //if they're the same words
  if(stringStart == stringEnd){
    stringPath.push_back(stringEnd);
    return 0;
  }

  //add the end word to the vector
  stringPath.push_back(stringEnd);
  int count = 0;
  string stringCurrent = stringEnd;

  //loop until the first word is found
  while(before[stringCurrent] != stringStart){
    stringPath.push_back(before[stringCurrent]);
    stringCurrent = before[stringCurrent];
    ++count;
  }

  stringPath.push_back(stringStart);
  ++count;

  //put in the proper order
  reverse(stringPath.begin(), stringPath.end());

  return count;
}
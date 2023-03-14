/*
 * Name: Abigail Poropatich
 * Date Submitted: 1 March 2023
 * Lab Section: 003
 * Assignment Name: Spell Checker Using a Hash Table
 */

#include "stringset.h"
#include <functional>
#include <iostream>

using namespace std;

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string> > Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

void Stringset::insert(string word)
{
    //creating hash table and store the location of a particular word
    hash<string> hashTable;
    int location = hashTable(word) % size;

    //if the word is already there do not insert a duplicate
    if(find(word) == true) {return;}

    //if the size does equal the elements
    ///double the size of the list
    else if(size == num_elems){
        int resize = size*2;
        vector<list<string>> newHash(resize);
    
        //copy each element into a new hash according to its new index
        for(int i = 0; i < size; i++){
            list<string>::const_iterator iterator = table[i].begin();
            while(iterator != table[i].end()){
                int resizedLocation = hashTable(*iterator) % resize;
                newHash[resizedLocation].push_back(*iterator);

                iterator++;
            }
        }

        //update the variables
        table = newHash;
        size = resize;
    }

    //establish the word in hash w/ updted size
    location = hashTable(word) % size;
    table[location].push_front(word);
    num_elems++;
}

bool Stringset::find(string word) const
{
    //creating hash table, index where the string is stored,
    //and create an iterator that can traverse the strings at a certain index
    hash<string> hashTable;
    int location = hashTable(word) % size;
    list<string>::const_iterator iterator = table[location].begin();

    //while the iterator is not at the end of the list
    //checking to see if each element matches the input word
    //if it does, return true. Otherwise, it is false.
    while(iterator != table[location].end()){
        if(*iterator == word){return true;}
        iterator++;
    }

    return false;

}

void Stringset::remove(string word)
{
    //creating hash table and store the location of a particular word
    hash<string> hashTable;
    int location = hashTable(word) % size;

    //if the word exists
    //remove it and decrease the size
    if(find(word) == true){
        table[location].remove(word);
        num_elems--;
    }

}
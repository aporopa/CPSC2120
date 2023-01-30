/*
 * Name: Abigail Poropatich
 * Date Submitted: 29 January 2023
 * Lab Section: 003
 * Assignment Name: Lab 1 - Linked List Based Stacks and Queues
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializing this list's instance variables
template <class T>
List<T>::List(){
  //initial condition for the start is nullptr 
  //and 0 because it should be assumed that the list is initally empty
  start = nullptr;
  mySize = 0;
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){
  Node<T> *current = start;
  
  //The while loop iterates through the list 
  //As long as the first thing it encounters is not the start of the list
  while(current != nullptr){
    Node<T> *next = current->next;
    delete current; 

    //Assign current to the next node, and delete 
    //Repeat until nullptr is reached
    current = next; 
  }
}

//Return the size of this list
template <class T>
int List<T>::size(){
  return mySize;
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty(){
  return start == nullptr;
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value){
  //dynamically allocating memory--creating new node with "value"
  Node<T> *newNode = new Node<T>(value); 

  if(empty()){
    start = newNode; //update start
    newNode->next = nullptr;
  }

  else{
    newNode->next = start;
    start = newNode;
  }

  mySize++; //increment the list
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value){
  Node<T> *newEnd = new Node<T>(value);

  //if the list is empty
  if(empty()){
    start = newEnd; //despite this being an insertEnd() function
                    //if the list is currently empty then assign the end node as the start

    mySize++; //increment
  }

  //if the list contains nodes
  else{
    Node<T> *track = start;

    //while start does not equal nullptr
    while(track->next != nullptr){
      track = track->next;
    }

    //access the last variable and assign it to the end
    track->next = newEnd;
    mySize++; //increment
  }
}

//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j){
  Node<T> *insertNode = new Node<T>(value);

  //if the position is 0, it means the new node should be inserted at the start of the list
  if(j == 0){
    insertNode->next = start;
    start = insertNode;
    mySize++;
  }

  //if the position is not 0, then assign k to the start of the list and iterate
  else if(j >= mySize){
    insertEnd(value);
  }

  else{
    Node<T> *k = start;

    //iterate using a for loop, moving the k place holder 
    //until it reaches the spot before where the pointer should be inserted
    for(int i = 0; i < j-1; i++){
      k = k->next;
    }

    //making the next pointer the new node
    insertNode->next = k->next;
    k->next = insertNode;

    //increment
    mySize++;
  }
}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart(){

  //empty list
  if(start == nullptr)
    return;

  else{
    Node<T> *temp = start;

      start = start->next;
      delete temp;
      mySize--;
  }
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd(){

  //check if empty
  if(start == nullptr){
    return;
  }

  //check if there is only one value in the list
  else if(mySize == 1){
    removeStart();
  }

  //else loops through the nodes until last element is reached
  //then, delete it and decrement the list size
  else{
    Node<T> *current = start;
    for(int i = 0; i < mySize - 2; i++){
    current = current->next;
    }

    Node<T> *del = current->next;
    current->next = nullptr;

    delete del;
    mySize--;
  }
}

//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j){

  //if j is the first element
  if(start == nullptr){
    return;
  }

  //check if j is first element, then call prev function
  else if(j == 0){
    removeStart();
  }

  //check if j is last element, then call prev function
  else if(j >= mySize){
    removeEnd();
  }

  else{
    Node<T> *current = start;

    for(int i = 0; i < j -1; i++){
      current = current->next;
    }

    //remove the nth element
    Node<T> *del = current->next;
    current->next = del->next;
    delete del;
    mySize--;
  }

  //if j is the last element
  if(j == mySize - 1){
    removeEnd();
    return;
  }
}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst(){
  //check if the list is empty
  if(mySize == 0)
    return T(); //returning the constructed values

  //returning value of first node
  else 
    return start->value;
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast(){

  //if empty
  if(start == nullptr)
    return T();

  else{
    Node<T> *current = start;
    while(current->next != nullptr){
      current = current->next;
    }
    //value of last node
    return current->value;
  }
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j){

  //if empty
  if(start == nullptr)
    return T();

  Node<T> *temp = start;

  //iterate until the position the user entered
  for(int i = 0; i < j; i++)
    temp = temp->next;

  return temp->value;
}

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key){
  //will keep track of the position of the node
  int pos = 0;

  //pointer that will loop through the list
  Node<T> *current = start;


  //loop through till key is found or end of the list is reached
  while(current != nullptr){
    if(current->value == key){
      return pos;
    }

    //move to the next node, and increate the position counter
    current = current->next;
    pos++;
  }
  
  return -1;
}
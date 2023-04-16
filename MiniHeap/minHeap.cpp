/*
 * Name: Abigail Poropatich
 * Date Submitted: 16 April 2023
 * Assignment Name: MinHeap implementation using a vector
 */
#pragma once

#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include "minHeap.h"

using namespace std;

//If the child node is greater than its parent
//then sift up through the tree
void minHeap::siftUp(int pos){
    int parent = floor((pos - 1)/2);
    if(pos == 0) return;

    //if the child is larger than its parent
    while(heap[parent] > heap[pos]){
        swap(heap[pos], heap[parent]);
        siftUp(parent);
    }
}

//if the parent node is larger than one of its children
//then sift down
void minHeap::siftDown(int pos){
    //calculating indicies
    int parent = pos;
    int leftChild = 2*parent + 1;
    int rightChild = 2*parent + 2;

    //reassignment of the parent in reference to its children
    if(leftChild < heap.size() && heap[leftChild] < heap[parent]) parent = leftChild;
    if(rightChild < heap.size() && heap[rightChild] < heap[parent]) parent = rightChild;
    if(pos != parent){
        swap(heap[pos], heap[parent]);
        siftDown(parent);
    }
}

//remove the minimum value (i.e. the head node)
//by swapping the last element with the head node
//then popping it out, decrememnting the size, and sifting down
int minHeap::removeMin(){
    int minVal = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    if(heap.size() > 0) siftDown(0);

    return minVal;
}

//insert at the bottom as a leaf node
//then sift up as necessary
void minHeap::insert(int value){
    heap.push_back(value);
    siftUp((heap.size() - 1));
}

//initialize the heap to the passed in vector
//and build from the bottom up
minHeap::minHeap(vector<int> data){
    heap = data;
    int parent = floor((heap.size() - 1) / 2);

    while(parent >= 0){
        siftDown(parent);
        parent--;
    }
}
/*
 * Name: Abigail Poropatich
 * Date Submitted: 17 February 2023
 * Lab Section: 003
 * Assignment Name: Searching and Sorting
 */

#pragma once

#include <vector>
#include <algorithm>
using namespace std;

template <class T>
std::vector<T> mergeSort(std::vector<T> lst){
    //Base case
    //return if there is 1 or less elements
    if(lst.size() <= 1)
        return lst;

    int middle = lst.size() / 2;

    //Creating the left and right vectors based on the middle index
    vector<T> leftSort(lst.begin(), lst.begin() + middle);
    vector<T> rightSort(lst.begin() + middle, lst.end());

    //Recursively sort
    leftSort = mergeSort(leftSort);
    rightSort = mergeSort(rightSort);

    //Clear the original vector
    lst.clear();

    //Merge the sorted vectors back into lst
    for(int i = 0; i < leftSort.size(); i++)
        lst.push_back(leftSort[i]);
    
    for(int i = 0; i < rightSort.size(); i++)
        lst.push_back(rightSort[i]);

    //Sort the merged vector
    sort(lst.begin(), lst.end());

    return lst;
}

template <class T>
std::vector<T> quickSort(std::vector<T> lst){
    //Base case
    //return if there is 1 or less elements
    if(lst.size() <= 1)
        return lst;

    //Establish the pivot as the first element
    //and create two vectors
    //1. Values less than the pivot
    //2. Values greater than the pivot
    T pivot = lst[0];
    vector<T> rightSort;
    vector<T> leftSort;

    for(int i = 1; i < lst.size(); i++){
        //Sorting into the "less than" vector
        if(lst[i] < pivot)
            leftSort.push_back(lst[i]);

        //Sorting into the "greater than" vector
        else
            rightSort.push_back(lst[i]);
    }

    //recursively sort the vectors
    leftSort = quickSort(leftSort);
    rightSort = quickSort(rightSort);

    //Clear the original vector
    lst.clear();

    //Merge the sorted vectors back into lst
    for(int i = 0; i < leftSort.size(); i++)
        lst.push_back(leftSort[i]);
    
    lst.push_back(pivot);

    for(int i = 0; i < rightSort.size(); i++)
        lst.push_back(rightSort[i]);

    return lst;
}

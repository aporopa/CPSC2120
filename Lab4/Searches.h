/*
 * Name: Abigail Poropatich
 * Date Submitted: 17 February 2023
 * Lab Section: 003
 * Assignment Name: Searching and Sorting
 */

#pragma once

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <class T>
int linearSearch(std::vector<T> data, T target){
    //Iterate through the list and see if the target matches the value at the index
    //if it does, return the index position
    for(int i = 0; i < data.size(); i++){
        if(data[i] == target)
            return i;
    }
    //if it does not match
    return -1;
}


template <class T>
int binarySearch(std::vector<T> data, T target){
    //Sort the vector
    sort(data.begin(), data.end());

    //setting bounds for search range
    int low = 0;
    int high = data.size()-1;
    
    //While the search range is not empty
    while(low <= high){
        int middle = (high + low)/2;

        //if the target is the middle element, return the middle element value
        if(data[middle] == target)
            return middle;

        //If the target is greater than the value at the middle index 
        //search the right half of the range
        else if(target > data[middle]){
            low = middle + 1;
        }

        //If the target is less than the value at the middle index
        //then search the left half of the range
        else{
            high = middle - 1;  
        }
    }

    //if not found
    return -1;
}

/*
 * Name: Abigail Poropatich
 * Date Submitted: 16 April 2023
 * Lab Section: 003
 * Assignment Name: Lab 9 - Using Recursion to Solve the N-Queens Problem
 */

#include <iostream>
#include <vector>

using namespace std;

bool ValidPosition(vector<int>& board, int r, int c);
int TrackingNQueens(int n, vector<int>& board, int r);
int nQueens(int n);

//Checks if the position is valid
//Queen cannot be placed in the diagonal, row, or column of another queen
bool ValidPosition(vector<int>& board, int r, int c){
    bool check = true;

    //Checked all of the rows
    if(r == board.size()) return false;

    for(int i = 0; i < r; i++){
        //calculating the difference between the current pos and the column
        int difference = (board[i] > c) ? (board[i] - c) : (c - board[i]);
        //if the difference is 0, then it is on the same row
        //if the difference is r-i then it is on the diagonal
        if(difference == 0 || difference == r-i) check = false;
    }

    return check;
}

//Keeps track of how many queens have been places
int TrackingNQueens(int n, vector<int>& board, int r){
    int tracker = 0;

    //checked all the rows
    if(r == n) return 1;
    else{
        for(int c = 0; c < n; c++){
            if(ValidPosition(board, r, c)){
                //if the position is valiid, then we can place miss queen
                board[r] = c;
                //tracking the number of valid positions
                tracker = TrackingNQueens(n, board, r+1) + tracker;
            }
        }
    }

    return tracker;
}

//Uses recursion to tracker how many solutions there are for
//placing n queens on an nxn chess board
int nQueens(int n){
    vector<int> board(n, -1);
    return TrackingNQueens(n, board, 0);
}
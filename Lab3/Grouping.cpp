/*
 * Name: Abigail Poropatich
 * Date Submitted: 9 February 2023
 * Lab Section: 003
 * Assignment Name: Finding Groups Using Recursion
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below

Grouping::Grouping(string fileName){
    ifstream myFile(fileName);
    string input;
    vector<GridSquare>counting;

    //driving loops to check .txt
    for(int i = 0; i < 10; i++){
        //reading through the file
        getline(myFile, input);
        for(int j = 0; j < 10; j++){
            //if j variable is equal to 'X', then assign 1
            grid[i][j] = (input[j] == 'X') ? 1 : 0;
        }
    }

    //iterate through all rows
    for(int i = 0; i < 10; i++){
        //iterate through columns
        for(int j = 0; j < 10; j++){
            //if a marker is encountered, call the findGroup function
            if(grid[i][j] == 1){

                groups.push_back(vector<GridSquare>());
                findGroup(i,j);
                // groups.push_back(counting);
                // counting.clear();
            }
        }
    }
    
}

void Grouping::findGroup(int r, int c){

    //base case, checking boundaries
    if(r < 0 || r >= 10 || c < 0 || c >= 10)
        return;
    
    if(grid[r][c] == 0)
        return;
    
    //recursive step
    grid[r][c] = 0;

    findGroup(r+1, c);
    findGroup(r-1, c);
    findGroup(r, c+1);
    findGroup(r, c-1);

    groups[groups.size() - 1].push_back(GridSquare(r,c));
    
}



//Simple main function to test Grouping
//Be sure to comment out main() before submitting
// int main()
// {
//   bool correct = false;
//   int groupNum = 0;
//   int totalSize = 0;

//   int groupCount = 2;
//   int sizeTest[] = {16, 16};
//   bool groupTestPass[] = {false, false, false, false, false,
//                           false, false, false, false, false};


//   Grouping input("input4.txt");
//   vector<vector<GridSquare>> groups;
//   groups = input.getGroups();

//   for (int g=0; g<groupCount; g++)
//   {
//     for (int i=0; i<groups.size(); i++)
//     {
//       if(sizeTest[g] == groups[i].size())
//       {
//         groupTestPass[g] = true;
//       }
//     }
//   }

//   correct = groupTestPass[0];
//   for (int g=1; g<groupCount; g++)
//   {
//     correct = correct && groupTestPass[g];
//   }

//   for (int i=0; i<groups.size(); i++)
//   {
//     totalSize += groups[i].size();
//   }

//   if (totalSize != 32)
//   {
//     correct = false;
//     cout << "total number of square(s) counted: " << totalSize << ", expected: 32.\n";
//   }

//   //ASSERT_EQ(correct, true);
//   if (correct != true)
//   {
//     cout << "expected/correct value true (1), actual value when testing " << correct << ".\n";
//     return 1;
//   }
//   cout << "Passed" << endl;
//   return 0;
// }

//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}
/*
 * Name: Abigail Poropatich
 * Date Submitted: 13 March 2023
 * Lab Section: 003
 * Assignment Name: Lab 6
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

struct point
{
    double x;
    double y;
};

//overloading the '<' operator
inline bool operator<(const point& leftSide, const point& rightSide)	
{
    if (leftSide.x < rightSide.x) return true;
    else if (leftSide.x > rightSide.x) return false;
    else return leftSide.y < rightSide.y;
    
}

//check if two points are already connected in a set
bool ConnectingPoints(point first, point second, std::set<vector<point>>& setter){
    vector<point> temp = {first, second};

    //Checking if the vector is in the set
    if(setter.find(temp) != setter.end()) return true;
    else return false;
}

//calculates the shortest distance between a point and all other
//points in the hasher vector
//skips over points that have been previously connected
double MinimumDistance(point current, vector<point> &hasher, set<vector<point>> prev){
    double min = std::numeric_limits<double>::max();

    //driving loop to check hashers points
    for(const auto p : hasher){
        //skip the current point
        if(p.x == current.x && p.y == current.y) continue;
        //skip if theyve already been connected
        if(ConnectingPoints(current,p,prev)) continue;

        //if the calculated distance is less than the current distance
        //store in the temp vector and add to prev and declare as connected
        if(sqrt(pow((current.x - p.x),2) + pow((current.y - p.y),2)) < min){ 
            min = sqrt(pow((current.x - p.x),2) + pow((current.y - p.y),2));
            vector<point> temp = {current, p};
            prev.insert(temp);
        }
    }
        return min;
}

double closestPair(string filename){
    int nPoint = 0;
    ifstream infile(filename);
    infile >> nPoint;

    int b = sqrt(nPoint);

    //3-D vector of points
    vector<vector<vector<point>>> cells(b, vector<vector<point>>(b));
    cells.resize(b);

    vector<point> points(nPoint);

    for(int i = 0; i < nPoint; i++){
        point count;

        count.x = 0;
        count.y = 0;
        infile >> count.x;
        infile >> count.y;

        int xV = (int)(count.x * b);
        int yV = (int)(count.y * b);

        cells[xV][yV].push_back(count);
        points[i] = count;
    }

    sort(points.begin(), points.end());

    set<vector<point>> checkerVec;
    double min = 1;

    for(int i = 0; i < nPoint; i++){
        for(int j = i + 1; j < nPoint && points[j].x - points[i].x < min; j++){
            double validate = sqrt(pow((points[i].x - points[j].x),2) + pow((points[i].y - points[j].y),2));
            if(validate < min && ConnectingPoints(points[i], points[j], checkerVec) == false){
                min = validate;
                vector<point> temp;
                temp.emplace_back(points[i]);
                temp.emplace_back(points[j]);
                checkerVec.insert(temp);
            }
        }
    }
    return min;
}


// int main()
// {
//     double min;
//     string filename;
//     cout << "File with list of p within unit square: ";
//     cin >> filename;
//     min = closestPair(filename);
//     cout << setprecision(16);
//     cout << "Distance between closest pair of p: " << min << endl;
//     return 0;
// }
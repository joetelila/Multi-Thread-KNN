// Author : Yohannis Kifle Telila.
// Date : 17/02/2022 [my BD]
// Desc : This file contain code for calculating KNN of a 2D points using sequantial
//        patterns using only C++ STL.


// include necessary libraries.
#include <iostream>
#include "src/utils.h"
using namespace std;


//def knn_sequential(int datapoints, int datapoint, int k){

 // code here.

//}


int main(int argc, char const *argv[]) {

  int  k = 5;
  // where the points are going to be stored [the one read from]
  vector<point> points; // where 2d points are stored

  string knn_seq_results = "";      // what will store the sequential result, string for convenience of output to file
  string filename = "points.txt";

  points = read2dpoints(filename);
  //knn_seq_results=knn_seq_compute(points, k);
  return 0;
}


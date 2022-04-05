/*
  C++ STL implementation of sequential knn.
*/
// Author : Yohannis Kifle Telila.
// Date : 17/02/2022
// Desc : This file contain code for calculating KNN of a 2D points using sequantial
//        patterns using only C++ STL.


// include necessary libraries.
#include <iostream>
#include <thread>
#include <cstring>
#include "src/utimer.cpp"
#include "src/utils.h"
using namespace std;


int main(int argc, char const *argv[]) {
  if (argc < 3) {
    cerr << "use: " << argv[0]  << " k-value input_file_path -d [optional -d flag to output only nw and running time]\n";
    return -1;
  }

  int  k = atoi(argv[1]); // k value.
  string filepath = argv[2]; // input file path.];
  string d = "";
  if(argv[3] != NULL){
    d = string(argv[3]);
  }
  
  // where the points are going to be stored [the one read from]
  vector<point> points; // where 2d points are stored
  vector<knn_result> knn_seq_result;      // what will store the sequential result.
  
  points = read2dpoints(filepath);
  int points_size  = points.size();  
  
  long seq_time;
  // Computing knn in sequantial.
  {
     utimer t_seq("STL Sequential KNN", &seq_time);
    // sequential knn
    vector<int> res;
    for(int i=0;i<points.size();i++){
       knn_result res;res.index = i;
       res.knn_index = get_knn(points, points.size(), i, k);
       knn_seq_result.push_back(res);      
     }

  }

  // printing the result.
  print_knn_result(knn_seq_result,k,seq_time,1, argv[0], d); // 1 is nw. 

  
  return 0;
}


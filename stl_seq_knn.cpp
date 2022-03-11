/*
  C++ STL implementation of sequential knn.
*/
// Author : Yohannis Kifle Telila.
// Date : 17/02/2022 [my BD]
// Desc : This file contain code for calculating KNN of a 2D points using sequantial
//        patterns using only C++ STL.
// include necessary libraries.
#include <iostream>
#include <thread>
#include <cstring>
#include "src/utimer.cpp"
#include "src/utils.h"
#include "src/stl_knn_seq.h"
#include "src/stl_knn_par.h"
using namespace std;


int main(int argc, char const *argv[]) {
  if (argc<3) {
        cerr << "use: " << argv[0]  << " nworkers k-value -d [optional -d flag to output only nw and running time]\n";
        return -1;
    }

  int nw = atoi(argv[1]); 
  int  k = atoi(argv[2]); // k value.
  string d = "";
  if(argv[3] != NULL){
    d = string(argv[3]);
  }
  
  // where the points are going to be stored [the one read from]
  vector<point> points; // where 2d points are stored
  string knn_seq_results = "";      // what will store the sequential result.

  string filepath = "data/input_medium.txt";
  
  points = read2dpoints(filepath);  
  
  long seq_time;
  // Computing knn in sequantial.
  {
     utimer t_seq("STL Sequential KNN", &seq_time);
    // sequential knn 
    knn_seq_results = stl_knn_sequential(points, k);
  }

  // writing the results to a file.
  
  if (string(d)=="-d"){
      cout<<"[nw]: "<<nw<<"  [k]: "<<k<<"  [time]: "<<seq_time<<"\n";
  }else{
      ofstream stl_res_writer("results/stl_seq_res.txt");
      stl_res_writer << knn_seq_results;
      stl_res_writer.close();
       cout<<"Result has been written to results/stl_seq_res.txt"<<endl;
  }



  
  return 0;
}


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
  string knn_seq_results = "";      // what will store the sequential result.

  
  points = read2dpoints(filepath);
  int points_size  = points.size();  
  
  long seq_time;
  // Computing knn in sequantial.
  {
     utimer t_seq("STL Sequential KNN", &seq_time);
    // sequential knn
    string res;
    for(int i=0;i<points.size();i++){
       res = get_knn(points, points.size(), i, k);
       knn_seq_results+= to_string(i)+": "+ res;
       knn_seq_results+="\n";
    }

  }
  // writing the results to a file.
  // Note : if you use -d, it wont write the results to a file.
  if (string(d)=="-d"){
      cout<<"[k]: "<<k<<"  [time]: "<<seq_time<<"\n";
  }else{
      ofstream stl_res_writer("outputs/stl_seq_res.txt");
      stl_res_writer << knn_seq_results;
      stl_res_writer.close();
      cout<<"STL Seq, Finished in "<<seq_time<<" ms.\n";
      cout<<"Result has been written to outputs/stl_seq_res.txt"<<endl;
  }
  return 0;
}


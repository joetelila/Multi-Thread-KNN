/*
  C++ openMp implementation of parallel knn.
*/
// Author : Yohannis Kifle Telila.
// Date : 17/02/2022
// Desc : This file contain code for calculating KNN of a 2D points using sequantial
//        patterns using openMp library.


// include necessary libraries.
#include <iostream>
#include <omp.h>
#include <bits/stdc++.h> // vector sort
#include <mutex>
#include <cstring>
#include "src/utimer.cpp"
#include "src/utils.h"

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc<4) {
        cerr << "use: " << argv[0]  << " nworkers k-value input_file_path -d [optional -d flag to output only nw, k and running time]\n";
        return -1;
    }

  // parallel knn 
  int nw = atoi(argv[1]);  // number of workers
  int  k = atoi(argv[2]); // k(neighbor) value.
  string filepath = argv[3]; // input file path.];  
  string d = ""; // output flag.0
  string finalResult = "";
  if(argv[4] != NULL){
    d = string(argv[4]);
  }
  // checking for k value.
  if (k < 1){
    cerr << "k must be greater than or equal to 1\n";
    return -1;
  }
  
  // where the points are going to be stored [the one read from]
  vector<point> points; // where 2d points are stored
  vector<knn_result> omp_par_result;    // what will store the result.
  points = read2dpoints(filepath);  
  int points_len  = points.size();
  vector<knn_result> par_chunk_result;
  long openmp_time;
  // Computing knn in sequantial.
  {
     utimer t_seq("openMp Parallel KNN", &openmp_time);
      // Ref : Intro to openMP_Mattson - page 76.
      #pragma omp parallel num_threads(nw) shared(points, omp_par_result, points_len, k) private(par_chunk_result)
      {
        #pragma omp for schedule(static)
        for(int i=0;i<points_len;i++){
          knn_result res;res.index = i; 
          res.knn_index = get_knn(points, points_len, i, k);
          par_chunk_result.push_back(res);
        }
      
        #pragma omp critical // Mutual exclusion: Only one thread at a time can enter a criticalregion.
        omp_par_result.insert(omp_par_result.end(), par_chunk_result.begin(), par_chunk_result.end());
      }

      // sorting the result.
      sort(omp_par_result.begin(), omp_par_result.end(), compare_point_index);
    }
  
  
  // printing results.
  print_knn_result(omp_par_result,k,openmp_time,nw,argv[0],d);
    
  
  return 0;
}


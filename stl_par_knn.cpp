/*
  STL C++ implementation of parallel KNN
*/

// Author : Yohannis Kifle Telila.
// Date : 17/02/2022 [my BD]
// Desc : This file contain code for calculating KNN of a 2D points using sequantial
//        patterns using only C++ STL.
// include necessary libraries.
#include <iostream>
#include <thread>
#include "src/utimer.cpp"
#include "src/utils.h"
#include "src/stl_knn_seq.h"
#include "src/stl_knn_par.h"
using namespace std;


int main(int argc, char const *argv[]) {

  if (argc<3) {
        std::cerr << "use: " << argv[0]  << "nworkers k-value\n";
        return -1;
    }
  
  // parallel knn 
  int nw = atoi(argv[1]); 
  int  k = atoi(argv[2]); // k value.

  // where the points are going to be stored [the one read from]
  vector<point> points; // where 2d points are stored
  string knn_par_results = "";      // what will store the parallel result.

  string filepath = "data/input_medium.txt";
  
  points = read2dpoints(filepath);  
    
  vector<thread> threads;
  vector<interval> ranges(nw);
  int delta = points.size() / nw;
  
  string results[nw];
  
   {
      utimer t_seq("Paralle KNN: ");

    auto compute_chunk = [&results](vector<point> points, interval range, int k, int i) {   // function to compute a chunk
    //cout<<"Thread "<<i<<": Range: "<<range.start<<" "<<range.end<<endl;
    results[i] = knn_par_stl(points, range, k);
    };
    
    // split the points into nw ranges.
    for(int i=0; i<nw; i++){
        ranges[i].start = i*delta;
        ranges[i].end = (i != (nw-1) ? (i+1)*delta : points.size());
      }
    
    // let threads start, assigning them a function and an amount of work
    for(int i=0; i<nw; i++){
      // cout<<"Thread "<<i<<": Range: "<<ranges[i].start<<" "<<ranges[i].end<<endl;
      if(true){
         threads.push_back(thread(compute_chunk, points, ranges[i], k, i));
      }else
      continue;
   }  
    // await thread termination
    for(thread& t: threads) {                       
      t.join();
     } 
   }
  //cout<<"All threads finished"<<endl;
  // join the results
  for(int i=0; i<nw; i++){
    knn_par_results += results[i];
  }
  // writing the results to a file.
  ofstream stl_par_writer("results/stl_par_res.txt");
  stl_par_writer << knn_par_results;
  stl_par_writer.close();
  cout<<"Result has been written to results/stl_par_res.txt"<<endl;
  return 0;
}


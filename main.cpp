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

  int  k = 5; // k value.
  // where the points are going to be stored [the one read from]
  vector<point> points; // where 2d points are stored
  string knn_seq_results = "";      // what will store the sequential result.
  string knn_par_results = "";      // what will store the parallel result.

  string filepath = "data/input_medium.txt";
  
  points = read2dpoints(filepath);
  
  // Computing knn in sequantial.
  {
    utimer t_seq("Sequential KNN");
    // sequential knn 
    knn_seq_results = stl_knn_sequential(points, k);
  }

    // parallel knn 
    int nw = 10;
    vector<thread> threads;
    vector<interval> ranges(nw);
    int delta = points.size() / nw;
    
    string results[nw];

    auto compute_chunk = [&results](vector<point> points, interval range, int k, int i) {   // function to compute a chunk
     cout<<"Thread "<<i<<": Range: "<<range.start<<" "<<range.end<<endl;
     knn_par_stl(points, range, k);
    };
    
    {
      utimer t_seq("Paralle KNN: ");
   
    // split the points into nw ranges.
    for(int i=0; i<nw; i++){
        ranges[i].start = i*delta;
        ranges[i].end = (i != (nw-1) ? (i+1)*delta : points.size());
      }
    
    // let threads start, assigning them a function and an amount of work
    for(int i=0; i<nw; i++){
        threads.push_back(thread(compute_chunk, points, ranges[i], k, i));
    }
       
    // await thread termination
    for(thread& t: threads) {                       
      t.join();
    } 
    
    }

    cout<<"All threads finished"<<endl;
    // join the results
    for(int i=0; i<nw; i++){
      knn_par_results += results[i];
    }
    // cout<<knn_par_results<<endl;

  return 0;
}


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

  if (argc<4) {
        cerr << "use: " << argv[0]  << " nworkers k-value input_file_path -d [optional -d flag to output only nw, k and running time]\n";
        return -1;
    }
  
  // parallel knn 
  int nw = atoi(argv[1]); 
  int  k = atoi(argv[2]); // k value.
  string filepath = argv[3]; // input file path.];  
  string d = "";
  if(argv[4] != NULL){
    d = string(argv[4]);
  }
  // where the points are going to be stored [the one read from]
  vector<point> points; // where 2d points are stored
  string knn_par_results = "";      // what will store the parallel result.
  
  points = read2dpoints(filepath);  
    
  vector<thread> threads;
  vector<interval> ranges(nw);
  int delta = points.size() / nw;
  
  string results[nw];
  
  long par_time;
   {
      utimer t_seq("STL Paralle KNN: ", &par_time);

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

  if (string(d)=="-d"){
      cout<<"[nw]: "<<nw<<"  [k]: "<<k<<"  [time]: "<<par_time<<"\n";
  }else{
      // writing the results to a file.
    ofstream stl_par_writer("results/stl_par_res.txt");
    stl_par_writer << knn_par_results;
    stl_par_writer.close();
    cout<<"STL par, Finished in "<<par_time<<" ms.\n";
    cout<<"Result has been written to results/stl_par_res.txt"<<endl;
  }

  return 0;
}
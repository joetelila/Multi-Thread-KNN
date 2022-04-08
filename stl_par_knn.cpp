/*
  STL C++ implementation of parallel KNN
*/
// Author : Yohannis Kifle Telila.
// Date : 17/02/2022
// Desc : This file contain code for calculating KNN of a 2D points using sequantial
//        patterns using only C++ STL.
// include necessary libraries.
#include <iostream>
#include <thread>
// mutex
#include <mutex>
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
  std::mutex iomutex; // for output.
  if(argv[4] != NULL){
    d = string(argv[4]);
  }
  // checking for k value.
  if (k < 1){
    cerr << "k must be greater than or equal to 1\n";
    return -1;
  }
  // where the points are going to be stored [the one read from]
  vector<point> points; // where 2d points are stored after reading from file.
  string knn_par_results = "";      // what will store the parallel result.
  
  // Read the file and store the points in the vector.
  long read_ftime;
  {
   utimer t_seq("File read took: ", &read_ftime);

  points = read2dpoints(filepath);  
  } 

  int points_size  = points.size();
  vector<thread> threads;         // where the threads are going to be stored.
  vector<interval> ranges(nw);    // where the ranges are going to be stored.
  int delta = points.size() / nw; // the delta for each thread.
  
  // This result array is accessed by all the threads but each entry is only accessed(write to it) by one thread.
  // So, its like owner writes / computes access pattern. (discussed in state access pattern on lecture 25)
  
  // res_dtype results[nw]; // the results of each thread.
  vector<knn_result> knn_par_result[nw]; // the results of each thread.
  
  long par_time;
   {utimer t_seq("STL Parallel KNN: ", &par_time);

  
  auto compute_chunk = [](vector<point> points, int points_len, interval range,  vector<knn_result> *knn_par_res, int k, int i) {   // function to compute a chunk
         // implement the result collection in different way to see if there is some improvement.
         // Collecting the result this way will cause cache coherent problem. (Check how to improve this)
         // The effect could be negligible. Because the only time the threads are writing to this
         // array is when they are done computing their result but still the result could be noticable if the
         // number of threads are large.(Apparently no significant effect or no effect at all).
        vector<knn_result> par_res_chunk;
        for(int i=range.start;i<range.end;i++){
            knn_result res;res.index = i; 
            res.knn_index = get_knn(points, points_len, i, k);
            par_res_chunk.push_back(res);
        }
        
        // Merging with the global result.
        *knn_par_res = par_res_chunk;
        //mu->lock(); I will be removing this lock.
       // knn_par_result.insert(knn_par_result.end(), par_res_chunk.begin(), par_res_chunk.end());
       // mu->unlock();
    };
  
  
    // split the points into nw ranges.
    for(int i=0; i<nw; i++){
        ranges[i].start = i*delta; // start of the range.
        ranges[i].end = (i != (nw-1) ? (i+1)*delta : points.size()); // end of the range.
    }
    
   for(int i=0; i<nw; i++){
      // Note: For report. (check if pinning the threads to the cores makes an improvement.)
      // During execution of threads, threads may be moved from one
      // core to another. Which also cause data movement from core to another
      // core and overall it will add additional overhead.
      threads.push_back(thread(compute_chunk, points, points_size, ranges[i], &knn_par_result[i], k, i));
      
    } 
    //cout<<"All threads finished"<<endl;
    // join the results
    for(thread& t: threads) {                       
      t.join(); // wait for thread to finish
     }
    }

    print_knn_result(knn_par_result,k,par_time,nw, argv[0], d);

  return 0;
}
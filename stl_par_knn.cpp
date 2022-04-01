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
// mutex
#include <mutex>
#include "src/utimer.cpp"
#include "src/utils.h"
#include "src/stl_knn_seq.h"
#include "src/stl_knn_par.h"
using namespace std;

struct res_dtype{
    // This data type is created to avoid the overhead of
    // false sharing. [ :cat /proc/cpuinfo / cache alignment size : 64 bytes]
  string result;
  string dummy = "dummy";
};


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
  vector<thread> threads; // where the threads are going to be stored.
  vector<interval> ranges(nw); // where the ranges are going to be stored.
  int delta = points.size() / nw; // the delta for each thread.
  
  // This result array is accessed by all the threads but each entry is only accessed(write to it) by one thread.
  // So, its like owner writes / computes access pattern. (discussed in state access pattern on lecture 25)
  // 
   res_dtype results[nw]; // the results of each thread.
  
   auto compute_chunk = [&results](vector<point> points, int points_len, interval range, int k, int i) {   // function to compute a chunk
         // implement the result collection in different way to see if there is some improvement.
         // Collecting the result this way will cause cache coherent problem. (Check how to improve this)
         // The effect could be negligible. Because the only time the threads are writing to this
         // array is when they are done computing their result but still the result could be noticable if the
         // number of threads are large.(Apparently no significant effect or no effect at all).
         results[i].result = knn_par_stl(points, points_len, range, k);
    };

  long par_time;
   {
      utimer t_seq("STL Parallel KNN: ", &par_time);
    // split the points into nw ranges.
    for(int i=0; i<nw; i++){
        ranges[i].start = i*delta; // start of the range.
        ranges[i].end = (i != (nw-1) ? (i+1)*delta : points.size()); // end of the range.
    }
    
    // let threads start, assigning them a function and an amount of work
    for(int i=0; i<nw; i++){
      threads.push_back(thread(compute_chunk, points, points_size, ranges[i], k, i));
      // cout<<"Thread "<<i<<": Range: "<<ranges[i].start<<" "<<ranges[i].end<<endl;
      std::lock_guard<std::mutex> iolock(iomutex);
      std::cout << "Thread #" << i << ": on CPU " << sched_getcpu() << "\n";

    }
      // await thread termination
      //cout<<"All threads finished"<<endl;
     // join the results
    for(thread& t: threads) {                       
      t.join(); // wait for thread to finish
     }

     // collecting results
    for(int i=0; i<nw; i++){
      knn_par_results += results[i].result;
    }
   }
  

  // output the results.
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
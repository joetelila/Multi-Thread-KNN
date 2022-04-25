/*
  Fast Flow -- Parallel For Reduce Implementation of KNN in C++
*/
// Author : Yohannis Kifle Telila.
// Date : 17/02/2022
// Desc : This file contain code for calculating KNN of a 2D points using sequantial
//        patterns using FF library.
// include necessary libraries.
#include <iostream>
#include <thread>
#include <fstream>
#include "src/utimer.cpp"
#include "src/utils.h"
#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>
using namespace std;

int main(int argc, char const *argv[]) {

  if (argc<4) {
        cerr << "use: " << argv[0]  << " nworkers k-value input_file_path -d [optional -d flag to output only nw, k and running time]\n";
        return -1;
    }

  int nw = atoi(argv[1]); 
  int  k = atoi(argv[2]); // k value.
  string filepath = argv[3]; // input file path.];
  // for debugging purposes.
  string d = "";
  if(argv[4] != NULL){
    d = string(argv[4]);
  }

  // where the points are going to be stored [the one read from]
  vector<point> points; // where 2d points are stored
  vector<knn_result> ff_par_results;      // what will store the parallel result.

  long  ff_par_time; // for later speedup print
  points = read2dpoints(filepath);  
  
  int points_len  = points.size();

    // FastFlow parallel execution
    {
    utimer tp("FF parallel reduce: ", &ff_par_time);

    // identity for reduce variable
   vector<knn_result> identity;
    // The parameters for parallel_for_reduce are:
    // ff_par_results - is where the final result will be stored.
    // identity - is the identity for the reduce operation, which is a vector of knn_result.
    // 0 - is the starting index of the loop.
    // points_len - is the ending index of the loop.
    // 1 - is the step size of the loop.
    // 0 - for static partitioning.
    // Lambda for computing KNN followed by Lambda for computing the reduction.
    ff::parallel_reduce(ff_par_results,identity,
                    0, points_len, 
                    1,
                    0,
                    [&](const long i,vector<knn_result> &local_result){
                        knn_result res;res.index = i; 
                        res.knn_index = get_knn(points, points_len, i, k); 
                        local_result.push_back(res);
                     },
                    [](vector<knn_result>& pf_res, const vector<knn_result>& local_res) {
                        // This is the reduction operator.
                        // It is called for each thread, and it receives the partial result
                       pf_res.insert(pf_res.end(), local_res.begin(), local_res.end());
                    }, 
                    nw);
    }
    
    // print results.
    print_knn_result(ff_par_results,k,ff_par_time,nw,argv[0],d);
   
  return 0;
}


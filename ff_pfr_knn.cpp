/*
  Fast Flow -- Parallel For Reduce Implementation of KNN in C++
*/
// Author : Yohannis Kifle Telila.
// Date : 17/02/2022 [my BD]
// Desc : This file contain code for calculating KNN of a 2D points using sequantial
//        patterns using only C++ STL.
// include necessary libraries.

/*
To compile:
 g++ -std=c++17  -g  -I /home/spm2021user/fastflow  -O3 -finline-functions -DNDEBUG -o knn_pf knn_pf.cpp src/utils.cpp src/stl_knn_seq.cpp src/stl_knn_par.cpp -pthread
 
*/

#include <iostream>
#include <thread>
#include <fstream>
#include "src/utimer.cpp"
#include "src/utils.h"
#include "src/stl_knn_seq.h"
#include "src/stl_knn_par.h"
#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>
using namespace std;

int main(int argc, char const *argv[]) {

  if (argc<3) {
        cerr << "use: " << argv[0]  << " nworkers k-value\n";
        return -1;
    }

  int nw = atoi(argv[1]); 
  int  k = atoi(argv[2]); // k value.

  // where the points are going to be stored [the one read from]
  vector<point> points; // where 2d points are stored
  string knn_seq_results = "";      // what will store the sequential result.
  string knn_par_results = "";      // what will store the parallel result.

  string filepath = "data/input_medium.txt";
  long seq_time, par_time; // for later speedup print
  points = read2dpoints(filepath);  
  
    // FastFlow parallel execution
    {
    utimer tp("knn parallel ff computation", &par_time);

    // identity for reduce variable
    string identity = "";
    // no need to instantiate object since this is a one-shot, avoid overhead of creating ParallelForReduce object
    ff::parallel_reduce(knn_par_results,identity,
                    0, points.size(),
                    1,
                    0, // static partitioning
                    [&](const long i,string &local_result){
                        local_result += to_string(i)+": "+get_knn_par(points, i, k);
                        local_result += "\n";
                    },
                    [](string& pf_res, const string& local_res) {
                        // This is the reduction operator.
                        // It is called for each thread, and it receives the partial result
                        // and the identity value.
                        pf_res+=local_res;
                    }, 
                    nw);
    // no need to sort because of static partitioning
}
 // writing the results to a file.
  ofstream ff_res_writer("results/ff_par_res.txt");
  ff_res_writer << knn_par_results;
  ff_res_writer.close();
  cout<<"Result has been written to results/ff_par_res.txt"<<endl;
  return 0;
}


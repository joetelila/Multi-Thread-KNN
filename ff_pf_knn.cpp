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
  string ff_par_results = "";      // what will store the parallel result.

  long  ff_par_time; // for later speedup print
  points = read2dpoints(filepath);  
  
    // FastFlow parallel execution
    {
    utimer tp("FF parallel reduce: ", &ff_par_time);

    // identity for reduce variable
    string identity = "";
    // no need to instantiate object since this is a one-shot, avoid overhead of creating ParallelForReduce object
    ff::parallel_reduce(ff_par_results,identity,
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
  if (string(d)=="-d"){
      cout<<"[nw]: "<<nw<<"  [k]: "<<k<<"  [time]: "<<ff_par_time<<"\n";
  }else{
      // writing the results to a file.
    ofstream ff_res_writer("results/ff_par_res.txt");
    ff_res_writer << ff_par_results;
    ff_res_writer.close();
    cout<<"FF Parallel for reduce, Finished in "<<ff_par_time<<" ms.\n";
    cout<<"Result has been written to results/ff_par_res.txt"<<endl;
  }

  return 0;
}


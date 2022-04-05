/*
  C++ openMp implementation of parallel knn.
*/
// Author : Yohannis Kifle Telila.
// Date : 17/02/2022
// Desc : This file contain code for calculating KNN of a 2D points using sequantial
//        patterns using only C++ STL.


// include necessary libraries.
#include <iostream>
#include <omp.h>
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
  vector<string> results(nw);    // what will store the result.
  points = read2dpoints(filepath);  
  int points_len  = points.size();
  string res = "";
  long openmp_time;
  // Computing knn in sequantial.
  {
     utimer t_seq("openMp Parallel KNN", &openmp_time);
    
      #pragma omp parallel for schedule(static) num_threads(nw) shared(points, results, points_len, k) private(res)
      for(int i=0;i<points_len;i++){
          res = get_knn(points, points_len, i, k);
          int id = omp_get_thread_num();
          // optimize this.
          results[id] += (to_string(i)+": "+ res+"\n");
       }
      // collecting results.
    for(int i=0;i<nw;i++){
      finalResult+= results[i];
    }
  }
  
  // writing the results to a file.
  // Note : if you use -d, it wont write the results to a file.
  if (string(d)=="-d"){   
      cout<<"[nw]: "<<nw<<" [k]: "<<k<<" [time]: "<<openmp_time<<"\n";
  }else{
      ofstream openMp_res_writer("outputs/openMp_par_res.txt");
      openMp_res_writer << finalResult;
      openMp_res_writer.close();
      cout<<"openMp Par, Finished in "<<openmp_time<<" ms.\n";
      cout<<"Result has been written to outputs/openMp_par_res.txt"<<endl;
  }
  
  return 0;
}


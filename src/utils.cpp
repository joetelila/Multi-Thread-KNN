// Author: Yohannis Kifle Telila.
// Date : 17/02/2022 [my BD]
// Desc : This file contains utility codes used by other files.

// import necessary libraries.
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include<vector>
#include<fstream>
#include <queue>
#include "utils.h"
using namespace std;

/*
bool checkfor_error(){
  // code here.
}

*/

vector<string> stringSplitter(string s){

  vector<string> res;
  istringstream iss(s);
  for(string s; iss >> s; )
      res.push_back(s);
  return res;
}

bool compare_point_index(knn_result p1, knn_result p2)
{
    return (p1.index < p2.index);
}


vector<point> read2dpoints(string filepath){
  // Reads 2D points from a file.
  // filename : the file name.
  // return : a vector of 2D points.

    ifstream fstream; // input file stream.
    point p; // point struct.
    vector<point> points; // stores the 2D points.
    
    fstream.open(filepath);
    // after open, check f and throw std::system_error with the errno
    if (!fstream)
        throw std::system_error(errno, std::system_category(), "failed to open "+filepath);

    
    if(fstream.is_open()){
        string line;
        vector<string> res;
        while(getline(fstream,line)){
          res = stringSplitter(line);
          p.x = stod(res[0]);
          p.y = stod(res[2]);
          points.push_back(p);
         // cout<<res[0]<<" "<<res[1]<<endl;
      }}
      fstream.close();
      return points;
}

float measure_euclidean_distance(point p1, point p2){
  //  Measures the distance between two points.
  //  p1 : the first point.
  //  p2 : the second point.
  return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

float measure_euclidean_distance_without_square_root(point p1, point p2){
  //  Measures the distance between two points without square root.
  //  p1 : the first point.
  //  p2 : the second point.
  return pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2);
}

vector<int> get_knn(vector<point> points, int points_size, int i, int k){
    // return k nearest neighbors of point i.
    // points : the 2d points.
    // i : the point of interest.
    // k : the number of neighbors.
    // return : a string of k nearest neighbors.
    vector<int> knn_res;
    kresult temp_res;
    priority_queue<kresult, vector<kresult>, cmpFunction> kneighbors;
    double distance;
    // Would it be a good idea to parallelize this aswell?
    for(int j = 0; j < points_size; j++){
        if(j != i){
            // This for loop can be vectorized. measure_euclidean_distance method call might prevent from vectorization.
            distance = measure_euclidean_distance(points[i], points[j]);
            temp_res.index = j;
            temp_res.distance = distance;
            if (kneighbors.size() < k){
                kneighbors.push(temp_res);
            }
            if (kneighbors.top().distance > temp_res.distance) {
                kneighbors.pop();
                kneighbors.push(temp_res);
            }
        }
    }
    // prepare the result. change to forloop so that it can be parallelized.
    // converted a while loop implementation to a for loop.(for vectorization**)
    for(int j = 0; j < k; j++){
        knn_res.push_back(kneighbors.top().index);
        kneighbors.pop();
    }
    


    return knn_res;
}


void print_knn_result(vector<knn_result> knn_results, int k,long time, int nw, string file, string d){
    // print the final KNN result.
    // knn_results : the final KNN result.
   
    // print output for debugging. 
    if (string(d)=="-d"){
       cout<<"[nw]: "<<nw<<"  [k]: "<<k<<"  [time]: "<<time<<"\n";
     return;
    }

    // print output for submission.
    string knn_res = "";
    for(int i = 0; i < knn_results.size(); i++){
        string temp = "";
        for(int j=0; j<knn_results[i].knn_index.size(); j++){
            temp = to_string(knn_results[i].knn_index[j]) +" "+ temp + " ";
        }
        knn_res = knn_res + to_string(knn_results[i].index)+ ": " + temp + "\n";
      }
     
      ofstream stl_res_writer("outputs/"+file.substr(6)+".txt");
      stl_res_writer << knn_res;
      stl_res_writer.close();
      cout<<file.substr(6)+ ", finished in "<<time<<" ms.\n";
      cout<<"Result has been written to outputs/"+file.substr(6)+".txt"<<endl;
  
  return;

}

void print_knn_result(vector<knn_result> knn_results[], int k,long time, int nw, string file, string d){
    // print the final KNN result.
    // knn_results : the final KNN result.
   
    // print output for debugging. 
    if (string(d)=="-d"){
       cout<<"[nw]: "<<nw<<"  [k]: "<<k<<"  [time]: "<<time<<"\n";
     return;
    }

    // print output for submission.
    string knn_res = "";

    for(int k=0; k<nw; k++){

      for(int i = 0; i < knn_results[k].size(); i++){
        string temp = "";
        for(int j=0; j<knn_results[k][i].knn_index.size(); j++){
            temp = to_string(knn_results[k][i].knn_index[j]) +" "+ temp + " ";
        }
        knn_res = knn_res + to_string(knn_results[k][i].index)+ ": " + temp + "\n";
      }
      
    }
     
      ofstream stl_res_writer("outputs/"+file.substr(6)+".txt");
      stl_res_writer << knn_res;
      stl_res_writer.close();
      cout<<file.substr(6)+ ", finished in "<<time<<" ms.\n";
      cout<<"Result has been written to outputs/"+file.substr(6)+".txt"<<endl;
  
  return;

}

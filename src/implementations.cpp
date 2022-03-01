#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include "utils.h"

using namespace std;

struct kresult{
    // a struct for storing the result of kNN.
  int index;
  float distance;
};

class cmpFunction{
    // compare function for priority queue.
 public:
   bool operator()(const kresult& a, const kresult& b)
   {
        return a.distance < b.distance;
   }
};

string get_knn(vector<point> points, int i, int k){
    // return k nearest neighbors of point i.
    // points : the 2d points.
    // i : the point of interest.
    // k : the number of neighbors.
    // return : a string of k nearest neighbors.
    string knn = "";
    kresult temp_result;
    priority_queue<kresult, vector<kresult>, cmpFunction> kneighbors;
    double distance;
    for(int j = 0; j < points.size(); j++){
        if(j != i){
            distance = measure_euclidean_distance(points[i], points[j]);
            temp_result.index = j;
            temp_result.distance = distance;
            if (kneighbors.size() < k){
                kneighbors.push(temp_result);
            }
            else if (kneighbors.top().distance > temp_result.distance) {
                kneighbors.pop();
                kneighbors.push(temp_result);
            }
        }
    }
    // prepare the result.
    while (!kneighbors.empty() ) {
        knn = to_string(kneighbors.top().index) +" "+ knn  + " ";
        kneighbors.pop();
    }
    return knn;
}

void stl_knn_sequential(vector<point> points, int k){
    // Calculate k nearest neighbors of each point sequentially.
    // points : the 2d points.
    // k : the number of neighbors.
    // return : nothing.
  string result = "";
  for(int i=0;i<points.size();i++){
       result = get_knn(points, i, k);
       cout<<i<<": "<<result<<endl;
  }
}

void stl_knn_par(vector<point> points, int k){
 cout<<"KNN Parallel: "<<k<< endl;
}

void ff_knn_par(vector<point> points, int k){
 cout<<"FF KNN Parallel: "<<k<< endl;
}

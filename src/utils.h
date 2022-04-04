// Author: Yohannis Kifle Telila.
// Date : 17/02/2022 [my BD]
// Desc : This file contains utility codes used by other files.

// import necessary libraries.
#include <math.h>
#include <string>
#include <sstream>
#include<vector>
#include<fstream>
using namespace std;

/*
bool checkfor_error();

bool checking_for_successful_parameter_provide();

void write2d_pooints(); */

struct point{
  double x;
  double y;
};

struct interval{
    // a struct for storing the range of points.
  int start;
  int end;
};

struct res_dtype{
    // This data type is created to avoid the overhead of
    // false sharing. [ :cat /proc/cpuinfo / cache alignment size : 64 bytes]
  string result;
  string dummy = "dummy";
};

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


vector<string> stringSplitter(string s);

vector<point> read2dpoints(string filename);

float measure_euclidean_distance(point p1, point p2);

float measure_euclidean_distance_without_square_root(point p1, point p2);

string get_knn(vector<point> points, int points_size, int i, int k);
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
using namespace std;

struct point{
  double x;
  double y;
};

struct range{
    // a struct for storing the range of points.
  int start;
  int end;
};


/*
bool checkfor_error(){
  // code here.
}

bool checking_for_successful_parameter_provide(){

 // code here.

}

void write2d_pooints(){

 // code here.

} */

vector<string> stringSplitter(string s){

  vector<string> res;
  istringstream iss(s);
  for(string s; iss >> s; )
      res.push_back(s);
  return res;
}


vector<point> read2dpoints(string filepath){
  // Reads 2D points from a file.
  // filename : the file name.
  // return : a vector of 2D points.

    ifstream fstream; // input file stream.
    point p; // point struct.
    vector<point> points; // stores the 2D points.
    fstream.open(filepath);
    
    if(fstream.is_open()){
        string line;
        vector<string> res;
        while(getline(fstream,line)){
          res = stringSplitter(line);
          p.x = stod(res[0]);
          p.y = stod(res[1]);
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

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

struct interval{
    // a struct for storing the range of points.
  int start;
  int end;
};

string get_knn_par(vector<point> points, int i, int k);
string knn_par_stl(vector<point> points, interval range, int k);

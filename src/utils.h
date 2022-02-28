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

struct point{
  double x;
  double y;
};

/*
bool checkfor_error();

bool checking_for_successful_parameter_provide();

void write2d_pooints(); */

vector<string> stringSplitter(string s);

vector<point> read2dpoints(string filename);

float measure_euclidean_distance(point p1, point p2);

float measure_euclidean_distance_without_square_root(point p1, point p2);
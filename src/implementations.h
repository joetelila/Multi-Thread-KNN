#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

string get_knn(vector<point> points, int i, int k);
void stl_knn_sequential(vector<point> points, int k);

void stl_knn_par(vector<point> points, int k);

void ff_knn_par(vector<point> points, int k);

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

string get_knn(vector<point> points, int points_size, int i, int k);
string stl_knn_sequential(vector<point> points, int points_len, int k);


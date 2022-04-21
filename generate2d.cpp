// Author: Yohannis Kifle Telila.
// Date : 28/03/2022
// Desc : This file contains utility codes to generate 2D points.
 
// include necessary libraries.
#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
using namespace std;

void generate_2d_points(float start, float end, int seed, int amount, string file_name){

    ofstream randWriter;
    randWriter.open ("data/"+file_name+".txt");
    random_device rand;
    default_random_engine eng(rand());
    eng.seed(seed);
    uniform_real_distribution<> distr(start, end);

    for (int n = 0; n < amount; ++n) {
        randWriter << setprecision(6)<< distr(eng) << " , "<<distr(eng)<<endl;
    }
    randWriter.close();

    return;
}

int main(int argc, char const *argv[]){
     
    if (argc<6) {
        cerr << "use: " << argv[0]  << " start end seed amount file_name\n";
        return -1;
    }

    float start = atof(argv[1]);
    float end = atof(argv[2]);
    int seed = atoi(argv[3]);
    int amount = atoi(argv[4]);
    string file_name = argv[5];

    generate_2d_points(start, end, seed, amount, file_name);
    
    std::cout<<"File has been generated and stored in data/"<<file_name<<".txt"<<endl;

    return EXIT_SUCCESS;
}

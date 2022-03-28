# Multi-Thread-KNN

Implementation of KNN algorithm using STL of c++  and FastFlow library.

## Description

Given a set of points in a 2D space, we require to compute in parallel for each one of the points in the set
of points the set of k closest points. Point i is the point whose coordinates are listed in line i in the file. The
input of the program is a set of floating-point coordinates (one per line, comma separated) and the output
is a set of lines each hosting a point id and a list of point ids representing its KNN set ordered with respect
to distance.


## Getting Started

### Dependencies

* Download and install Docker if you dont alredy have it.

### Installing

* Clone repo repo.
```
git clone https://github.com/joetelila/Multi-Thread-KNN.git
```
* Build the docker image provided <a href='https://github.com/joetelila/Multi-Thread-KNN/blob/main/Dockerfile'>here</a>
```
docker build .
```
* After starting the docker container run the make command.
```
make
```

### Executing program

* After the make command you would find 5 executable files.
#### Generating 2D points
* generate2d : This code will generate 2D points conditioned on provided parameters. All parameters are important. The generated 
               points will be stored under the <b>data</b> folder.
 
```
./generate2d [start] [end] [seed] [amount] [file_name]
Eg: ./generate2d 0 100 200 10000 "input_10k_s200"  // no need to write file extension.
```

#### Running C++ Sequential program
* stl_seq_knn : This executable contain a code to run the problem sequentially. The result of this code will be stored under <b>results/stl_seq_res.txt</b>. To run use the following command
 
```
./stl_seq_knn [k-value] [input_file_path] -d   // -d is optional flag for debuggin and output formatting.
Eg: ./stl_seq_knn 4 data/input_10k_s200.txt
```

#### Running C++ Parallelized program
* stl_par_knn : This executable contain a code to run the problem using multiple threads(in parallel). The result of this code will be stored under <b>results/stl_par_res.txt</b>. To run use the following command
 
```
./stl_par_knn [nw] [k-value] [input_file_path] -d   // nw - number of workers. -d  is optional flag for debuggin and output formatting.
Eg: ./stl_par_knn 4 4 data/input_10k_s200.txt
```

#### Running C++ Parallelized program using Fastflow parallel for.
* ff_pf_knn : This executable contain parrallel implementation of the problem using <a href="https://github.com/fastflow/fastflow">FastFlow</a>. The result of this code will be stored under <b>results/ff_par_res.txt</b>. To run use the following command
 
```
./ff_pf_knn [nw] [k-value] [input_file_path] -d   // nw - number of workers. -d  is optional flag for debuggin and output formatting.
Eg: ./ff_pf_knn 4 4 data/input_10k_s200.txt
```

#### Running C++ Parallelized program using openMP.
* openmp_par_knn : This executable contain parrallel implementation of the problem using <a href="https://www.openmp.org/">openMP</a>. The result of this code will be stored under <b>results/openMP_par_res.txt</b>. To run use the following command
 
```
./openmp_par_knn [nw] [k-value] [input_file_path] -d   // nw - number of workers. -d  is optional flag for debuggin and output formatting.
Eg: ./openmp_par_knn 4 4 data/input_10k_s200.txt
```

## License

MIT

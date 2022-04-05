#!/bin/bash
# Shell script to execute the test

# check correct number of parameters
if [ "$#" -ne 2 ]; then
    echo "Usage: ./executeTest.sh [k-value, Eg. 25] [total runs, Eg. 2]"
    exit 2
fi

k=$1
totalRuns=$2

allThreads=(1 2 4 8 16 32 64 128 256)
inputFiles=("input_20k_s123.txt")  #"input_50k_s456.txt" "input_100k_s789.txt") 

echo "k-value: $k"
echo "Total runs: $totalRuns"
# Running sequential version
#----------------------------------------------------------------------------------------------------------------------
echo "---------------Running sequential version---------------"
for inputFile in ${inputFiles[@]}
do
  for ((i=0;i<$totalRuns; i++)); do ./bin/stl_seq_knn $k data/$inputFile -d ; done |  awk '{sum+=$4} END {printf "[STL Sequence]: [ "(sum/NR)/1000000 " sec"}'; echo "]  ["$inputFile"]";
done


# Running parallel version
echo "---------------Running STL CPP parallel version---------------"
for inputFile in ${inputFiles[@]}
do
for nw in ${allThreads[@]}
do  
     for ((i=0;i<$totalRuns; i++)); do ./bin/stl_par_knn $nw $k data/$inputFile -d ; done |  awk '{sum+=$6} END {printf "[STL Par]: [ "(sum/NR)/1000000 " sec"}'; echo "]  ["$inputFile"]" "[ "$nw" ]";
    done
    echo " "
done

# Running parallel version
echo "---------------Running FF parallel for version---------------"
for inputFile in ${inputFiles[@]}
do
for nw in ${allThreads[@]}
do  
     for ((i=0;i<$totalRuns; i++)); do ./bin/ff_pf_knn $nw $k data/$inputFile -d ; done |  awk '{sum+=$6} END {printf "[FF Par]: [ "(sum/NR)/1000000 " sec"}'; echo "]  ["$inputFile"]" "[ "$nw" ]";
    done
    echo " "
done

# Running parallel version
echo "---------------Running openMP parallel version---------------"
#echo "Running parallel version"
for inputFile in ${inputFiles[@]}
do
for nw in ${allThreads[@]}
do  
     for ((i=0;i<$totalRuns; i++)); do ./bin/openmp_par_knn $nw $k data/$inputFile -d ; done |  awk '{sum+=$6} END {printf "[openMp Par]: [ "(sum/NR)/1000000 " sec"}'; echo "]  ["$inputFile"]" "[ "$nw" ]";
    done
    echo " "
done
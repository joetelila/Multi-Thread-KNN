#!/bin/bash
# Shell script to execute the test
allThreads=(1 2 4 8 16 32 64 128 256)
inputFiles=("input_10k_s100.txt" "input_50k_s200.txt" "input_100k_s300.txt") 
totalRuns=6
# Running sequential version
#----------------------------------------------------------------------------------------------------------------------
echo "---------------Running sequential version---------------"
for inputFile in ${inputFiles[@]}
do
  for ((i=0;i<$totalRuns; i++)); do ./stl_seq_knn 10 data/$inputFile -d ; done |  awk '{sum+=$4} END {printf "[STL Sequence]: [ "(sum/NR)/1000000 " sec"}'; echo "]  ["$inputFile"]";
done


# Running parallel version
echo "---------------Running STL CPP parallel version---------------"
for inputFile in ${inputFiles[@]}
do
for nw in ${allThreads[@]}
do  
     for ((i=0;i<$totalRuns; i++)); do ./stl_par_knn $nw 10 data/$inputFile -d ; done |  awk '{sum+=$6} END {printf "[STL Par]: [ "(sum/NR)/1000000 " sec"}'; echo "]  ["$inputFile"]" "[ "$nw" ]";
    done
    echo " "
done

# Running parallel version
echo "---------------Running FF parallel for version---------------"
for inputFile in ${inputFiles[@]}
do
for nw in ${allThreads[@]}
do  
     for ((i=0;i<$totalRuns; i++)); do ./ff_pf_knn $nw 10 data/$inputFile -d ; done |  awk '{sum+=$6} END {printf "[FF Par]: [ "(sum/NR)/1000000 " sec"}'; echo "]  ["$inputFile"]" "[ "$nw" ]";
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
     for ((i=0;i<$totalRuns; i++)); do ./openMp_par_knn $nw 10 data/$inputFile -d ; done |  awk '{sum+=$6} END {printf "[openMp Par]: [ "(sum/NR)/1000000 " sec"}'; echo "]  ["$inputFile"]" "[ "$nw" ]";
    done
    echo " "
done
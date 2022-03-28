#!/bin/bash
# Shell script to execute the test
allThreads=(1 2 4 8 16 32 64 128 256)
inputFiles=("input_10k_s100.txt" "input_50k_s200.txt" "input_100k_s300.txt")
totalRuns=10
# Running sequential version
#----------------------------------------------------------------------------------------------------------------------
echo "---------------Running sequential version---------------"
for inputFile in ${inputFiles[@]}
do
seq_time_sum=0
for ((n=0;n<totalRuns;n++))
do
    runtime=$(./stl_seq_knn 10 data/$inputFile -d | awk '{print $4}') 
    seq_time_sum=`expr $seq_time_sum + $runtime`
done
seq_time_avg=`expr $seq_time_sum / $totalRuns`
echo "[STL CPP Sequential], [$inputFile], [$totalRuns runs]: $seq_time_avg"
done

# Running parallel version
echo "---------------Running STL CPP parallel version---------------"
#echo "Running parallel version"
for inputFile in ${inputFiles[@]}
do
par_time_sum=0
for nw in ${allThreads[@]}
do  
    for ((i=0;i<totalRuns;i++))
    do
        runtime=$(./stl_par_knn $nw 10 data/$inputFile -d | awk '{print $6}') 
        par_time_sum=`expr $par_time_sum + $runtime`
    done
     echo "[STL CPP Parallel] , [$inputFile],[$nw threads] [$totalRuns runs] : `expr $par_time_sum / $totalRuns`"
done
done

# Running parallel version
echo "---------------Running FF parallel for version---------------"
#echo "Running parallel version"
for inputFile in ${inputFiles[@]}
do
par_time_sum=0
for nw in ${allThreads[@]}
do  
    for ((i=0;i<totalRuns;i++))
    do
        runtime=$(./ff_pf_knn $nw 10 data/$inputFile -d | awk '{print $6}') 
        par_time_sum=`expr $par_time_sum + $runtime`
    done
     echo "[FF Parallel for] , [$inputFile],[$nw threads] [$totalRuns runs] : `expr $par_time_sum / $totalRuns`"
done
done

# Running parallel version
echo "---------------Running openMP parallel version---------------"
#echo "Running parallel version"
for inputFile in ${inputFiles[@]}
do
par_time_sum=0
for nw in ${allThreads[@]}
do  
    for ((i=0;i<totalRuns;i++))
    do
        runtime=$(./openmp_par_knn $nw 10 data/$inputFile -d | awk '{print $6}') 
        par_time_sum=`expr $par_time_sum + $runtime`
    done
     echo "[openMP Parallel] , [$inputFile],[$nw threads] [$totalRuns runs] : `expr $par_time_sum / $totalRuns`"
done
done
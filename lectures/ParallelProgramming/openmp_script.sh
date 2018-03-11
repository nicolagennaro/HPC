#!/bin/bash

n_times=4
n_points=1000000000 # 1 billion
filename="openmp"
#n_points=100000000   # 100 millions

#export OMP_PLACES=cores

export OMP_PLACES=cores
export OMP_PROC_BIND=close


#for threads in `seq 20`; do
for threads in 1 2 3 4; do
    echo "running with $threads threads"
    for n in `seq $n_times`;do
	printf "$threads\t" >> $filename$threads.dat
	export OMP_NUM_THREADS=$threads
	/usr/bin/time -p ./pi_openmp $n_points 2>&1  | grep "real" | \
	    awk '{print $2}' >> $filename$threads.dat
    done
done


for files in $filename[0-9]*.dat; do
    echo "reading file $files"
    ./mean_var.awk $files >> plot.dat
done

echo
echo
echo "FINAL FILE:"
cat plot.dat

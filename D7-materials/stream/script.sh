#!/bin/bash

make


if [ -e hardware.txt ]; then
    rm hardware.txt
    #echo "hardware.txt removed"
fi

# echo "numactl --hardware" >> hardware.txt

numactl --hardware >> hardware.txt

if [ -e stream00.txt ]; then
    rm stream00.txt
    #echo "stream.txt removed"
fi

#echo "Bandwidth for stream.x"
for i in `seq 1 3`; do
    numactl --cpunodebind 0 --membind 0 ./stream.x | grep Triad \
	| awk '{print $2}' >> stream00.txt
done

if [ -e stream01.txt ]; then
    rm stream01.txt
    echo "streamOMP.txt removed"
fi

for i in `seq 1 3`; do
    numactl --cpunodebind 0 --membind 1 ./stream.x | grep Triad \
	| awk '{print $2}' >> stream01.txt
done

if [ -e filethreads00.txt ]; then
    rm filethreads00.txt
fi

if [ -e filethreads01.txt ]; then
    rm filethreads01.txt
fi

#echo "Bandwidth changing number of threads"
for threads in `seq 1 10`; do
    export OMP_NUM_THREADS=$threads
    printf "$threads\t" >> filethreads00.dat
    numactl --cpunodebind 0 --membind 0 ./stream_omp.x | grep Triad \
	| awk '{print $2}' >> filethreads00.dat
done


for threads in `seq 1 10`; do
    export OMP_NUM_THREADS=$threads
    printf "$threads\t" >> filethreads01.dat
    numactl --cpunodebind 0 --membind 1 ./stream_omp.x | grep Triad \
	| awk '{print $2}' >> filethreads01.dat
done

#!/bin/bash

cd ex1/new

pi_times=20000000
echo "PI TIMES: $pi_times"
means=5
echo "means: $means"


echo "loading dependencies"
module load openmpi
echo "DONE"

echo removing old files
rm weak*
rm strong*
rm serial*

echo compiling pi
gcc -o pi pi.c


echo compiling mpi_pi
mpicc -o mpi_pi mpi_pi.c



echo
echo SERIAL PI
echo

for timmes in `seq $means`; do
    /usr/bin/time -p ./pi $pi_times  2>>serial.txt          # 2>> timespi.txt
done



echo
echo STRONG SCALING
echo



for procs in 1 2 4 8 16 20; do
    num=$(($pi_times/$procs))
    # echo "num: " $num
    # echo "procs: $procs   num: $num" >> strong.txt
    for timmes in `seq $means`; do
	printf "$procs\t" >> strong$procs.dat
	/usr/bin/time -p  mpirun -np ${procs} mpi_pi ${num}  2>&1 | grep "real" | \
	    awk '{print $2}' >> strong$procs.dat
    done
done



echo
echo WEAK SCALING
echo


for procs in 1 2 4 8 16 20; do

    for times in `seq $means`; do
	printf "$procs\t" >> weak$procs.dat
	/usr/bin/time -p mpirun -np ${procs} mpi_pi ${pi_times}  2>&1  | grep "real" | \
	    awk '{print $2}' >> weak$procs.dat
    done
done


for files in strong[0-9]*.dat; do
    ./mean_var.awk $files >> strongplot.dat
done

for files in weak[0-9]*.dat; do
    ./mean_var.awk $files >> weakplot.dat
done


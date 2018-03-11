#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>



int main(int argc, char *argv[]){
int size, rank;
long n_points, n, i;
double w, x, sum, pi, start;

 if(argc != 2){
   printf("Usage: ./a.out N_POINTS\n");
   exit(1);
 }

n_points = atoi(argv[1]);

sum = 0.0;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);

// every process compute the part of the integral from start
// using N_STEP/size rectangles

if( rank != (size-1) ) 
   n = n_points/size;
else
   n = n_points/size + n_points % size;


start = (1.0 / (double) size) * rank;
w = 1.0 / (double) n_points;

printf("proc %d, starting point %f, step %f, n times %ld\n", rank, start, w, n);

for( i=1; i<=n; i++){
	x = start + w*( i - 0.5);
	sum += 4.0 / (1.0 + x*x);
}

sum *= w;

printf("proc %d, sum %f\n", rank, sum);

MPI_Reduce( &sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );

if( rank == 0 )
	printf("proc %d, PI: %.10lf\n", rank, pi);	

MPI_Finalize();

return 0;
}

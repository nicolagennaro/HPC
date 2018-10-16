#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>




void print_mat(double *p, int d){
int i, j;

 for(i=0; i<d; i++){
   for(j=0; j<d; j++)
       printf("%.2lf\t", p[d*i + j]);
       	
   printf("\n");
 }

}








int main(int argc, char *argv[]){
 int size, rank;
 double *A,*B,*C, *send_buf, *recv_buf;
 int mat_size;
 int N_loc, i, j, k, count;
 double tmp;
 double *Atot, *Btot, *Ctot;

 FILE *fp;
 size_t written; 


 if(argc < 2){
   printf("USAGE: %s mat_size\n", argv[0]);
   exit(1);
 }


 mat_size = atoi(argv[1]);

 
 
 fp = fopen("matrix.bin","w");
 if( fp == NULL ){
   printf("proc %d: cannot open file\n", rank);
   exit(1);
 }


 MPI_Init(&argc, &argv);
 MPI_Comm_size(MPI_COMM_WORLD, &size);
 MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  

 
 if(rank==size-1){
    N_loc = mat_size - mat_size/size*(size-1);
    printf("proc %d proc_size %d\n", rank, N_loc);
 }
 else{
    N_loc = mat_size/size;
    printf("proc %d proc_size %d\n", rank, N_loc);
 }



A = (double*) malloc(mat_size * N_loc * sizeof(double) );
B = (double*) malloc(mat_size * N_loc * sizeof(double) );
C = (double*) malloc(mat_size * N_loc * sizeof(double) );

send_buf = (double*) malloc(N_loc * N_loc * sizeof(double) );
recv_buf = (double*) malloc(mat_size * N_loc * sizeof(double) );


 
// initialize A, B
for(i=0; i< mat_size*N_loc; i++)
	A[i] = (double) i + rank*mat_size*N_loc;
	
for(i=0; i< mat_size*N_loc; i++)
	B[i] = (double) i + rank*mat_size*N_loc;


if(rank == 0){
	Atot = (double*) malloc (mat_size*mat_size*sizeof(double) );
	Btot = (double*) malloc (mat_size*mat_size*sizeof(double) );
	Ctot = (double*) malloc (mat_size*mat_size*sizeof(double) );
}


// send to proc 0
MPI_Gather(A, mat_size * N_loc, MPI_DOUBLE, Atot, mat_size * N_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
MPI_Gather(B, mat_size * N_loc, MPI_DOUBLE, Btot, mat_size * N_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

if(rank == 0 && mat_size <= 16 ){
        printf("MATRIX A\n");
	print_mat(Atot, mat_size);
	printf("MATRIX B\n");
	print_mat(Btot, mat_size);
}


// core cycle
for(count=0; count<size; count++){
	// set the buffer as function of count
	for( i=0; i<N_loc; i++){ 		// rows
		for( j=0; j< N_loc; j++){ 	// index elements
			send_buf[N_loc*i + j] = B[mat_size*i + count*N_loc + j];
		}
	}


	// gather all the send_buf into recv_buf
	MPI_Allgather(send_buf, (N_loc*N_loc), MPI_DOUBLE, recv_buf, (N_loc * N_loc), MPI_DOUBLE, MPI_COMM_WORLD);

	// multiply A and the recv_buf, store in C
	for( i=0; i<N_loc; i++){ 		// rows
		for( j=0; j< N_loc; j++){ 	// cols
			tmp = 0.0;
			for(k=0; k<mat_size; k++){
				tmp += A[mat_size*i + k] * recv_buf[ j + k*N_loc]; // no mat*k + j
			}
			C[ mat_size*i + count*N_loc + j ] = tmp;
		}
	}
	
} // end count


// send to proc 0
MPI_Gather(C, mat_size * N_loc, MPI_DOUBLE, Ctot, mat_size * N_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

 if(rank == 0 && mat_size<=16 ){
	printf("mat C\n");
	print_mat(Ctot, mat_size);
}

// parallel writing binary file

 fseek(fp, rank*N_loc*mat_size*sizeof(double), SEEK_SET);

 written = fwrite(C, sizeof(double), N_loc*mat_size, fp);

 //printf("proc %d: written %ld\n", rank, written);



 MPI_Finalize();

 fclose(fp);
 
return 0;
}

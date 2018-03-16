#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


/*
void init_A(double *p, int np, int size){
int i;


}
*/


// void set_send_buffer(double *p)
void print_mat(double *p, int d){
int i, j;
	for(i=0; i<d; i++){
		for(j=0; j<d; j++){
			printf("%.0lf\t", p[d*i + j]);
		}
		printf("\n");
	}

}








int main(int argc, char *argv[]){
 int size=1, rank=0;
 double *A,*B,*C, *send_buf, *recv_buf;
 // char fileA[20], fileB[20];
 int mat_size;
 int N_loc, i, j, k, count;
 double tmp;
 double *Atot, *Btot, *Ctot;

 FILE *fpA, *fpB;
 



 MPI_Init(&argc, &argv);
 MPI_Comm_size(MPI_COMM_WORLD, &size);
 MPI_Comm_rank(MPI_COMM_WORLD, &rank);

 // open file and set N_loc
 if(argc < 2){
   printf("USAGE: %s mat_size", argv[0]);
   exit(1);
 }

 /* if( strlen(argv[1]) > 20 ){ */
 /*    printf("fileA name too long\n"); */
 /*    exit(1); */
 /*  } */

 /*  strcpy(fileA, argv[1]); */

 /*  printf("file A: %s\n", fileA); */

 /*  fpA = fopen(fileA, "r"); */

 /*  if(fpA==NULL){ */
 /*    printf("cannot open %s\n", fileA); */
 /*    exit(1); */
 /*  } */

 /* if( strlen(argv[2]) > 20 ){ */
 /*    printf("fileB name too long\n"); */
 /*    exit(1); */
 /*  } */

 /*  strcpy(fileB, argv[2]); */

 /*  printf("file B: %s\n", fileB); */

 /*  fpA = fopen(fileB, "r"); */

 /*  if(fpA==NULL){ */
 /*    printf("cannot open %s\n", fileB); */
 /*    exit(1); */
 /*  } */

  
 mat_size = atoi(argv[1]);

 
 if(rank==size-1){
    N_loc = mat_size - mat_size/size*(size-1);
    printf("proc %d proc_size %d\n", rank, N_loc);
 }
 else{
    N_loc = mat_size/size;
    printf("proc %d proc_size %d\n", rank, N_loc);
 }


 // printf("MAT_DIM / np = %d\n", MAT_DIM / size);

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



MPI_Gather(A, mat_size * N_loc, MPI_DOUBLE, Atot, mat_size * N_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
MPI_Gather(B, mat_size * N_loc, MPI_DOUBLE, Btot, mat_size * N_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

if(rank == 0){
	print_mat(Atot, mat_size);
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


MPI_Gather(C, mat_size * N_loc, MPI_DOUBLE, Ctot, mat_size * N_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
if(rank == 0){
	printf("mat C\n");
	print_mat(Ctot, mat_size);
}

MPI_Finalize();
  
return 0;
}

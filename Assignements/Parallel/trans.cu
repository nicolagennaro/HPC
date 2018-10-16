#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define NUM_THREADS 64

typedef double MYTYPE;


__global__ void mat_trans(MYTYPE* a, MYTYPE* at, int size){
  // MYTYPE tmp;

  // threadIdx from 0 to NUM_THREADS
  // blockIdx = (size*size + NUM_THREADS)/NUM_THREADS
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  int row = idx/size;
  int col = idx % size;

  if( idx < size*size ){
    at[ col*size + row ] = a[ row*size + col ];
  }
}



void mat_print(MYTYPE *m, int dim){
  int i, j;
  printf("\n");
  for(i=0; i<dim; i++){
	 for(j=0; j<dim; j++)
	 	  printf( "%.3lf\t", m[i*dim + j] );
	printf("\n");
  }
  printf("\n");
}




int main(int argc, char *argv[]){

MYTYPE *h_a, *h_at;
MYTYPE *d_a, *d_at;
int dim, i;
size_t m_size;

if( argc != 2){
 printf("\n");
 printf("usage: a.out MAT_DIM\n\n");
 exit(1);
}

dim = atoi(argv[1]);
m_size = dim*dim * sizeof(MYTYPE);

h_a = (MYTYPE*) malloc( m_size );
h_at = (MYTYPE*) malloc( m_size );

for(i=0; i<dim*dim; i++)
	 h_a[i] = (MYTYPE)( rand() % 10 );

if( dim <= 10)
    mat_print(h_a, dim);

cudaMalloc((void**) &d_a, m_size );
cudaMalloc((void**) &d_at, m_size );


cudaMemcpy(d_a, h_a, m_size, cudaMemcpyHostToDevice);

mat_trans<<< (dim*dim + NUM_THREADS)/NUM_THREADS , NUM_THREADS >>>(d_a, d_at, dim);

cudaMemcpy(h_at, d_at, m_size, cudaMemcpyDeviceToHost);


if( dim <= 10)
    mat_print(h_at, dim);

free(h_a);
free(h_at);

cudaFree(d_a);
cudaFree(d_at);

return 0;
}

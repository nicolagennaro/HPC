#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>


double cclock()
  /* Returns elepsed seconds past from the last call to timer rest */
{

    struct timeval tmp;
    double sec;
    gettimeofday( &tmp, (struct timezone *)0 );
    sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
    return sec;
}


void print_mat(double *pt, int dim){
int i,j;

for( i = 0; i < dim; i++ ){
	for( j = 0; j < dim; j++ )
		printf("%3.1lf\t", *(pt + i*dim + j));

	printf("\n");
}

}


int check(double *m1, double *m2, int dim){
int ret, i, j;

ret = 1;

for( i = 0; i < dim; i++ ){
	for( j = 0; j < dim; j++ ){
		if( *(m1 + dim*i + j) != *(m2 + dim*j + i) ){
			ret = 0;
			break;
		}		
	}

	if( ret == 0 )
		break;
}


return ret;
}



int main( int argc, char * argv [] ) {

  double * A, * AT;
  int i, j;
  double t_start, t_end;
  int BLOCKSIZE, MATRIXDIM;
  // FILE *fp;

  if( argc < 3 ){
    fprintf( stderr, "Error. The program runs as following: %s [MATRIXDIM] [BLOCKSIZE]\nProgram exit ...\n", argv[0]);
    exit(1);
  }

  MATRIXDIM=atoi(argv[1]);
  BLOCKSIZE=atoi(argv[2]);

  if( MATRIXDIM < 1 ){
    fprintf( stderr, "Error. Inconsistent parameters  %s.\nProgram exit ...\n", argv[0]);
    exit(1);
  }

  A = ( double * ) malloc( MATRIXDIM * MATRIXDIM * sizeof( double ) );
  AT = ( double * ) malloc( MATRIXDIM * MATRIXDIM * sizeof( double ) );

  for( i = 0; i < MATRIXDIM * MATRIXDIM; i++ ){
    A[i] = (double) i;
    AT[i] = 0;
  }

if( MATRIXDIM <= 10 )
	print_mat(A,MATRIXDIM);

if( MATRIXDIM <= 10 )
	print_mat(AT,MATRIXDIM);



int n_blocks;
int ib, jb, ioff, joff;
double temp, mean, square;


// fp = fopen("transpose.dat","w");

// if(fp == NULL){
//	printf("cannot open file");
//	exit(1);
// }


int jt, n_times = 20;
int bb, bsize;

bsize = BLOCKSIZE;

mean = 0.0;
square = 0.0;
n_blocks = MATRIXDIM/BLOCKSIZE;
bsize = BLOCKSIZE;

for( jt=0; jt<n_times; jt++){ // loop for the time mean


t_start=cclock();

// block cycle on i
for( ib = 0; ib < n_blocks; ib++ ){

	ioff = ib*bsize;

	// block cycle on j
	for( jb = 0; jb < n_blocks; jb++ ){

		joff = jb*bsize;

		// Transposition
		for( i = 0; i < bsize; i++ )
			for( j = 0; j < bsize; j++ )
				*(AT + MATRIXDIM*(i + ioff) + j + joff) = *(A + (j+joff)*MATRIXDIM + (i+ioff) );
			

	} // jb
} // ib

	
t_end=cclock(); 
mean += (t_end - t_start);
square += (t_end - t_start)*(t_end - t_start);
	
}  // jt

mean /= (double)n_times;
square -= mean*mean*(double)n_times;
square/=(double)(n_times-1);
printf("%.5lf\t%.5lf\n", mean, sqrt(square));


free( A );
free( AT );


  return 0;
}

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




int main( int argc, char * argv [] ) {

  double * A, * AT;
  int i, j;
  double t_start, t_end;
  int MATRIXDIM;

  if( argc < 2 ){
    fprintf( stderr, "Error. The program runs as following: %s [MATRIXDIM]\nProgram exit ...\n", argv[0]);
    exit(1);
  }

  MATRIXDIM=atoi(argv[1]);


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

double temp, mean, square;

int jt, n_times = 20;

mean = 0.0;
square = 0.0;


for( jt=0; jt<n_times; jt++){ // loop for the time mean

	t_start=cclock();

	// Transposition
	for( i = 0; i < MATRIXDIM; i++ )
		for( j = 0; j < MATRIXDIM; j++ )
			*(AT + MATRIXDIM*i + j ) = *(A + MATRIXDIM*j + i );
			
	
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

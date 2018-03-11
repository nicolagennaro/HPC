#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]){

  long n , i ; 
  double  w,x,sum,pi,f,a;

  if(argc != 2){
    printf("Usage: ./a.out N_POINTS\n");
    exit(1);
  }
    
  n = atol(argv[1]);
  w = 1.0/n;
  sum = 0.0;


#pragma omp parallel for private(i,x) reduction(+:sum)
  for ( i = 1 ; i <= n ; i++ ) {
    x = w * (i - 0.5);
    sum += (4.0 / (1.0 + x * x ) );
  } 

  pi = w * sum ;
  printf("Value of pi: %.16g\n", pi);

  return 0;
} 

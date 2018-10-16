#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
  char filename[20];
  double *v;
  size_t read;
  int size;
  int i, j;
  FILE *fp;
  
  if(argc != 3){
    printf("USAGE: ./a.out filename size_to_read\n");
    exit(1);
  }

  if( strlen(argv[1]) > 20 ){
    printf("filename too long\n");
    exit(1);
  }

  strcpy(filename, argv[1]);

  printf("%s:\n", filename);

  fp = fopen(filename, "r");

  if(fp==NULL){
    printf("cannot open %s\n", filename);
    exit(1);
  }

  size = atoi(argv[2]);

  printf("size %d\n", size);

  v = (double*)malloc(size*size*sizeof(double));
  if(v==NULL){
    printf("cannot malloc %ld\n", size*size*sizeof(double));
    exit(1);
  }

  read = fread(v, sizeof(double), size*size, fp);

  for(i=0; i<size; i++){
    for(j=0; j<size; j++)
       printf("%.2lf\t", v[i*size + j]);
    printf("\n");
  }

  printf("\n\n");
  fclose(fp);
  
  return 0;
}

#include<stdio.h>
#include<stdlib.h>


int main(int argc, char **argv){

  if(argc < 2){
    printf("error\n");
    exit(0);
  }



  char* filename = argv[1];
  FILE* file;
  file = fopen(filename, "r");
  if(file == NULL){
    printf("error\n");
    exit(0);
  }


  int m;
  int n;
  fscanf(file, "%d %d", &m, &n);
  int m1[m][n];
  int m2[m][n];
  int f[m][n];
  int r;
  int c;



  for(r = 0; r < m; r++){
    for(c = 0; c < n; c++){
      fscanf(file, "%d", &m1[r][c]);
    }
  }


  for(r = 0; r < m; r++){
    for(c = 0; c < n; c++){
      fscanf(file, "%d", &m2[r][c]);
    }
  }


  for(r = 0; r < m; r++){
    for(c = 0; c < n; c++){
      f[r][c] = ((m1[r][c]) + (m2[r][c]));
    }
  }


  for(r = 0; r < m; r++){
    for(c = 0; c < n; c++){
      printf("%d\t", f[r][c]);
    }
    printf("\n");
  }
  fclose(file);
  return 0;
}

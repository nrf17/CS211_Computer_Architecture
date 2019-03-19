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


  int r1, c1;
  fscanf(file, "%d %d", &r1, &c1);
  int m1[r1][c1];
  int i, j;
  for(i = 0; i < r1; i++){
    for(j = 0; j < c1; j++){
      fscanf(file, "%d", &m1[i][j]);
    }
  }

    int r2, c2;
    fscanf(file, "%d %d", &r2, &c2);
    if(c1 != r2){
      printf("error\n");
      exit(0);
    }
    int m2[r2][c2];
    int m, n;
    for(m = 0; m < r2; m++){
      for(n = 0; n < c2; n++){
	fscanf(file, "%d", &m2[m][n]);
      }
    }




    int f[r1][c2];
    int a, b, c;
    int ans = 0;
    for(a = 0; a < r1; a++){
      for(b = 0; b < c2; b++){
	for(c = 0; c < r2; c++){
	  ans += (m1[a][c]*m2[c][b]);
	}
	f[a][b] = ans;
	ans = 0;
      }
    }



    int x, z;
    for(x = 0; x < r1; x++){
      for(z = 0; z < c2; z++){
	printf("%d\t", f[x][z]);
      }
      printf("\n");
    }
    fclose(file);
    return 0;
}

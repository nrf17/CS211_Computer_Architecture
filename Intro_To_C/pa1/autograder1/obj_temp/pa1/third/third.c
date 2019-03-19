#include<stdio.h>
#include<stdlib.h>
#include<math.h>



int main(int argc, char **argv){
  

  if( argc < 2){
    printf("error\n");
    exit(0);
  }

  int arr[10000];
  char* filename = argv[1];
  FILE* file;
  file = fopen(filename, "r");
  if(file == NULL){
    printf("error\n");
    exit(0);
  }
  char c;
  int n;
  while(fscanf(file, "%c %d\n", &c, &n) != EOF){
    if(c == 'i'){
      int indx = abs(c%10000);
      if(n == arr[indx]){
	printf("duplicate\n");
      }else{
	arr[indx] = n;
	printf("inserted\n");
      }
    }else if(c == 's'){
      int indx = abs(c%10000);
      if(n == arr[indx]){
	printf("present\n");
      }else{
	printf("absent\n");
      }
    }else{
      printf("error\n");
    }
  }
  return 0;
}

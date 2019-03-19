#include "second.h"

int main(int argc, char **argv){
  if(argc != 2){ printf("invalid input\n"); exit(0); }
  char* filename = argv[1];
  FILE* file;
  file = fopen(filename, "r");
  if(file == NULL){ printf("invalid input\n"); exit(0); }
  fclose(file);
  return 0;
}

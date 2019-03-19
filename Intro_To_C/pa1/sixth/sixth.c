#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv){

  if(argc < 2){
    printf("error\n");
    exit(0);
  }

  //number of words entered+1(for the binary file argv[0])
  int size = argc;
  //number to get all the arguments/words #1-total
  int i = 1;
  //position # to place char at in final acronym
  int j = 0;
  //size is number of words+1 to place "\0" at the end
  char final[size];
  //place to copy the argv[i] word
  char * copy;
  //gets each argv[i] word(argv[1]-argv[last])
  while(i < size){
    //number of chars + 1 for "\0"
    int len = strlen(argv[i]);
    len = len + 1;
    //allocates memory
    copy = (char*)malloc(sizeof(char)*(len));
    //copies the string argv[i] to the char * copy
    memcpy(copy, argv[i], len);
    //takes last char in word[i] and sets it to the positions in the final acronym
    final[j] = copy[0];
    //goes to next word
    i++;
    //goes to next open spot in final for the last char in word[i]
    j++;
    //frees the copy string, so no overflow and can reset copy string to next word
    free(copy);
  }

  final[size-1] = '\0';
  //prints the final acronym
  printf("%s\n", final);



  return 0;
}

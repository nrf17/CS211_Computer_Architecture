#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<math.h>
#include "first.h"

//prototypes

//method that converts the index string bits for a cache into an int
int binToDec(char* bin){
  //starts off at 2^0 and * 2 each iteration of the loop ot it goes from 1->2->4->8->16......
  int num = 1;
  int sum = 0;
  int spot = strlen(bin)-1;
  while(spot >= 0){
    if(bin[spot] == '1'){ sum = sum + num; }
    spot--;
    num = num*2;
  }
  return sum;
}





//convert the hexadecimal number to a binary string
char* hexToBin(char* hex, int k){
  char* bin = malloc(49);
  bin[48] = '\0';
  int a;
  for(a = 0; a < 47; a++){ bin[a] = '0'; }//sets the nonused bits in the beggining to 0
  int b = 47;
  for(k = k; k >= 2; k--){
    switch(hex[k]){
    case '0':/* = 0 in bin*/ bin[b-3] = '0'; bin[b-2] = '0'; bin[b-1] = '0'; bin[b] = '0'; b -= 4; break;
    case '1':/* = 1 in bin*/ bin[b-3] = '0'; bin[b-2] = '0'; bin[b-1] = '0'; bin[b] = '1'; b -= 4; break;
    case '2':/* = 2 in bin*/ bin[b-3] = '0'; bin[b-2] = '0'; bin[b-1] = '1'; bin[b] = '0'; b -= 4; break;
    case '3':/* = 3 in bin*/ bin[b-3] = '0'; bin[b-2] = '0'; bin[b-1] = '1'; bin[b] = '1'; b -= 4; break;
    case '4':/* = 4 in bin*/ bin[b-3] = '0'; bin[b-2] = '1'; bin[b-1] = '0'; bin[b] = '0'; b -= 4; break;
    case '5':/* = 5 in bin*/ bin[b-3] = '0'; bin[b-2] = '1'; bin[b-1] = '0'; bin[b] = '1'; b -= 4; break;
    case '6':/* = 6 in bin*/ bin[b-3] = '0'; bin[b-2] = '1'; bin[b-1] = '1'; bin[b] = '0'; b -= 4; break;
    case '7':/* = 7 in bin*/ bin[b-3] = '0'; bin[b-2] = '1'; bin[b-1] = '1'; bin[b] = '1'; b -= 4; break;
    case '8':/* = 8 in bin*/ bin[b-3] = '1'; bin[b-2] = '0'; bin[b-1] = '0'; bin[b] = '0'; b -= 4; break;
    case '9':/* = 9 in bin*/ bin[b-3] = '1'; bin[b-2] = '0'; bin[b-1] = '0'; bin[b] = '1'; b -= 4; break;
    case 'a':/* = 10 in bin*/ bin[b-3] = '1'; bin[b-2] = '0'; bin[b-1] = '1'; bin[b] = '0'; b -= 4; break;
    case 'b':/* = 11 in bin*/ bin[b-3] = '1'; bin[b-2] = '0'; bin[b-1] = '1'; bin[b] = '1'; b -= 4; break;
    case 'c':/* = 12 in bin*/ bin[b-3] = '1'; bin[b-2] = '1'; bin[b-1] = '0'; bin[b] = '0'; b -= 4; break;
    case 'd':/* = 13 in bin*/ bin[b-3] = '1'; bin[b-2] = '1'; bin[b-1] = '0'; bin[b] = '1'; b -= 4; break;
    case 'e':/* = 14 in bin*/ bin[b-3] = '1'; bin[b-2] = '1'; bin[b-1] = '1'; bin[b] = '0'; b -= 4; break;
    case 'f':/* = 15 in bin*/ bin[b-3] = '1'; bin[b-2] = '1'; bin[b-1] = '1'; bin[b] = '1'; b -= 4; break;
    }
  }
  char* z = bin;
  return z;
}




struct block* makeBlock(char* tag){
  struct block* blck = (struct block*)malloc(sizeof(struct block));
  blck->tagBits = tag;
  blck->next = NULL;
  return blck;
}


struct cache* makeCache(int numSets, int i){
  struct cache* c = (struct cache*)malloc(sizeof(struct cache));
  c->head = malloc(sizeof(struct block) * numSets);
  while(i < numSets){
  c->head[i] = NULL;
  i++;
  }
  return c;
}


//______________________________________________________________________________________________________________________________________________
int main(int argc, char** argv){
  
  //arguments from command line
  int cacheSize = atoi(argv[1]);
  char* ass = argv[2];
  int assoc;
  int blockSize = atoi(argv[3]);
  char* traceFile = argv[4];
  
  //check if the assoc is: direct, assoc, or assoc:n
  int direct = strcmp(ass, "direct");
  int assoctitty = strcmp(ass, "assoc");
  if(direct == 0){ assoc = 1; }
  else if(assoctitty == 0){ assoc = cacheSize/blockSize; }
  else{//if assoc:n, get the n number and from string and converts it to an int
    char b[3];
    int i;
    int j = 0;
    for(i = 6; i < 8; i++){
      if(ass[i] == '\0'){ break; }
      else{ b[j] = ass[i]; j++; }
    }//end of for loop
    for(j = j; j<3; j++){ b[j] = '\0'; }
    assoc = atoi(b);
  }//ends else

  //computes the # of sets, and the # of bits for the offset, index, tag
  int sets;
  if(assoctitty == 0){ sets = 1; }
  else{ sets = cacheSize/(assoc*blockSize); }
  int comp = blockSize;
  int o = 1;
  int offset = 0;
  while(o != comp){ o = o*2; offset += 1; }
  int indx = 0;
  int ind = 1;
  while(ind != sets){ ind = ind*2; indx += 1; }
  int tag = 48 - indx - offset;


  FILE* file;
  file = fopen(traceFile, "r");
  char* shit = (char*)malloc(sizeof(char) * 49);
  char op;
  char* hex = (char*)malloc(sizeof(char) * 49);

  int outputA[4] = {0,0,0,0};
  int p = 0;
  struct cache* cacheA = makeCache(sets, p);
  //need 2 caches
  int outputB[4] = {0,0,0,0};
  int q = 0;
  struct cache* cacheB = makeCache(sets, q);

  while(fscanf(file, "%s %c %s", shit, &op, hex) == 3){

    int h = 0;
    while(hex[h] != '\0'){ h++; }
    char* bin = hexToBin(hex, h);
    
    //the tag bits for cache A
    int i;
    char* tA = malloc(tag+1);
    tA[tag] = '\0';
    for(i = 0; i < tag; i++){ tA[i] = bin[i]; }
    //the index bits for cache A
    char* iA = malloc(indx+1);
    //char iA[indx+1];
    iA[indx] = '\0';
    int j = 0;
    for(i= tag; i < (tag+indx); i++){ iA[j] = bin[i]; j++; }
    //converts the index bits to an int for cache A
    int hashA = binToDec(iA);
    //_______________________________________________________
    //the index bits for cache B
    char* iB = malloc(indx+1);
    iB[indx] = '\0';
    for(i = 0; i < indx; i++){ iB[i] = bin[i]; }
    //the tag bits for cache B
    char* tB = malloc(tag+1);
    tB[tag] = '\0';
    j = 0;
    for(i = indx; i < (indx+tag); i++){ tB[j] = bin[i]; j++; }
    //converts the index bits to an int for cache B
    int hashB = binToDec(iB);
    //_______________________________________________________
    //work for cache A
    //______________________________________________________________________________________________________________________________________
    //___________________________________________________________________________________________________________________________________________
    //___________________________________________________________________________________________________________________________________________
    //___________________________________________________________________________________________________________________________________________
    //___________________________________________________________________________________________________________________________________________
    if(cacheA->head[hashA] == NULL){//empty bucket miss
      outputA[3]++;//miss++
      outputA[0]++;//read++
      if(op == 'W'){ outputA[1]++; /*write++*/ }
      struct block* new = makeBlock(tA);
      cacheA->head[hashA] = new;
    }else{//there is a link list that needs to be checked
      struct block* ptr = (struct block*)malloc(sizeof(struct block));
      ptr = cacheA->head[hashA];
      int count = 0;
      while(count < assoc){
	if(strcmp(ptr->tagBits, tA) == 0){//hit
	  outputA[2]++;//hit++
	  if (op == 'W'){ outputA[1]++; /*write++*/ }
	  break;
	}else{//miss/traverse
	  if(ptr->next != NULL){//traverse thru LL checking each node
	    ptr = ptr->next;
	    count++;
	  }else{//the end of the list without a match
	    if((count+1) == assoc){//if there is no more room because of reached max assoc
	      outputA[3]++;//miss++
	      outputA[0]++;//read++
	      if(op == 'W'){ outputA[1]++; /*write++*/ }
	      struct block* new = makeBlock(tA);
	      ptr->next = new;
	      cacheA->head[hashA] = cacheA->head[hashA]->next;
	      break;
	    }else{//not all of assoc is used, so do not need to change head, just add to the end
	      outputA[3]++;//miss++
	      outputA[0]++;//read++
	      if(op == 'W'){ outputA[1]++; /*write++*/ }
	      struct block* new = makeBlock(tA);
	      ptr->next = new;
	      break;
	    }//ends not all of assoc....->
	  }//(the end of the list w/o a match)
	}//ends miss/traverse
      }//ends while assoc loop
    }//ends LL check
    //___________________________________________________________________________________________________________________________________________
    //___________________________________________________________________________________________________________________________________________
    //___________________________________________________________________________________________________________________________________________
    if(cacheB->head[hashB] == NULL){//empty bucket miss
      outputB[3]++;//miss++
      outputB[0]++;//read++
      if(op == 'W'){ outputB[1]++; /*write++*/ }
      struct block* new = makeBlock(tB);
      cacheB->head[hashB] = new;
    }else{//there is a link list that needs to be checked
      struct block* ptr = (struct block*)malloc(sizeof(struct block));
      ptr = cacheB->head[hashB];
      int countB = 0;
      while(countB < assoc){
	if(strcmp(ptr->tagBits, tB) == 0){//hit
	  outputB[2]++;//hit++
	  if (op == 'W'){ outputB[1]++; /*write++*/ }
	  break;
	}else{//miss/traverse
	  if(ptr->next != NULL){//traverse thru LL checking each node
	    ptr = ptr->next;
	    countB++;
	  }else{//the end of the list without a match
	    if((countB+1) == assoc){//if there is no more room because of reached max assoc
	      outputB[3]++;//miss++
	      outputB[0]++;//read++
	      if(op == 'W'){ outputB[1]++; /*write++*/ }
	      struct block* new = makeBlock(tB);
	      ptr->next = new;
	      cacheB->head[hashB] = cacheB->head[hashB]->next;
	      break;
	    }else{//not all of assoc is used, so do not need to change head, just add to the end
	      outputB[3]++;//miss++
	      outputB[0]++;//read++
	      if(op == 'W'){ outputB[1]++; /*write++*/ }
	      struct block* new = makeBlock(tB);
	      ptr->next = new;
	      break;
	    }//ends not all of assoc....->
	  }//(the end of the list w/o a match)
	}//ends miss/traverse
      }//ends while assoc loop
    }//ends LL check
    
  }//ends big while
  printf("cache A\nMemory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", outputA[0], outputA[1], outputA[2], outputA[3]);
  printf("cache B\nMemory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", outputB[0], outputB[1], outputB[2], outputB[3]);
  
  free(shit);
  free(hex);
  fclose(file);
  





  return 0;
}

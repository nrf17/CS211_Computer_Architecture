#ifndef _first_h
#define _first_h


struct block{
  char* tagBits;
  struct block* next;
};

struct cache{
  struct block** head;
};


char* hexToBin(char* hex, int k);
int binToDec(char* bin);
struct block* makeBlock(char* tag);
struct cache* makeCache(int numSets, int i);





#endif

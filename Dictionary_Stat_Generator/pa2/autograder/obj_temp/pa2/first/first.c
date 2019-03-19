#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "first.h"
   
//struct trieNode *root;
//char* outi;
//void printRecur(struct trieNode *itr, char word[46], FILE *outPut, int ind);

/*struct trieNode{
  char letter;
  int occ;
  int super;
  struct trieNode* kid[26];
  bool leaf;
  };*/


struct trieNode* makeTrieNode(char l){
  char let = tolower(l);
  struct trieNode* entry;    
  entry = (struct trieNode *)malloc(sizeof(struct trieNode) * 1);
  entry->letter = tolower(let);
  entry->occ = 0;
  entry->super = 0;
  entry->leaf = false;
  int i = 0;
  while(i < 26){ entry->kid[i] = NULL; i++; }
  return entry;
}

//_______________________________________________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________________________________________


void readDict (FILE *dict){
  root = makeTrieNode('\0');
  char l;
  struct trieNode *itr = root;
  while(fscanf(dict, "%c", &l) != EOF){
    char let = tolower(l);
    int ind = let - 'a';
    if(isalpha(let)){
      if(itr->kid[ind] != NULL){ itr = itr->kid[ind]; continue; }
      struct trieNode *node = makeTrieNode(let);
      itr->kid[ind] = node;
      itr = itr->kid[ind];
    }else{
      if(itr != root){ itr->leaf = true; }
      itr = root;
    }
  }//ends while
  fclose(dict);
  return;
}




//_______________________________________________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________________________________________


void matchStr(char* str){
  FILE *data = fopen(str, "r");
  char l;
  char word[300];
  int i = 0;
  while(i < 300){ word[i] = '\0'; i++; }
  int j = 0;
  bool end = false;    
  while(fscanf(data, "%c", &l) != EOF){
    char let = tolower(l);
    //int ind = let - 'a';
    if(isalpha(let)){ word[j] = let; end = true; j++; }
    else{
      if(end == true){
	int k = j;
	while(k < 300){ word[k] = '\0'; k++; }
	//_______________________________________________________________________________________________________________________________________
        struct trieNode *itr = root;
	int len = strlen(word);
	int z = 0;
	while(z < len){
	  if(itr == NULL){ z++; continue;}  
	  if(itr->leaf == true){
	    int charLeft = len - z;
	    if(charLeft != 0){ itr->super += 1; }
	  }
	  char c = word[z];
	  int indx = c - 'a';
	  itr = itr->kid[indx];
	  z++;
	}//ends while
	if(itr != NULL){
	  if(itr->leaf == true){ itr->occ += 1; }
	}
        //_______________________________________________________________________________________________________________________________________
	j = 0;
	end = false;
      }// ends end == true
    }//ends else not a word
  }//ends while
  fclose(data);
  return;
}












//_______________________________________________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________________________________________
   

void printResult(){
    FILE *outP = fopen(outi, "w");
    char word[300];
    printRecur(root, word , outP, -1); //go through all
    fclose(outP);
}


void printRecur(struct trieNode *itr, char word[300], FILE *outPut, int ind){
  if(itr == NULL){ return; }
  if(itr != root){ word[ind] = itr->letter; }
  if(itr->leaf == true){
    int i = ind + 1;
    while(i < 300){ word[i] = '\0'; i++; }
    int occurences = itr->occ;
    int superwords = itr->super;
    fprintf(outPut,"%s %d %d\n", word, occurences, superwords);
  }//ends if leaf
  int i = 0;
  while(i < 26){
    if(itr->kid[i] == NULL){ i++; }
    else{ printRecur(itr->kid[i], word, outPut, ind+1); i++; }
  }
  return;
}

//_______________________________________________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________________________________________

void freeTree(struct trieNode *itr){
    if(itr == NULL){ return; }
    int i = 0;
    while(i < 26){
      if(itr->kid[i] == NULL){ i++; }
      else{ freeTree(itr->kid[i]); i++; }
    }//end while
      free(itr);
      return;
}








int main(int argc, char **argv){
  if(argc != 2){ printf("invalid input\n"); exit(0); }
  
  char* fileName = argv[1];
  FILE* file;
  file = fopen(fileName, "r");
  if(file == NULL){ printf("invalid input\n"); exit(0); }
  
  char *dict_file;
  char *data_file;
  dict_file = (char *)malloc(sizeof(char) * 20);
  data_file = (char *)malloc(sizeof(char) * 20);
  
  int fNum = 1;
  while(fscanf(file, "%s %s", dict_file, data_file) != EOF){
    FILE *dict = fopen(dict_file, "r");
    readDict(dict);
    matchStr(data_file);

    
    char output[11];
    outi = output;
    sprintf(outi, "out%d.txt", fNum);
    printResult();
    freeTree(root);
    root = NULL;
    fNum++;
  }//end while
  free(dict_file);
  free(data_file);
  fclose(file);
  return 0;
}

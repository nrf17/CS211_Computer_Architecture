#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "first.h"
   


//creates the node and allocates the space for each node
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

//reades the dictioinary file and creates the trie for it
void readDict (FILE *dict){
  //creates the root with the null char
  root = makeTrieNode('\0');
  char l;
  struct trieNode *itr = root;
  //scans the file char by char until word is over then creates a new word, makes char lowercase and get its index
  while(fscanf(dict, "%c", &l) != EOF){
    char let = tolower(l);
    int ind = let - 'a';
    if(isalpha(let)){// is a letter, continue word
      if(itr->kid[ind] != NULL){ itr = itr->kid[ind]; continue; }//letter already exist, no need to add it in
      //letter not present adds it into trie
      struct trieNode *node = makeTrieNode(let);
      itr->kid[ind] = node;
      itr = itr->kid[ind];
    }else{//char is not a letter, ends word, marks last letter the end of word
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

//reads the data file and matches with the words in the trie to update the info
void matchStr(char* str){
  //reads data file
  FILE *data = fopen(str, "r");
  char l;
  char word[300];
  int i = 0;
  //sets word to all null
  while(i < 300){ word[i] = '\0'; i++; }
  int j = 0;
  bool end = false;    
  //scans the file char by char untill we are out of chars, converts the char to lower case
  while(fscanf(data, "%c", &l) != EOF){
    char let = tolower(l);
    //int ind = let - 'a';
    if(isalpha(let)){ word[j] = let; end = true; j++; }//char is a letter, add it to the word and get next char
    else{//char is not a letter, end of word time to do the comparing
      if(end == true){
	int k = j;
	while(k < 300){ word[k] = '\0'; k++; }//set the remainder of the empty spaces in the word array to null char
	//_______________________________________________________________________________________________________________________________________
        //searches trie until the word from the data file runs out or the trie reaches an end
	struct trieNode *itr = root;
	int len = strlen(word);
	int z = 0;
	//the search
	while(z < len){
	  if(itr == NULL){ z++; continue;}  
	  if(itr->leaf == true){//hit a the end of a word from dict words
	    int charLeft = len - z;
	    //the word at this point in the trie is a prefix of the word from the data file
	    if(charLeft != 0){ itr->super += 1; }
	  }
	  //continues the search until reaching a the ending of a dict file word
	  char c = word[z];
	  int indx = c - 'a';
	  itr = itr->kid[indx];
	  z++;
	}//ends while
	//the words being compared are the exact same
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
   
//prints the result from trie add and search
void printResult(){
    FILE *outP = fopen(outi, "w");
    char word[300];
    printRecur(root, word , outP, -1); //go through all
    fclose(outP);
}

//recursice helper method to traverse the tre and get all the information for each dictionary word
void printRecur(struct trieNode *itr, char word[300], FILE *outPut, int ind){
  if(itr == NULL){ return; }//base case
  if(itr != root){ word[ind] = itr->letter; }//copies the letters of the word in the trie
  if(itr->leaf == true){//end of dict word
    int i = ind + 1;
    while(i < 300){ word[i] = '\0'; i++; }
    //prints the words occurences and prefixs of dict word
    int occurences = itr->occ;
    int superwords = itr->super;
    fprintf(outPut,"%s %d %d\n", word, occurences, superwords);
  }//ends if leaf
  //recursive call, searches the rest of the kids
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

//recursive method to free all the nodes in the tree so next file is quicker and there are no memory problems
void freeTree(struct trieNode *itr){
  if(itr == NULL){ return; }//base case
    int i = 0;
    //traverses the entire tree to free the node there
    while(i < 26){
      if(itr->kid[i] == NULL){ i++; }
      else{ freeTree(itr->kid[i]); i++; }
    }//end while
      free(itr);
      return;
}








int main(int argc, char **argv){
  //incorrect input, no mapping file, program terminates
  if(argc != 2){ printf("invalid input\n"); exit(0); }
  
  //gets the mapping file, if it is empty, program terminates
  char* fileName = argv[1];
  FILE* file;
  file = fopen(fileName, "r");
  if(file == NULL){ printf("invalid input\n"); exit(0); }
  
  //creates the dict and data files, allocates space for them
  char *dict_file;
  char *data_file;
  dict_file = (char *)malloc(sizeof(char) * 20);
  data_file = (char *)malloc(sizeof(char) * 20);
  
  //scans each dict and data file, keeps track of what set of files we are on
  int fNum = 1;
  while(fscanf(file, "%s %s", dict_file, data_file) != EOF){
    //reads dict file and builds tree
    FILE *dict = fopen(dict_file, "r");
    readDict(dict);
    //reads data file, does the matching
    matchStr(data_file);

    //create the output for results, fills the file, then frees the tree for the next set of files
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

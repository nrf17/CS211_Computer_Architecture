

#ifndef _first_h
#define _first_h

struct trieNode{
  char letter;
  int occ;
  int super;
  struct trieNode* kid[26];
  bool leaf;
};
struct trieNode *root;
char* outi;
struct trieNode* makeTrieNode(char let);
void readDict(FILE *dict);
void matchStr(char* str);
void printResult();
void printRecur(struct trieNode *itr, char word[300], FILE *outPut, int ind);
void freeTree(struct trieNode *itr);


#endif

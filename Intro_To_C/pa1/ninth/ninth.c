#include<stdio.h>
#include<stdlib.h>


struct node{
  int num;
  struct node* left;
  struct node* right;
};


struct node* newNode(int number){
  struct node* temp;
  temp = (struct node*)malloc(sizeof(struct node));
  temp->num = number;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}



struct node* addNode(struct node* root, int val){
  //level the we are currently at
  int i = 1;
  //no nodes in tree
  if(root == NULL){
    root = newNode(val);
    printf("inserted %d\n", i);
    return root;
  }else if(root->num == val){
    //number already present in tree
    printf("duplicate\n");
    return root;
  }else if(val < root->num){//need to enter left subtree
    //new starts here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //first # to left inserted
    if(root->left == NULL){
      i++;
      root->left = newNode(val);
      printf("inserted %d\n", i);
      return root;
    }else if(root->left->num == val){
      //# already exists in tree
      printf("duplicate\n");
      return root;
    }else{//left subtree move
      //last starts here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      //need to move to left subtree
      struct node *ptr = root->left;
      int ins = 0;
      i++;
      //loop to continue iterating through the subtree
      while(ins == 0){
	//checks if # already exits
	if(ptr->num == val){
	  printf("duplicate\n");
	  return root;
	}else if(val < ptr->num){//continue going left
	  //continue going left
	  if(ptr->left != NULL){
	    ptr = ptr->left;
	    i++;
	    if(ptr->num == val){
	      printf("duplicate\n");
	      return root;
	    }
	  }else{//next spot is null, found insertion spot
	    ptr->left = newNode(val);
	    i++;
	    printf("inserted %d\n", i);
	    ins++;
	    return root;
	  }
	}else{//else(val > ptr->num)|||||||||need to start heading right in the subtree
	  //other starts here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  //continue going right
	  if(ptr->right != NULL){
	    ptr = ptr->right;
	    i++;
	    if(ptr->num == val){
	      printf("duplicate\n");
	      return root;
	    }
	  }else{//next spot is null, found insertion spot
	    ptr->right = newNode(val);
	    i++;
	    printf("inserted %d\n", i);
	    ins++;
	    return root;
	  }
	}//ends ELSE (other)
      }//ends INS WHILE
    }//ends ELSE  condition (last)
    //ends(new) (val < root->num)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  }else{//(val > root->num) need to enter right subtree
    //new starts here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     //first # to the right to be inserted
    if(root->right == NULL){
      i++;
      root->right = newNode(val);
      printf("inserted %d\n", i);
      return root;
    }else if(root->right->num == val){
      //# already exists in tree
      printf("duplicate\n");
      return root;
    }else{//right subtree move
      //last starts here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      //need to move to right subtree
      struct node *ptr = root->right;
      int ins = 0;
      i++;
      //loop to continue iterating through the subtree
      while(ins == 0){
	//checks if # already exits
	if(ptr->num == val){
	  printf("duplicate\n");
	  return root;
	}else if(val < ptr->num){//need to start heading left
	  //checks if we can continue left
	  if(ptr->left != NULL){
	    ptr = ptr->left;
	    i++;
	    if(ptr->num == val){
	      printf("duplicate\n");
	      return root;
	    }
	  }else{//next spot is null, found insertion spot
	    ptr->left = newNode(val);
	    i++;
	    printf("inserted %d\n", i);
	    ins++;
	    return root;
	  }
	}else{//else(val > ptr->num)|||||||||continue heading right in the subtree
	  //other start here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	  //continue going right
	  if(ptr->right != NULL){
	    ptr = ptr->right;
	    i++;
	    if(ptr->num == val){
	      printf("duplicate\n");
	      return root;
	    }
	  }else{//next spot is null, found insertion spot
	    ptr->right = newNode(val);
	    i++;
	    printf("inserted %d\n", i);
	    ins++;
	    return root;
	  }
	}//ends ELSE (other)
      }//ends INS WHILE
    }//ends ELSE  condition (last)
  }//ends (new) (val > root->num)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //keeps the program from complaining
  return root;
}//ends method







struct node* searchTree(struct node* root, int target){
  int i = 1;
  if(root == NULL){
    printf("absent\n");
    return root;
  }else{
    struct node *ptr = root;
    int srch = 0;
    while(srch == 0 /*ptr->left != NULL && ptr->right != NULL*/){
      if(target == ptr->num){
	printf("present %d\n", i);
	return root;
      }else if(target < ptr->num){
	if(ptr->left == NULL){
	  break;
	}else{
	  ptr = ptr->left;
	  i++;
	}
      }else{//(target > ptr->num)
	if(ptr->right == NULL){
	  break;
	}else{
	  ptr = ptr->right;
	  i++;
	}
      }
      if(ptr->num == target){
	printf("present %d\n", i);
	return root;
      }
      if(ptr->left == NULL && ptr->right == NULL){
	srch++;
      }
    }//ends WHILE
  }//ends ELSE
  printf("absent\n");
  return root;
}








struct node* removeNode(struct node* root, int targ){


  if(root == NULL){
    printf("fail\n");
    return root;
  }else if(root->num == targ){
    //here
    if(root->left == NULL && root->right == NULL){
      struct node* temp = root;
      root = NULL;
      free(temp);
      printf("success\n");
      return root;
    }else if(root->right == NULL){//HERE 1
      struct node* ptr = root->left;
      if(ptr->right == NULL){
	int val = ptr->num;
	struct node* temp = ptr;
	root->left = ptr->left;
	free(temp);
	root->num = val;
	printf("success\n");
	return root;
      }
      while(ptr->right->right != NULL){
	ptr = ptr->right;
      }
      int val = ptr->right->num;
      struct node* temp = ptr->right;
      ptr->right = ptr->right->left;
      free(temp);
      root->num = val;
      printf("success\n");
      return root;
      //HERE 1
    }else{
      struct node* ptr = root->right;
      if(ptr->left == NULL){
	int val = ptr->num;
	struct node* temp = ptr;
	root->right = ptr->right;
	free(temp);
	root->num = val;
	printf("success\n");
	return root;
      }
      while(ptr->left->left != NULL){
	ptr = ptr->left;
      }
      int val = ptr->left->num;
      struct node* temp = ptr->left;
      ptr->left = ptr->left->right;
      free(temp);
      root->num = val;
      printf("success\n");
      return root;
    }//ends else
    //here
    //_____________________________________________________________________________________________________________________________
  }else if(targ < root->num){//start NOW
    struct node* ptr = root->left;
    int srch = 0;
    while(srch == 0){
      if(targ == ptr->num){
	/*
	 *
	 *
	 *
	 */
	if(ptr->left == NULL && ptr->right == NULL){
	  struct node* temp = ptr;
	  ptr = NULL;
	  free(temp);
	  printf("success\n");
	  return root;
	}else if(ptr->right == NULL){
	  struct node* ptr2 = ptr->left;
	  if(ptr2->right == NULL){
	    int val = ptr2->num;
	    struct node* temp = ptr2;
	    ptr->left = ptr2->left;
	    ptr->num = val;
	    free(temp);
	    printf("success\n");
	    return root;
	  }
	  while(ptr2->right->right != NULL){
	    ptr2 = ptr2->right;
	  }
	  int val = ptr2->right->num;
	  struct node* temp = ptr2->right;
	  ptr2->right = ptr2->right->left;
	  free(temp);
	  ptr->num = val;
	  printf("sucess\n");
	  return root;
	}else{
	  struct node* ptr2 = ptr->right;
	  if(ptr2->left == NULL){
	    int val = ptr2->num;
	    struct node* temp = ptr2;
	    ptr->right = ptr2->right;
	    ptr->num = val;
	    free(temp);
	    printf("success\n");
	    return root;
	  }
	  while(ptr2->left->left != NULL){
	    ptr2 = ptr2->left;
	  }
	  int val = ptr2->left->num;
	  struct node* temp = ptr2->left;
	  ptr2->left = ptr2->left->right;
	  free(temp);
	  ptr->num = val;
	  printf("success\n");
	  return root;
	}
	/*
	 *
	 *
	 *
	 */
      }else if(targ < ptr->num){
	if(ptr->left == NULL){
	  break;
	}else{
	  ptr = ptr->left;
	}
      }else{//(targ > ptr->num)
	if(ptr->right == NULL){
	  break;
	}else{
	  ptr = ptr->right;
	}
      }
      if(ptr->num == targ){
	/*
	 *
	 *
	 *
	 */
        if(ptr->left == NULL && ptr->right == NULL){
	  struct node* temp = ptr;
	  ptr = NULL;
	  free(temp);
	  printf("success\n");
	  return root;
	}else if(ptr->right == NULL){
	  struct node* ptr2 = ptr->left;
	  if(ptr2->right == NULL){
	    int val = ptr2->num;
	    struct node* temp = ptr2;
	    ptr->left = ptr2->left;
	    ptr->num = val;
	    free(temp);
	    printf("success\n");
	    return root;
	  }
	  while(ptr2->right->right != NULL){
	    ptr2 = ptr2->right;
	  }
	  int val = ptr2->right->num;
	  struct node* temp = ptr2->right;
	  ptr2->right = ptr2->right->left;
	  free(temp);
	  ptr->num = val;
	  printf("sucess\n");
	  return root;
	}else{
	  struct node* ptr2 = ptr->right;
	  if(ptr2->left == NULL){
	    int val = ptr2->num;
	    struct node* temp = ptr2;
	    ptr->right = ptr2->right;
	    ptr->num = val;
	    free(temp);
	    printf("success\n");
	    return root;
	  }
	  while(ptr2->left->left != NULL){
	    ptr2 = ptr2->left;
	  }
	  int val = ptr2->left->num;
	  struct node* temp = ptr2->left;
	  ptr2->left = ptr2->left->right;
	  free(temp);
	  ptr->num = val;
	  printf("success\n");
	  return root;
	}
	/*
	 *
	 *
	 *
	 */
      }
      if(ptr->left == NULL && ptr->right == NULL){
	srch++;
      }
    }//ends WHILE
    printf("fail\n");
    return root;
    //_______________________________________________________________________________________________________________________________
    //end NOW
  }else{
    struct node* ptr = root->right;
    int srch = 0;
    while(srch == 0){
      if(targ == ptr->num){
	/*
	 *
	 *
	 *
	 */
	if(ptr->left == NULL && ptr->right == NULL){
	  struct node* temp = ptr;
	  ptr = NULL;
	  free(temp);
	  printf("success\n");
	  return root;
	}else if(ptr->right == NULL){
	  struct node* ptr2 = ptr->left;
	  if(ptr2->right == NULL){
	    int val = ptr2->num;
	    struct node* temp = ptr2;
	    ptr->left = ptr2->left;
	    ptr->num = val;
	    free(temp);
	    return root;
	  }
	  while(ptr2->right->right != NULL){
	    ptr2 = ptr2->right;
	  }
	  int val = ptr2->right->num;
	  struct node* temp = ptr2->right;
	  ptr2->right = ptr2->right->left;
	  free(temp);
	  ptr->num = val;
	  printf("sucess\n");
	  return root;
	}else{
	  struct node* ptr2 = ptr->right;
	  if(ptr2->left == NULL){
	    int val = ptr2->num;
	    struct node* temp = ptr2;
	    ptr->right = ptr2->right;
	    ptr->num = val;
	    free(temp);
	    printf("success\n");
	    return root;
	  }
	  while(ptr2->left->left != NULL){
	    ptr2 = ptr2->left;
	  }
	  int val = ptr2->left->num;
	  struct node* temp = ptr2->left;
	  ptr2->left = ptr2->left->right;
	  free(temp);
	  ptr->num = val;
	  printf("success\n");
	  return root;
	}
	/*
	 *
	 *
	 *
	 */
      }else if(targ < ptr->num){
	if(ptr->left == NULL){
	  break;
	}else{
	  ptr = ptr->left;
	}
      }else{//(targ > ptr->num)
	if(ptr->right == NULL){
	  break;
	}else{
	  ptr = ptr->right;
	}
      }
      if(ptr->num == targ){
	/*
	 *
	 *
	 *
	 */
        if(ptr->left == NULL && ptr->right == NULL){
	  struct node* temp = ptr;
	  ptr = NULL;
	  free(temp);
	  printf("success\n");
	  return root;
	}else if(ptr->right == NULL){
	  struct node* ptr2 = ptr->left;
	  if(ptr2->right == NULL){
	    int val = ptr2->num;
	    struct node* temp = ptr2;
	    ptr->left = ptr2->left;
	    ptr->num = val;
	    free(temp);
	    return root;
	  }
	  while(ptr2->right->right != NULL){
	    ptr2 = ptr2->right;
	  }
	  int val = ptr2->right->num;
	  struct node* temp = ptr2->right;
	  ptr2->right = ptr2->right->left;
	  free(temp);
	  ptr->num = val;
	  printf("sucess\n");
	  return root;
	}else{
	  struct node* ptr2 = ptr->right;
	  if(ptr2->left == NULL){
	    int val = ptr2->num;
	    struct node* temp = ptr2;
	    ptr->right = ptr2->right;
	    ptr->num = val;
	    free(temp);
	    printf("success\n");
	    return root;
	  }
	  while(ptr2->left->left != NULL){
	    ptr2 = ptr2->left;
	  }
	  int val = ptr2->left->num;
	  struct node* temp = ptr2->left;
	  ptr2->left = ptr2->left->right;
	  free(temp);
	  ptr->num = val;
	  printf("success\n");
	  return root;
	}
	/*
	 *
	 *
	 *
	 */
      }
      if(ptr->left == NULL && ptr->right == NULL){
	srch++;
      }
    }//ends WHILE
    printf("fail\n");
    return root;
  }//ends METHOD
  return root;
}














int main(int argc, char **argv){
  
  if(argc < 2){
    printf("error\n");
    exit(0);
  }


  struct node* root = NULL;
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
      root = addNode(&(*root), n);
    }else if(c == 's'){
      root = searchTree(&(*root), n);
    }else if(c == 'd'){
      root = removeNode(&(*root), n);
    }
    else{
      printf("error\n");
      exit(0);
    }
  }
  fclose(file);
  return 0;
}

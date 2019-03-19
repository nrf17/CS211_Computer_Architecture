#include<stdio.h>
#include<stdlib.h>



struct node{
  //what makes up a node in the LL
  //the number in the list
  int num;
  //the next command for the next  node in the LL
  struct node* next;
};


struct node* newNode(int number){
    //makes the node that will be inserted into the LL
    struct node* element;
    //allocates memory for each node that will be created
    element = (struct node*)malloc(sizeof(struct node));
    //assign the number and the next command for the node
    element->num = number;
    element->next = NULL;
    return element;
  }




struct node* addNode(struct node* root, int value){
  //if the list is empty, adds the 1st node to the LL
  if(root == NULL){
    root = newNode(value);
    return root;
  }else if(root->num == value){
    //the number is already in the LL
    return root;
  }else if(value < root->num){
    //the node being inserted is the smallest number in the list and should now be the first node
    struct node* holder = newNode(value);
    holder->next = root;
    root = holder;
    return root;
  }else{//starts LAST ELSE statement
    //the node trying to be inserted is further down the list
    struct node *ptr = root;
    while(ptr->next != NULL){
      //the node already exists in the LL
      if(ptr->next->num == value){
	return root;
      }else if(value < ptr->next->num){
	//the node being inserted needs to go inbetween two numbers
	struct node* temp = newNode(value);
	temp->next = ptr->next;
	ptr->next = temp;
	return root;
      }else{
	//correct position not yet found for node
	ptr = ptr->next;
      }
	
    }

  

    //the number being inserted is the largest number in the list and should be last
    ptr->next = newNode(value);
    return root;
  }//ends LAST ELSE statement




}









struct node* removeNode(struct node* root, int target){
  //list is empty nothing to delete
  if(root == NULL){
    return root;
  }else if(root->num > target){
    return root;
  }else if(root->num == target){
    //1st node is to be deleted and then adjust the root
    struct node* temp = root;
    root = root->next;
    free(temp);
    return root;
  }else{
    //target woulld be located somewhere further down the LL
    struct node* ptr = root;
    while(ptr->next != NULL){
      //the next number is to be deleted
      if(ptr->next->num == target){
	struct node* temp = ptr->next;
	ptr->next = ptr->next->next;
	free(temp);
	return root;
      }else if(ptr->next->num > target){
	//quicker method of determining if number is in LL, this way you do not traverse the whole list if its not in it
	return root;
      }else{
	//continues to find target
	ptr = ptr->next;
      }
    }
    //node does not exist in the LL
    return root;
  }//end of else statement
  }//ends method





//prints the LL
void printList(struct node *root){
  struct node *ptr = root;
  while(ptr != NULL){
    printf("%d\t", ptr->num);
    ptr = ptr->next;
  }
  printf("\n");
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
  char ch;
  int num;
  while(fscanf(file, "%c %d\n", &ch, &num) != EOF){
    if(ch == 'i'){
      root = addNode(&(*root), num);
      }else if(ch == 'd'){
      root = removeNode(&(*root), num);
      }else{
	printf("error\n");
	exit(0);
	}
  }
  fclose(file);
  printList(root);
  return 0;
}

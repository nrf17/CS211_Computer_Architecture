#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

  /*if a number isnt entered from the command promt reports an error*/
   if(argc < 2){
     printf("error\n");
     exit(0);
   }

   /*takes input number from the command line and determines whether the number is prime or not*/
  float num = atoi(argv[1]);
  float i;
  
  /*divides number from 2-9 to see if the number is divisble by anything other than 1 and itself*/
  for(i = 2; i < num; i++){//STARTS THE BIGGEST FOR LOOP (DIVIDEND FOR LOOP)
    /*makes sure the input isnt divided by itself because the program would report back that it is prime*/
    if(i == num){
      i++;
    }
    /*divides number to test for prime*/
    float temp = (num/i);
    /*converts the float to a string*/
    char t[25];
    sprintf(t, "%.1f", temp);
    /*loops through the result to see if the number did a clean divison with no decimals*/
    int j;
    for(j = 0; j < 25; j++){//STARTS THE SMALLER FOR LOOP (LOOP THROUGH THE RESULT)
      /*find the '.' char because the number after this is all we care for*/
      if(t[j] == '.'){//START 1ST IF STATMENT
	j++;
	/*if the tenth place is a 0, then clean divison was done and the number is not prime*/
	if(t[j] == '0'){//STARTS 2ND IF STATEMENT
	  printf("no\n");
	  return 0;
	}//ENDS 2ND IF STATEMENT
      }//ENDS 1ST IF STATMENT
    }//ENDS SMALLER FOR LOOP (LOOP THROUGH RESULT)
  }//ENDS BIGGEST FOR LOOP (DIVIDEND FOR LOOP)

  /*all divison was done and the input is not divisble by any other number, so it is prime*/
  printf("yes\n");
  return 0;
}

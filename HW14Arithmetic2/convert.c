// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "list.h"
#include "convert.h"

// DO NOT MODIFY FROM HERE --->>>
const int Operations[] = {'+', '-', '*', '(', ')'};

// return -1 if the word is not an operator
// return 0 if the word contains '+'
//        1                      '-'
//        2                      '*'
//        3                      '('
//        4                      ')'
int isOperator(char * word)
{
  int ind;
  int numop = sizeof(Operations) / sizeof(int);
  for (ind = 0; ind < numop; ind ++)
    {
    char *loc = strchr(word, Operations[ind]);
    if (loc != NULL && !isdigit(loc[1]))
	{
	  return ind;
	}
    }
  return -1;
}
// <<<--- UNTIL HERE

// ***
// *** You MUST modify the convert function
// ***
//HANDLE: Nothing is left in the input. Pop the stack and append it to the end of the output.
#ifdef TEST_CONVERT
bool convert(List * arithlist)
{
  if (arithlist == NULL)
    {
      return true;
    }
  if ((arithlist -> head) == NULL)
    {
      return true;
    }
  //VARIABLE DECLARATIONS
  ListNode *iteration = arithlist->head; //LinkNode to be used for iteration only. Always set back to head. 
  ListNode *a = arithlist->head;
  int numOfOperands; //counter for operands
  int numOfOperators; //counter for operators
  int currentPrec = 0; //Stores precedence of iteration nodes precedence. 
  int tailPrec = 0; //Will store the tails precedence for comparision. 
  int temp; //temp variable
  bool parantheses = false;
  List * operators = malloc(sizeof(List)); //Link to store operators
  List * outputs = malloc(sizeof(List)); //Link to store outputs 
  operators->head = NULL;
  operators->tail = NULL;
  outputs->head = NULL;
  outputs->tail = NULL;
  //Do initial iteration through arithlist. Count amount of operators there are in List. 
  while(iteration){
    if(isOperator(iteration->word) == -1){
      numOfOperands++;
    }
    else if(isOperator(iteration->word) >= 0){
      numOfOperators++;
    }
    iteration = iteration->next;
  }
  iteration = arithlist->head;
  //printf("operands: %d\n", numOfOperands);
  //printf("operators: %d\n", numOfOperators);
  while(iteration){
    if(isOperator(iteration->word) >= 0){ //If current node is operator
        //printf("operator: %s\n", iteration->word);
        temp = isOperator(iteration->word); //precedence of current node
        if((temp == 0) || (temp == 1)){currentPrec = 1;} //precedence is + or -
        else if(temp == 2){currentPrec = 2;} //precedence is *
        else if(temp == 3){
          currentPrec = 3;
          parantheses = true;} //parantheses active
        else if(temp == 4){currentPrec = 4;}
      if(operators->head != NULL){ //If operators Link is not empty
        temp = isOperator(operators->tail->word); //precedence of tail node

        if((temp == 0) || (temp == 1)){tailPrec = 1;} //precedence is + or -
        else if(temp == 2){tailPrec = 2;} //precedence is *
        else if(temp == 3){
          currentPrec = 3;
          parantheses = true;} //parantheses active
        else if(temp == 4){//printf("operators has ) !!");
        }
        //printf("tailOperator %s\n", operators->tail->word);

        if(currentPrec == tailPrec){ //If currentPrec == tailPrec ->pop
          addNode(outputs, operators->tail->word);
          deleteNode(operators, operators->tail);
        }
        else if((tailPrec == 2) && (tailPrec > currentPrec)){ //If currentPrec is + or -, tailPrec is *
          addNode(outputs, operators->tail->word);
          deleteNode(operators, operators->tail);
        }
        else if((currentPrec == 2) && (currentPrec > tailPrec)){
          addNode(operators, iteration->word);
        }
        else if(currentPrec == 3){
          addNode(operators, iteration->word);
        }
        else if((currentPrec == 4) && parantheses){
          //printf("Iteration: %s\n", operators->tail->word);
          while(isOperator(operators->tail->word) != 3){
            addNode(outputs, operators->tail->word);
            deleteNode(operators, operators->tail);
          }
          deleteNode(operators, operators->tail);
        }
      }
      else{ //If list is empty, add operator. 
        addNode(operators, iteration->word);
      }
      // a = operators->head;
      // while(a){
      //   printf("operators: %s\n", a->word);
      //   a = a->next;
      // }  
    } //END OF: if(isOperator(iteration->word) >= 0)

    else{ //if current iteration is not a operator, add integer to outputs.  
      addNode(outputs, iteration->word);
      // a = outputs->head;
      // while(a){
      //   printf("outputs: %s\n", a->word);
      //   a = a->next;
      // }  
    }
    //tempNode = iteration; //Store current node after it is assigned.     
    iteration = iteration->next; //iterate to next
    //deleteNode(arithlist, tempNode); //Delete current node
  }
  ListNode *tempNode = iteration;
  //printf("-------------------\n");
  a = operators->head;
   while(a){
    //printf("operators: %s\n", a->word);
    a = a->next;
  }  
  iteration = operators->head;
  tempNode = operators->tail;
  while(tempNode){
    addNode(outputs, tempNode->word);
    tempNode = tempNode ->prev;
  }
  while(arithlist->head){
    deleteNode(arithlist,arithlist->head);
  }
  arithlist->head = outputs->head;
  arithlist->tail = outputs->tail;
  deleteList(operators);
  free(outputs);
  return true;
}
#endif
      //  if(temp == 0 || temp == 1){currentPrec = 5; }
      //   else if(temp == 2){currentPrec = 10;}
      //   else if(temp == 3){
      //     currentPrec = 10;
      //     parantheses = true;
      //   }
      //   else if(temp == 4){
      //     currentPrec = 10;
      //   }
      //   temp = isOperator(operators->tail->word); //precedence of tail node
      //   if(temp == 0 || temp == 1){currentPrec = 5; }
      //   else if(temp == 2){currentPrec = 10;}
      //   else if(temp == 3){
      //     currentPrec = 10;
      //    // parantheses = true;
      //   }
      //   else if(temp == 4){
      //     currentPrec = 10;
      //   }
      //deleteNode(operators, operators->tail); //To delete last parantheses. 
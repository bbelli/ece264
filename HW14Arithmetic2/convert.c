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
  //ListNode *a = arithlist->head;
  int currentPrec = 0; //Stores precedence of iteration nodes precedence. 
 // int tailPrec = 0; //Will store the tails precedence for comparision. 
  //int temp; //temp variable
  //bool parantheses = false;
  List * operators = malloc(sizeof(List)); //Link to store operators
  List * outputs = malloc(sizeof(List)); //Link to store outputs 
  operators->head = NULL;
  operators->tail = NULL;
  outputs->head = NULL;
  outputs->tail = NULL;
  //Do initial iteration through arithlist. Count amount of operators there are in List. 
  while(iteration != NULL){ //0 1 or 2
    if(isOperator(iteration->word) >= 0){ //If current node is operator
        currentPrec = isOperator(iteration->word); //precedence of current node
        if((currentPrec == 0) ||(currentPrec == 1) || (currentPrec == 2)){
          if(operators->head == NULL){
            addNode(operators, iteration->word);
          }
          else{
          //tailPrec = isOperator(operators->tail->word); //precedence of tail node
          while(operators->head != NULL && isOperator(operators->tail->word) > currentPrec && isOperator(operators->tail->word) < 3){
            addNode(outputs, operators->tail->word);
            deleteNode(operators, operators->tail);
          }
            addNode(operators, iteration->word);
          }
        }
        else if(currentPrec == 3){
          addNode(operators, iteration->word);
        }
        else if((currentPrec == 4)){
            while((isOperator(operators->tail->word) != 3) && (operators->tail != NULL)){
              addNode(outputs, operators->tail->word);
              deleteNode(operators, operators->tail);
           }
            deleteNode(operators, operators->tail);
        }
    } //END OF: if(isOperator(iteration->word) >= 0)
    else{ //if current iteration is not a operator, add integer to outputs.  
      addNode(outputs, iteration->word);
    }    
    iteration = iteration->next; //iterate to next
  }


  ListNode *tempNode = iteration;
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
      //      // a = operators->head;
      // while(a){
      //   printf("operators: %s\n", a->word);
      //   a = a->next;
      // }  

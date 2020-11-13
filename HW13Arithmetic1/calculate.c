// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calculate.h"

// DO NOT MODIFY FROM HERE --->>>
const int Operations[] = {'+', '-', '*'};

// return -1 if the word is not an operator
// return 0 if the word contains '+'
// return 1 if the word contains '-'
// ...
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
// *** You MUST modify the calculate function
// ***
#ifdef TEST_CALCULATE
// if arithlist is NULL, return true
// if arithlist -> head is NULL, return true
// if the input list is invalid, return false
bool calculate(List * arithlist)
{
  if (arithlist == NULL)
    {
      return true;
    }
  if ((arithlist -> head) == NULL)
    {
      return true;
    }
  // go through the list until there is only node in the list
  // find the next operator
  // If no operator can be found, return false
  // If an operator is found, find the two previous nodes as operands
  // If cannot find previous two operands, return false
  // If two operands can be found, perform the arithmetic operation
  // Be careful, subtraction is no commutative: 4 2 - means 4 - 2,
  //    not 2 - 4
  // After the operation,
  //     put the result back to the list
  //     remove the two nodes used to store the two operands
  // After going through the entire list and performing the operations,
  //     the list should have exactly one node left. If this is not
  //     true, return false
  // If the input is valud, return true
  ListNode *a = arithlist->head;
  int operator;
  int count = 0;
  int intCount = 0;
  long op1int = 0;
  long op2int = 0;
  while(a){ //Check if operator exists in List
    //ListNode *temp = a->next;
    if(isOperator(a->word) >= 0){
      count++;
    }
    else if(isOperator(a->word) == -1){
      intCount++;
    }
    //printf("calcNode: %s\n", a->word);
    a = a->next;
  }
  if(((count < 1) && (intCount != 1)) || (intCount == 0) ){ //If no operand, return false. 
    return false;
  }
  a = arithlist->head;
  count = 0;
  while(a){
     //printf("calcNode: %s\n", a->word);
    if(isOperator(a->word) >= 0){
      operator = isOperator(a->word);
      ListNode *operand2 = a->prev; //2, 3, +
      //printf("operand2: %s\n", operand2->word);
      ListNode *operand1 = operand2->prev;
      //printf("operand1: %s\n", operand1->word);
      char results[36];
      // If an operator is found, find the two previous nodes as operands
      if((operand2 == NULL) ||(operand1 == NULL)){ // If cannot find previous two operands, return false
        return false;
      }
      op1int = strtol(operand1->word, NULL, 10);
      op2int = strtol(operand2->word, NULL, 10);
      if(operator == -1){
        return false;
      }
      if(operator == 0){ //SUM
      int sum = op1int + op2int;
      sprintf(results, "%d\n", sum); //Convert int to char
      strcpy(a->word, results); //Replace temp->word with result.
      deleteNode(arithlist, operand1); //Delete operand 1
      deleteNode(arithlist, operand2); //Delete operand 2
      }
      if(operator == 1){ //SUB
      int sub = op1int - op2int;
      sprintf(results, "%d\n", sub); //Convert int to char
      strcpy(a->word, results); //Replace temp->word with result. 
      deleteNode(arithlist, operand1); //Delete operand 1
      deleteNode(arithlist, operand2); //Delete operand 2
      }
      if(operator == 2){ //MULT
      int mult = op1int * op2int;
      sprintf(results, "%d\n", mult); //Convert int to char
      strcpy(a->word, results); //Replace temp->word with result. 
      deleteNode(arithlist, operand1); //Delete operand 1
      deleteNode(arithlist, operand2); //Delete operand 2
      }
      operand1 = NULL;
      operand2 = NULL;
      a = arithlist->head;
      count++;
    }
    else{
      a = a->next;
    }
  }
  a = arithlist->head;
  arithlist->tail->next = NULL;
  arithlist->head->prev = NULL;
  a = arithlist->head;
  

  // after going through the entire list and performing the operations,
  //     the list should have exactly one node left. If this is not
  //     true, return false
  int final = isOperator(arithlist->head->word);
  if((arithlist->head->next == NULL) && (arithlist->tail->next == NULL) ){
    if(final == -1){ //If last node is an operator, return false. 
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}
#endif
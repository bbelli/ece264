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
  long op1int = 0;
  long op2int = 0;
  while(a){ 
    ListNode *temp = a->next;
    if(isOperator(temp->word)){
      count++;
    }
    a = a->next;
  }
  if(count < 1){
    return false;
  }
  a = arithlist->head;
  while(a->next){
    ListNode *temp = a->next;
    if(isOperator(temp->word)){
      ListNode *operand1 = NULL;
      ListNode *operand2 = NULL;
      //char *junk;
      char results[36];
      operand2 = temp->prev; 
      operand1 = operand2->prev;
      op1int = strtol(operand1->word, NULL, 36);
      op2int = strtol(operand2->word, NULL, 36);
      operator = isOperator(temp->word);
      if(operator == -1){
        return false;
      }
      if(operator == 0){ //SUM
      int sum = op1int + op2int;
      sprintf(results, "%d", sum);
      strcpy(temp->word, results);
      deleteNode(arithlist, operand1);
      deleteNode(arithlist, operand2);
      }
      if(operator == 1){ //SUB
      int sub = op1int - op2int;
      sprintf(results, "%d", sub);
      strcpy(temp->word, results);
      deleteNode(arithlist, operand1);
      deleteNode(arithlist, operand2);
      }
      if(operator == 2){ //MULT
      int mult = op1int - op2int;
      sprintf(results, "%d", mult);
      strcpy(temp->word, results);
      deleteNode(arithlist, operand1);
      deleteNode(arithlist, operand2);
      }
    }
  }
  if((a->next == NULL) & (a->word == NULL)){
    if(isOperator(a->word) == (0 || 1 || 2)){
      return false;
    }
    else{
      return true;
    }
  }
  else{
    return false;
  }
}
#endif

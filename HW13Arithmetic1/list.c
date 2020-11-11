// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#ifdef TEST_READLIST
// read line by line from the input file
// each line shorter than WORDLENGTH (including '\n' and '\0')
// arithlist should have memory to store head and tail
// If arithlist is NULL, return false
// If fopen fails, return false
// If a line is too long,
//    free memory of the list
//    fclose
//    return false
// If everything is fine
//    fclose
//    arithlist points to the head and tail of the list
//    return true
bool readList(char * filename, List * arithlist){
  // If arithlist is NULL, return false
  if(arithlist == NULL){
    return false;
  }
  FILE *fptr = fopen(filename, "r");
  // If fopen fails, return false
  if(fptr == NULL){
    return false;
  }
  char inputs[WORDLENGTH];
  while(fgets(inputs, WORDLENGTH, fptr) != NULL){
    if(strchr(inputs, '\n') == NULL){
      deleteList(arithlist); //free memory of the list
      fclose(fptr); //fclose
      return false;
    }
    addNode(arithlist, inputs);
  }
  fclose(fptr);
  return true;
}
#endif

#ifdef TEST_DELETELIST
// If arithlist is NULL, do nothing
// release the memory of every node in the list
// release the memory of the list 
void deleteList(List * arithlist){
  
  if(arithlist == NULL){
    return;
  }
  ListNode *a = arithlist->head;

  while(a){
    ListNode *temp = a->next;
    free(a); // release the memory of every node in the list
    a = temp;
  }
    free(arithlist); // release the memory of the list 
}
#endif

#ifdef TEST_ADDNODE
// Input: 
// arithlist stores the addresses of head and tail
// If arithlist is NULL, do nothing
// word is the word to be added
//
// Output:
// a ListNode is added to the end (become tail)
//
// allocate memory for a new ListNode
// copy word to the word attribute of the new ListNode
// insert the ListNode to the list
void addNode(List * arithlist, char * word){
  // If arithlist is NULL, do nothing
  if(arithlist == NULL){
    return;
  }
  // allocate memory for a new ListNode
  ListNode * newNode = malloc(sizeof(ListNode));
  strcpy(newNode->word, word); //Copy word given by function argument into newNode.
  newNode->prev = NULL;
  newNode->next = NULL;
  ListNode * currentTail = arithlist->tail; //store current tail
  arithlist->tail->next = newNode; //set newNode as new tail (add newNode to the very end)
  newNode->prev = currentTail; //set newNode as new tail
  newNode->next = NULL; //set tail->next = NULL;
}
#endif

#ifdef TEST_DELETENODE
//  Input:
// arithlist stores the addresses of head and tail
// If arithlist is NULL, return false
// If the list is empty (head and tail are NULL), return false
// ln is the node to be deleted
// If ln is not in the list, return false
// 
// Output:
// arithlist stores the addresses of head and tail
//   after ln is deleted
// return true.
//
// Be careful about delete the first or the last node
bool deleteNode(List * arithlist, ListNode * ln){
  // If arithlist is NULL, return false
  // If the list is empty (head and tail are NULL), return false
  if((arithlist == NULL) || ((arithlist->head == NULL) && (arithlist->tail == NULL))){
    return false;
  }
// If ln is not in the list, return false
//Search for ln in while loop. 
  ListNode * a = arithlist->head;
  while(a){
    if(a == ln){
      break;
    }
    a = a->next;
  }
  //If temp cannot find ln in while loop, return false. 
  // If ln is not in the list, return false
  if(a != ln){
    return false;
  }
  //It is possible that ln is the first node in the list (i.e.,
  // the head). If this occurs, return the second node of the list.
  if((arithlist->head) == ln){
    ListNode * secondNode = arithlist->head->next;
    arithlist->head = secondNode;
    free(arithlist->head);
    return true;
  }
   //It is possible that ln is the tail node in the list (i.e.,
  // the tail). If this occurs, return the second node from the tail of the list.
    if((arithlist->tail) == ln){
    ListNode * secondNode = arithlist->tail->prev;
    free(arithlist->tail);
    arithlist->tail = secondNode;
    return true;
  }
  if(ln != NULL){ //3. If todelete is  in the list, delete.
    ln->prev->next = ln->next;
    ln->next->prev = ln->prev;
    free(ln);
  }
  return true;
}
#endif


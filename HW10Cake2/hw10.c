// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include "hw10.h"

// DO NOT MODIFY this function --->>>
void printListNode(ListNode * head)
{
  ListNode * p = head;
  printf("printListNode: ");
  while (p != NULL)
    {
      printf("%7d ", p -> value);
      p = p -> next;
    }
  printf("\n");
}
// <<<--- until here

// You MUST modify the following functions

#ifdef TEST_CREATELIST
// create a linked list storing values 0, 1, 2, ... valn - 1
// The first node (head) stores 0, the next node stores 1,
// ..., the last node stores valn - 1
// return the head of the linked listn
ListNode * createList(int valn){
  ListNode * p = NULL;
  ListNode * n = NULL;
  int values = valn - 1;
  while(values >= 0){
    n = malloc(sizeof(*n));
    n->value = values;
    n->next = p;
    p = n;//?
    values--;
  }
  return p;
}
#endif

#ifdef TEST_ELIMINATE
// eliminate the nodes in the linked list
// starting from the head, move one node at a time and count to valk.
// eliminate that node, keep counting
//
// when reaching the end of the list, continue from the beginning of
// the list
//
// print the values of the nodes to be deleted
void eliminate(ListNode * head, int valk){
  ListNode * p = head;
  int count = 1;
  while(head->next != NULL){
     if(count == valk){
        #ifdef DEBUG
        ListNode * todelete = p;
        printListNode(todelete);
        #endif
        p = deleteNode(head, todelete);
        count = 1;
        if((p) == NULL){
          p = head;
        }
     }
     else{
       if((p->next) == NULL ){
         p = head;
       }
       else{
         p = p->next;
       }
       count++;
     }
  }
}
// #ifdef DEBUG
//   // this #ifdef ... #endif should be inside the condition *BEFORE* a
//   // node' value is printed and it is deleted
//   ListNode * todelete = p; //Does this take care of assigning the value? No need to do anything in/after while loop?
//   printListNode (todelete); 
// #endif
#endif

#ifdef TEST_DELETENODE
// head points to the first node in the linked list
// todelete points  to the node to be deleted
//
// delete the node and return the head of the linked list
// release the memory of the deleted node
//
// should check several conditions:
// 1. If head is NULL, the list is empty and this function returns
//    NULL
// 2. If todelete is NULL, nothing can be deleted, return head
// 3. If todelete is not in the list, keep the list unchanged and
//    return head
// It is possible that todelete is the first node in the list (i.e.,
// the head). If this occurs, return the second node of the list.
ListNode * deleteNode(ListNode * head, ListNode * todelete){
  ListNode * p = head;
  ListNode * q = p->next; //to be deleted
  ListNode * returnNode = todelete->next;
  //1. If head is NULL, the list is empty and this function returns NULL
  if(head == NULL){
    return returnNode;
  }
  //2. If todelete is NULL, nothing can be deleted, return head
  if(todelete == NULL){
    return returnNode;
  }
  //Delete

  if(head == todelete){
    free(head);
    return returnNode; 
  }
  //Find todelete value in the Linked List and delete
  while((q!= NULL) && ((q->value) != (todelete->value))){
    p = p->next;
    q = q->next;
  }
  if(q != NULL){ //3. If todelete is  in the list, delete.
    p->next = q->next;
    free(q);
  }
  return returnNode;
}
#endif

// void eliminate(ListNode * head, int valk){
//   ListNode * p = head;
//   int count = 1;
//   while(head->next != NULL){
//     count = valk;
//     while((count) > 0 ){ 
//         if(p != NULL){
//           count--;
//         }
//         #ifdef DEBUG
//         // this #ifdef ... #endif should be inside the condition *BEFORE* a
//         // node' value is printed and it is deleted
//         ListNode * todelete = p; 
//         printListNode (todelete); 
//         #endif
//         ListNode * newHead = deleteNode(head, p);
//         ListNode * check = p->next;
//         if(check == NULL){
//           p = newHead;
//         }
//         else{
//           p = check;
//         }
//     } /
//   }
// #ifdef TEST_DELETENODE
// // head points to the first node in the linked list
// // todelete points  to the node to be deleted
// //
// // delete the node and return the head of the linked list
// // release the memory of the deleted node
// //
// // should check several conditions:
// // 1. If head is NULL, the list is empty and this function returns
// //    NULL
// // 2. If todelete is NULL, nothing can be deleted, return head
// // 3. If todelete is not in the list, keep the list unchanged and
// //    return head
// // It is possible that todelete is the first node in the list (i.e.,
// // the head). If this occurs, return the second node of the list.
// ListNode * deleteNode(ListNode * head, ListNode * todelete){
//   //1. If head is NULL, the list is empty and this function returns NULL
//   if(head == NULL){
//     return NULL;
//   }
//   //2. If todelete is NULL, nothing can be deleted, return head
//   if(todelete == NULL){
//     return head;
//   }
//   //Delete
//   //If todelete node is the first node
//   ListNode * p = head;
//   ListNode * q = p->next; //to be deleted
//   if(head == todelete){
//     p = head-> next; //Is this correct?
//     free(head);
//     return p; 
//   }
//   //Find todelete value in the Linked List and delete
//   while((q!= NULL) && ((q->value) != (todelete->value))){
//     p = p->next;
//     q = q->next;
//   }
//   if(q != NULL){ //3. If todelete is  in the list, delete.
//     p->next = q->next;
//     free(q);
//   }
//   return head;
// }
// #endif
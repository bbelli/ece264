// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

// DO NOT MODIFY FROM HERE --->>>
Tree * newTree(void)
{
  Tree * t = malloc(sizeof(Tree));
  t -> root = NULL;
  return t;
}

void deleteTreeNode(TreeNode * tr)
{
  if (tr == NULL)
    {
      return;
    }
  deleteTreeNode (tr -> left);
  deleteTreeNode (tr -> right);
  free (tr);
}

void freeTree(Tree * tr)
{
  if (tr == NULL)
    {
      // nothing to delete
      return;
    }
  deleteTreeNode (tr -> root);
  free (tr);
}


// <<<--- UNTIL HERE

// ***
// *** You MUST modify the follow function
// ***
#ifdef TEST_BUILDTREE

TreeNode* newNode(int value){
  TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
  node->value = value;
  node->left = node->right = NULL;
  return (node);
}

int search(int arr[], int start, int end, int value){
  int i;
  for (i=start; i <= end; i++){
    if (arr[i] == value){
      break;
    }
  }
  return i;
}

TreeNode * buildUtil(int *in, int *post , int inStrt, int inEnd, int* pIndex){
  if (inStrt > inEnd){
    return NULL;
  }
  TreeNode* node = newNode(post[*pIndex]);
  (*pIndex)--;

  if(inStrt == inEnd){
    return node;
  }
  int iIndex = search(in, inStrt, inEnd, node->value);

  node->right = buildUtil(in, post, iIndex + 1, inEnd, pIndex);
  node->left = buildUtil(in, post, inStrt, iIndex - 1, pIndex);

  return node;

}


Tree * buildTree(int * inArray, int * postArray, int size){
  //int pIndex = size - 1; 
  Tree * tr = malloc(sizeof(Tree));
  int postIndex = size - 1;
  tr -> root = buildUtil(inArray, postArray, 0, size - 1, & postIndex);
  return tr;

  //return buildUtil(inArray, postArray, 0, size - 1, &pIndex); 
}
#endif

#ifdef TEST_PRINTPATH
void printPath(Tree * tr, int val){
  printf("Root: %d\n", tr->root->value);
  printf("n1: %d\n", tr->root->left->value);
  printf("2: %d\n", tr->root->left->left->value);
  TreeNode* leftSide = tr->root;
  TreeNode* rightSide = tr->root;
  bool side;

  while(leftSide){
    if(leftSide->value == val){
      side = false;
      printf("BB : %d\n", leftSide->value);
      break;
    } else{
    leftSide = leftSide->left;
    }
  }
  while(rightSide){
    if(rightSide->value == val){
      side = true;
      printf("AA: %d\n", rightSide->value);
      break;
    } else{
    rightSide = rightSide->right;
    }
  }
  if(side){
    while(rightSide){
      printf("%d\n", rightSide->value);
      rightSide = rightSide->left;
    } 
  }
  // else{
  //   while(leftSide){
  //     printf("%d", rightSide->value);
  //     leftSide = leftSide->right;
  //   } 
  // }


  //free(rightSide);
  //free(leftSide);
}
#endif

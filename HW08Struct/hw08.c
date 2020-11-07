// ***
// *** You must modify this file
// ***
#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "hw08.h"
//#include "hw08.c"


#ifdef TEST_COUNTVECTOR
int countVector(char * filename)
{
  // count the number of vectors in the file and return the number
  // The input is a binary file. You must use fread.
  // You must not use fscanf(, "%d", ) 
  //
  // If fopen fails, return -1
  Vector a;
  FILE *fptr = fopen(filename, "r");
  if(fptr == NULL){
    return -1;
  }
  int counter = 0;
  while(fread(&a, sizeof(Vector), 1, fptr)){
    counter++;
  }
  fclose(fptr);
  return counter;
}
#endif

#ifdef TEST_READVECTOR
bool readVector(char* filename, Vector * vecArr, int size)
{
  // if fopen fails, return false
  FILE *fptr = fopen(filename, "r");
  if(fptr == NULL){
    return false;
  }
  // read Vectors from the file.
  int counter = 0;
  counter = fread(&vecArr[0], sizeof(Vector), size, fptr);
  // if the number of integers is different from size (too
  // few or too many) return false
  if(counter != size){
    fclose(fptr);
    return false;
  }
  // 
  // if everything is fine, fclose and return true
  fclose(fptr);
  return true;
}
#endif

#ifdef TEST_COMPAREVECTOR
int compareVector(const void *p1, const void *p2)
{
  const Vector* vec1 = (const Vector *) p1;
  const Vector* vec2 = (const Vector *) p2;
  // compare the x attribute first
  // If the first vector's x is less than the second vector's x
  if((vec1->x) < (vec2->x)){
    return -1;
  }
  
  // If the first vector's x is greater than the second vector's x
  if((vec1->x) > (vec2->x)){
    return 1;
  }
  // If the two vectors' x is the same, compare the y attribute
  if((vec1->x) == (vec2->x)){
  // If the first vector's y is less than the second vector's y
    if((vec1->y) < (vec2->y)){
      return -1;
    }
  // If the first vector's y is greater than the second vector's y
    if((vec1->y) > (vec2->y)){
      return 1;
    }
  // If the two vectors' y is the same, compare the z attribute
  // If the first vector's z is less than the second vector's z
    if((vec1->y) == (vec2->y)){
      if((vec1->z) < (vec2->z)){
        return -1;
      }  
      if((vec1->z) > (vec2->z)){
        return 1;
      }
  // If the two vectors' x, y, z are the same (pairwise), return 0
    }
  }
  return 0;
}
#endif

#ifdef TEST_WRITEVECTOR
bool writeVector(char* filename, Vector * vecArr, int size)
{
  // if fopen fails, return false
  FILE *fptr = fopen(filename, "w");
  if(fptr == NULL){
    return false;
  }
  // read Vectors from the file.
  int counter = 0;
  //while(fread(&vecArr, sizeof(Vector), ,filename)){
  counter = fwrite(&vecArr[0], sizeof(Vector), size, fptr);
  //} 
  // if the number of integers is different from size (too
  // few or too many) return false
  if(counter != size){
    fclose(fptr);
    return false;
  }
  // 
  // if everything is fine, fclose and return true
  fclose(fptr);
  return true;
}
#endif

// This function is provided to you. No need to change
void printVector(Vector * vecArr, int size)
{
  int ind = 0;
  for (ind = 0; ind < size; ind ++)
    {
      printf("%6d %6d %6d\n",
	     vecArr[ind].x, vecArr[ind].y, vecArr[ind].z);
    }
}

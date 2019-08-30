/* Copyright (C) 2019 by Angel de Vicente, angel@iac.es 
   https://github.com/angel-devicente/                     */

/******************************************************************
* Angel de Vicente 
*
* A simple program to perform memoization with dynamic jagged arrays
* 
******************************************************************
* TO DO: 
*   + add proper description
*   + add error handling to code
******************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "memoization_ja.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)
#define ERROR { fprintf(stderr, "ERROR at %s: %s\n", AT,strerror( errno )); exit(EXIT_FAILURE); }

/************************************************************** 
*
* Inserting functions for 1D-6D memoization jagged arrays 
*
**************************************************************/
int place_val1D(int st, int l1, double val, strip1D *A) {
  for(int i=st; i<=l1; i++){
    if (i == l1) {
      if ( ! (A->s[i] = (double *)malloc(sizeof(double))) ) ERROR;
      *(A->s[i]) = val; 
    } else {
      A->s[i] = NULL;
    }
  }
  return 0;
}

int insert1D(int l1, double val, strip1D *A) {
  double **tmp;
  
  if (A->size > 0) {
    if (l1 < A->size) {
      if (A->s[l1]) {   // already stored, noop 
      } else {          // no link to value, adding  
	if ( ! (A->s[l1] = (double *)malloc(sizeof(double))) ) ERROR;
	*(A->s[l1]) = val;
      }
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      if ( ! (tmp = realloc(A->s,sizeof(double*)*(s1))) ) ERROR;
      A->s=tmp;
      place_val1D(p_s1,l1,val,A);
      
    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    if ( ! (A->s = (double**)malloc(sizeof(double*)*(s1))) ) ERROR;
    place_val1D(0,l1,val,A);
  }

  return 0;
}


int insert2D(int l1, int l2, double val, strip2D *A) {
  strip1D *tmp;
  
  if (A->size > 0) {
    if (l1 < A->size) {
      insert1D(l2,val,&(A->s[l1]));
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      if ( ! (tmp = realloc(A->s,sizeof(strip1D)*(s1))) ) ERROR;
      A->s=tmp;

      for(int i=p_s1; i<=l1; i++){
	(A->s[i]).size = 0;
      }
      insert1D(l2,val,&(A->s[l1]));

    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    if ( ! (A->s = (strip1D*)malloc(sizeof(strip1D)*(s1)))) ERROR;
    for(int i=0; i<=l1; i++){
      A->s[i].size = 0;
    }
    insert1D(l2,val,&(A->s[l1]));
  }

  return 0;
}


int insert3D(int l1, int l2, int l3, double val, strip3D *A) {
  strip2D *tmp;
  
  if (A->size > 0) {
    if (l1 < A->size) {
      insert2D(l2,l3,val,&(A->s[l1]));
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      if ( ! (tmp = realloc(A->s,sizeof(strip2D)*(s1))) ) ERROR;
      A->s=tmp;

      for(int i=p_s1; i<=l1; i++){
	(A->s[i]).size = 0;
      }
      insert2D(l2,l3,val,&(A->s[l1]));

    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    if ( ! (A->s = (strip2D*)malloc(sizeof(strip2D)*(s1))) ) ERROR;
    for(int i=0; i<=l1; i++){
      A->s[i].size = 0;
    }
    insert2D(l2,l3,val,&(A->s[l1]));
  }

  return 0;
}


int insert4D(int l1, int l2, int l3, int l4, double val, strip4D *A) {
  strip3D *tmp;
  
  if (A->size > 0) {
    if (l1 < A->size) {
      insert3D(l2,l3,l4,val,&(A->s[l1]));
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      if ( ! (tmp = realloc(A->s,sizeof(strip3D)*(s1))) ) ERROR;
      A->s=tmp;

      for(int i=p_s1; i<=l1; i++){
	(A->s[i]).size = 0;
      }
      insert3D(l2,l3,l4,val,&(A->s[l1]));

    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    if ( ! (A->s = (strip3D*)malloc(sizeof(strip3D)*(s1))) ) ERROR;
    for(int i=0; i<=l1; i++){
      A->s[i].size = 0;
    }
    insert3D(l2,l3,l4,val,&(A->s[l1]));
  }

  return 0;
}


int insert5D(int l1, int l2, int l3, int l4, int l5, double val, strip5D *A) {
  strip4D *tmp;
  
  if (A->size > 0) {
    if (l1 < A->size) {
      insert4D(l2,l3,l4,l5,val,&(A->s[l1]));
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      if ( ! (tmp = realloc(A->s,sizeof(strip4D)*(s1))) ) ERROR;
      A->s=tmp;

      for(int i=p_s1; i<=l1; i++){
	(A->s[i]).size = 0;
      }
      insert4D(l2,l3,l4,l5,val,&(A->s[l1]));

    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    if ( ! (A->s = (strip4D*)malloc(sizeof(strip4D)*(s1))) ) ERROR;
    for(int i=0; i<=l1; i++){
      A->s[i].size = 0;
    }
    insert4D(l2,l3,l4,l5,val,&(A->s[l1]));
  }

  return 0;
}


int insert6D(int l1, int l2, int l3, int l4, int l5, int l6, double val, strip6D *A) {
  strip5D *tmp;
  
  if (A->size > 0) {
    if (l1 < A->size) {
      insert5D(l2,l3,l4,l5,l6,val,&(A->s[l1]));
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      if ( ! (tmp = realloc(A->s,sizeof(strip5D)*(s1))) ) ERROR;
      A->s=tmp;

      for(int i=p_s1; i<=l1; i++){
	(A->s[i]).size = 0;
      }
      insert5D(l2,l3,l4,l5,l6,val,&(A->s[l1]));

    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    if ( ! (A->s = (strip5D*)malloc(sizeof(strip5D)*(s1))) ) ERROR;
    for(int i=0; i<=l1; i++){
      A->s[i].size = 0;
    }
    insert5D(l2,l3,l4,l5,l6,val,&(A->s[l1]));
  }

  return 0;
}


/************************************************************** 
*
* Searching function for 6D memoization jagged arrays 
*
* Returns: NULL if element not in Jagged_Array.
*          Pointer to value if present in Jagged_Array
*
* TODO: my main goal was a 6D jagged array, so for the moment 
* I only wrote the searching for 6Ds, but it is trivial to
* write the 1D-5D versions.
**************************************************************/
double* elem6D(int l1,int l2,int l3,int l4,int l5,int l6,strip6D A) {
  if (A.size > l1 &&
      A.s[l1].size > l2 &&
      A.s[l1].s[l2].size > l3 &&
      A.s[l1].s[l2].s[l3].size > l4 &&
      A.s[l1].s[l2].s[l3].s[l4].size > l5 &&
      A.s[l1].s[l2].s[l3].s[l4].s[l5].size > l6)
    return A.s[l1].s[l2].s[l3].s[l4].s[l5].s[l6];

  return NULL;
}


/************************************************************** 
*
* Basic printing functions for 1D-6D memoization jagged arrays 
*
**************************************************************/
int print_jA1D(strip1D A) {
  printf("----------- \n"); 
  for (int i=0; i<A.size; i++) {
    if (A.s[i]) {
      printf("A[%d] is: %f \n",i,*(A.s[i]));
    }
  }
  return 0;
}


int print_jA2D(strip2D A) {
  printf("----------- \n");
  for (int i=0; i<A.size; i++) {
    for (int j=0; j<A.s[i].size; j++) {
      if (A.s[i].s[j]) {
	printf("A[%d,%d] is: %f \n",i,j,*(A.s[i].s[j]));
      }
    }
  }
  return 0;
}


int print_jA3D(strip3D A) {
  printf("----------- \n");
  for (int i=0; i<A.size; i++) {
    for (int j=0; j<A.s[i].size; j++) {
      for (int k=0; k<A.s[i].s[j].size; k++) {
  	if (A.s[i].s[j].s[k]) {
	  printf("A[%d,%d,%d] is: %f \n",i,j,k,*(A.s[i].s[j].s[k]));
	}
      }
    }
  }
  return 0;
}


int print_jA4D(strip4D A) {
  printf("----------- \n");
  for (int i1=0; i1<A.size; i1++) {
    for (int i2=0; i2<A.s[i1].size; i2++) {
      for (int i3=0; i3<A.s[i1].s[i2].size; i3++) {
	for (int i4=0; i4<A.s[i1].s[i2].s[i3].size; i4++) {
	  if (A.s[i1].s[i2].s[i3].s[i4]) {
	    printf("A[%d,%d,%d,%d] is: %f \n",i1,i2,i3,i4,*(A.s[i1].s[i2].s[i3].s[i4]));
	  }
	}
      }
    }
  }
  return 0;
}

int print_jA5D(strip5D A) {
  printf("----------- \n");
  for (int i1=0; i1<A.size; i1++) {
    for (int i2=0; i2<A.s[i1].size; i2++) {
      for (int i3=0; i3<A.s[i1].s[i2].size; i3++) {
	for (int i4=0; i4<A.s[i1].s[i2].s[i3].size; i4++) {
	  for (int i5=0; i5<A.s[i1].s[i2].s[i3].s[i4].size; i5++) {
	    if (A.s[i1].s[i2].s[i3].s[i4].s[i5]) {
	      printf("A[%d,%d,%d,%d,%d] is: %f \n",i1,i2,i3,i4,i5,*(A.s[i1].s[i2].s[i3].s[i4].s[i5]));
	    }
	  }
	}
      }
    }
  }
  return 0;
}


int print_jA6D(strip6D A) {
  printf("----------- \n");
  for (int i1=0; i1<A.size; i1++) {
    for (int i2=0; i2<A.s[i1].size; i2++) {
      for (int i3=0; i3<A.s[i1].s[i2].size; i3++) {
	for (int i4=0; i4<A.s[i1].s[i2].s[i3].size; i4++) {
	  for (int i5=0; i5<A.s[i1].s[i2].s[i3].s[i4].size; i5++) {
	    for (int i6=0; i6<A.s[i1].s[i2].s[i3].s[i4].s[i5].size; i6++) {
	      if (A.s[i1].s[i2].s[i3].s[i4].s[i5].s[i6]) {
		printf("A[%d,%d,%d,%d,%d,%d] is: %f \n",i1,i2,i3,i4,i5,i6,*(A.s[i1].s[i2].s[i3].s[i4].s[i5].s[i6]));
	      }
	    }
	  }
	}
      }
    }
  }
  return 0;
}






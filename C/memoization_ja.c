/* Copyright (C) 2019 by Angel de Vicente, angel.de.vicente@iac.es 
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
#include <limits.h>
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

/***********************
 * place_val1D
 *
 * will set NULL for all positions from [st:end]
 *        and to val at position 'l1'
 *
 * s0 points to where the index for 0 would be, so we can 
 *        use negative indices 
 *
 **********************/
int place_val1D(int st, int end, int l1, double val, strip1D *A) {
  for(int i=st; i<=end; i++)  A->s0[i] = NULL;

  if ( ! (A->s0[l1] = (double *)malloc(sizeof(double))) ) ERROR;
  *(A->s0[l1]) = val; 

  return 0;
}

/***********************
 * insert1D
 *
 * will set NULL for all positions from [st:end]
 *        and to val at position 'l1'
 *
 * s0 points to where the index for 0 would be, so we can 
 *        use negative indices 
 *
 **********************/
int insert1D(int l1, double val, strip1D *A) {
  double **tmp, **tmp0;
  
  if (A->s0) {
    if (l1 >= A->min && l1 <= A->max) {
      if (A->s0[l1]) {           // already stored, noop 
      } else {                   // no link to value, adding  
	if ( ! (A->s0[l1] = (double *)malloc(sizeof(double))) ) ERROR;
	*(A->s0[l1]) = val;
      }
    } else {                    // not big enough: realloc and place value
      int n_min = l1 < A->min ? l1 : A->min;
      int n_max = l1 > A->max ? l1 : A->max;
      int n_size = n_max - n_min + 1;
      
      if ( ! (tmp = (double **) malloc(sizeof(double*)*(n_size))) ) ERROR;
      tmp0 = &(tmp[abs(n_min)]);
      for (int i=A->min; i <= A->max; i++) tmp0[i] = A->s0[i];

      free(A->s);
      A->s = tmp;
      A->s0 = tmp0;

      if (n_min < A->min) {     // we extended the array in the low part
	place_val1D(n_min,A->min - 1,l1,val,A);
      } else {                 // we extended the array in the high part
	place_val1D(A->max +1,n_max,l1,val,A);
      }

      A->max = n_max;
      A->min = n_min;

    }
  } else {                         // dimension does not exist yet: create and place value
    A->min = l1 < 0 ? l1 : 0;  
    A->max = l1 < 0 ? 0 : l1;
    int size = A->max - A->min + 1;
    if ( ! (A->s = (double**)malloc(sizeof(double*)*(size))) ) ERROR;
    A->s0 = &(A->s[abs(A->min)]);   // if negative indices, s0 will point somewhere
				    // in the array, not the first position
    place_val1D(A->min, A->max, l1, val, A);
  }

  return 0;
}


/***********************
 * insert2D
 *
 * similar idea to insert1D
 **********************/
int insert2D(int l1, int l2, double val, strip2D *A) {
  strip1D *tmp, *tmp0;
  
  if (A->s0) {
    if (l1 >= A->min && l1 <= A->max) {
      insert1D(l2,val,&(A->s0[l1]));
    } else {                    // not big enough: realloc and place value
      int n_min = l1 < A->min ? l1 : A->min;
      int n_max = l1 > A->max ? l1 : A->max;
      int n_size = n_max - n_min + 1;
      
      if ( ! (tmp = (strip1D*) malloc(sizeof(strip1D)*(n_size))) ) ERROR;
      tmp0 = &(tmp[abs(n_min)]);
      for (int i=A->min; i <= A->max; i++) tmp0[i] = A->s0[i];

      free(A->s);
      A->s = tmp;
      A->s0 = tmp0;

      if (n_min < A->min) {     // we extended the array in the low part
	for(int i=n_min; i<=A->min-1; i++){
	  A->s0[i].min = INT_MAX;
	  A->s0[i].max = INT_MIN;
	  A->s0[i].s = NULL;
	  A->s0[i].s0 = NULL;
	}
      } else {                 // we extended the array in the high part
	for(int i=A->max+1; i<=n_max; i++){
	  A->s0[i].min = INT_MAX;
	  A->s0[i].max = INT_MIN;
	  A->s0[i].s = NULL;
	  A->s0[i].s0 = NULL;
	}
      }
      insert1D(l2,val,&(A->s0[l1]));
      
      A->max = n_max;
      A->min = n_min;

    }
    
  } else {                         // dimension does not exist yet: create and place value
    A->min = l1 < 0 ? l1 : 0;  
    A->max = l1 < 0 ? 0 : l1;
    int size = A->max - A->min + 1;
    if ( ! (A->s = (strip1D*)malloc(sizeof(strip1D)*(size))) ) ERROR;
    A->s0 = &(A->s[abs(A->min)]);   // if negative indices, s0 will point somewhere
				    // in the array, not the first position
    for(int i=A->min; i<=A->max; i++){
      A->s0[i].min = INT_MAX;
      A->s0[i].max = INT_MIN;
      A->s0[i].s = NULL;
      A->s0[i].s0 = NULL;
    }
    insert1D(l2,val,&(A->s0[l1]));
  }

  return 0;
}


/***********************
 * insert3D
 *
 * similar idea to insert1D
 **********************/
int insert3D(int l1, int l2, int l3, double val, strip3D *A) {
  strip2D *tmp, *tmp0;
  
  if (A->s0) {
    if (l1 >= A->min && l1 <= A->max) {
      insert2D(l2,l3,val,&(A->s0[l1]));
    } else {                    // not big enough: realloc and place value
      int n_min = l1 < A->min ? l1 : A->min;
      int n_max = l1 > A->max ? l1 : A->max;
      int n_size = n_max - n_min + 1;
      
      if ( ! (tmp = (strip2D*) malloc(sizeof(strip2D)*(n_size))) ) ERROR;
      tmp0 = &(tmp[abs(n_min)]);
      for (int i=A->min; i <= A->max; i++) tmp0[i] = A->s0[i];

      free(A->s);
      A->s = tmp;
      A->s0 = tmp0;

      if (n_min < A->min) {     // we extended the array in the low part
	for(int i=n_min; i<=A->min-1; i++){
	  A->s0[i].min = INT_MAX;
	  A->s0[i].max = INT_MIN;
	  A->s0[i].s = NULL;
	  A->s0[i].s0 = NULL;
	}
      } else {                 // we extended the array in the high part
	for(int i=A->max+1; i<=n_max; i++){
	  A->s0[i].min = INT_MAX;
	  A->s0[i].max = INT_MIN;
	  A->s0[i].s = NULL;
	  A->s0[i].s0 = NULL;
	}
      }
      insert2D(l2,l3,val,&(A->s0[l1]));
      
      A->max = n_max;
      A->min = n_min;

    }
    
  } else {                         // dimension does not exist yet: create and place value
    A->min = l1 < 0 ? l1 : 0;  
    A->max = l1 < 0 ? 0 : l1;
    int size = A->max - A->min + 1;
    if ( ! (A->s = (strip2D*)malloc(sizeof(strip2D)*(size))) ) ERROR;
    A->s0 = &(A->s[abs(A->min)]);   // if negative indices, s0 will point somewhere
				    // in the array, not the first position
    for(int i=A->min; i<=A->max; i++){
      A->s0[i].min = INT_MAX;
      A->s0[i].max = INT_MIN;
      A->s0[i].s = NULL;
      A->s0[i].s0 = NULL;
    }
    insert2D(l2,l3,val,&(A->s0[l1]));
  }

  return 0;
}


/***********************
 * insert4D
 *
 * similar idea to insert1D
 **********************/
int insert4D(int l1, int l2, int l3, int l4,double val, strip4D *A) {
  strip3D *tmp, *tmp0;
  
  if (A->s0) {
    if (l1 >= A->min && l1 <= A->max) {
      insert3D(l2,l3,l4,val,&(A->s0[l1]));
    } else {                    // not big enough: realloc and place value
      int n_min = l1 < A->min ? l1 : A->min;
      int n_max = l1 > A->max ? l1 : A->max;
      int n_size = n_max - n_min + 1;
      
      if ( ! (tmp = (strip3D*) malloc(sizeof(strip3D)*(n_size))) ) ERROR;
      tmp0 = &(tmp[abs(n_min)]);
      for (int i=A->min; i <= A->max; i++) tmp0[i] = A->s0[i];

      free(A->s);
      A->s = tmp;
      A->s0 = tmp0;

      if (n_min < A->min) {     // we extended the array in the low part
	for(int i=n_min; i<=A->min-1; i++){
	  A->s0[i].min = INT_MAX;
	  A->s0[i].max = INT_MIN;
	  A->s0[i].s = NULL;
	  A->s0[i].s0 = NULL;
	}
      } else {                 // we extended the array in the high part
	for(int i=A->max+1; i<=n_max; i++){
	  A->s0[i].min = INT_MAX;
	  A->s0[i].max = INT_MIN;
	  A->s0[i].s = NULL;
	  A->s0[i].s0 = NULL;
	}
      }
      insert3D(l2,l3,l4,val,&(A->s0[l1]));
      
      A->max = n_max;
      A->min = n_min;

    }
    
  } else {                         // dimension does not exist yet: create and place value
    A->min = l1 < 0 ? l1 : 0;  
    A->max = l1 < 0 ? 0 : l1;
    int size = A->max - A->min + 1;
    if ( ! (A->s = (strip3D*)malloc(sizeof(strip3D)*(size))) ) ERROR;
    A->s0 = &(A->s[abs(A->min)]);   // if negative indices, s0 will point somewhere
				    // in the array, not the first position
    for(int i=A->min; i<=A->max; i++){
      A->s0[i].min = INT_MAX;
      A->s0[i].max = INT_MIN;
      A->s0[i].s = NULL;
      A->s0[i].s0 = NULL;
    }
    insert3D(l2,l3,l4,val,&(A->s0[l1]));
  }

  return 0;
}


/***********************
 * insert5D
 *
 * similar idea to insert1D
 **********************/
int insert5D(int l1, int l2, int l3, int l4, int l5,double val, strip5D *A) {
  strip4D *tmp, *tmp0;
  
  if (A->s0) {
    if (l1 >= A->min && l1 <= A->max) {
      insert4D(l2,l3,l4,l5,val,&(A->s0[l1]));
    } else {                    // not big enough: realloc and place value
      int n_min = l1 < A->min ? l1 : A->min;
      int n_max = l1 > A->max ? l1 : A->max;
      int n_size = n_max - n_min + 1;
      
      if ( ! (tmp = (strip4D*) malloc(sizeof(strip4D)*(n_size))) ) ERROR;
      tmp0 = &(tmp[abs(n_min)]);
      for (int i=A->min; i <= A->max; i++) tmp0[i] = A->s0[i];

      free(A->s);
      A->s = tmp;
      A->s0 = tmp0;

      if (n_min < A->min) {     // we extended the array in the low part
	for(int i=n_min; i<=A->min-1; i++){
	  A->s0[i].min = INT_MAX;
	  A->s0[i].max = INT_MIN;
	  A->s0[i].s = NULL;
	  A->s0[i].s0 = NULL;
	}
      } else {                 // we extended the array in the high part
	for(int i=A->max+1; i<=n_max; i++){
	  A->s0[i].min = INT_MAX;
	  A->s0[i].max = INT_MIN;
	  A->s0[i].s = NULL;
	  A->s0[i].s0 = NULL;
	}
      }
      insert4D(l2,l3,l4,l5,val,&(A->s0[l1]));
      
      A->max = n_max;
      A->min = n_min;

    }
    
  } else {                         // dimension does not exist yet: create and place value
    A->min = l1 < 0 ? l1 : 0;  
    A->max = l1 < 0 ? 0 : l1;
    int size = A->max - A->min + 1;
    if ( ! (A->s = (strip4D*)malloc(sizeof(strip4D)*(size))) ) ERROR;
    A->s0 = &(A->s[abs(A->min)]);   // if negative indices, s0 will point somewhere
				    // in the array, not the first position
    for(int i=A->min; i<=A->max; i++){
      A->s0[i].min = INT_MAX;
      A->s0[i].max = INT_MIN;
      A->s0[i].s = NULL;
      A->s0[i].s0 = NULL;
    }
    insert4D(l2,l3,l4,l5,val,&(A->s0[l1]));
  }

  return 0;
}



/***********************
 * insert6D
 *
 * similar idea to insert1D
 **********************/
int insert6D(int l1, int l2, int l3, int l4, int l5, int l6,double val, strip6D *A) {
  strip5D *tmp, *tmp0;
  
  if (A->s0) {
    if (l1 >= A->min && l1 <= A->max) {
      insert5D(l2,l3,l4,l5,l6,val,&(A->s0[l1]));
    } else {                    // not big enough: realloc and place value
      int n_min = l1 < A->min ? l1 : A->min;
      int n_max = l1 > A->max ? l1 : A->max;
      int n_size = n_max - n_min + 1;
      
      if ( ! (tmp = (strip5D*) malloc(sizeof(strip5D)*(n_size))) ) ERROR;
      tmp0 = &(tmp[abs(n_min)]);
      for (int i=A->min; i <= A->max; i++) tmp0[i] = A->s0[i];

      free(A->s);
      A->s = tmp;
      A->s0 = tmp0;

      if (n_min < A->min) {     // we extended the array in the low part
	for(int i=n_min; i<=A->min-1; i++){
	  A->s0[i].min = INT_MAX;
	  A->s0[i].max = INT_MIN;
	  A->s0[i].s = NULL;
	  A->s0[i].s0 = NULL;
	}
      } else {                 // we extended the array in the high part
	for(int i=A->max+1; i<=n_max; i++){
	  A->s0[i].min = INT_MAX;
	  A->s0[i].max = INT_MIN;
	  A->s0[i].s = NULL;
	  A->s0[i].s0 = NULL;
	}
      }
      insert5D(l2,l3,l4,l5,l6,val,&(A->s0[l1]));
      
      A->max = n_max;
      A->min = n_min;

    }
    
  } else {                         // dimension does not exist yet: create and place value
    A->min = l1 < 0 ? l1 : 0;  
    A->max = l1 < 0 ? 0 : l1;
    int size = A->max - A->min + 1;
    if ( ! (A->s = (strip5D*)malloc(sizeof(strip5D)*(size))) ) ERROR;
    A->s0 = &(A->s[abs(A->min)]);   // if negative indices, s0 will point somewhere
				    // in the array, not the first position
    for(int i=A->min; i<=A->max; i++){
      A->s0[i].min = INT_MAX;
      A->s0[i].max = INT_MIN;
      A->s0[i].s = NULL;
      A->s0[i].s0 = NULL;
    }
    insert5D(l2,l3,l4,l5,l6,val,&(A->s0[l1]));
  }

  return 0;
}



/************************************************************** 
*
* Basic printing functions for 1D-6D memoization jagged arrays 
*
**************************************************************/
int print_jA1D(strip1D A) {
  printf("----------- \n"); 
  for (int i=A.min; i<=A.max; i++) {
    if (A.s0[i]) {
      printf("A[%d] is: %f \n",i,*(A.s0[i]));
    }
  }
  return 0;
}


int print_jA2D(strip2D A) {
  printf("----------- \n");
  for (int i=A.min; i<=A.max; i++) {
    for (int j=A.s0[i].min; j<=A.s0[i].max; j++) {
      if (A.s0[i].s0[j]) {
	printf("A[%d,%d] is: %f \n",i,j,*(A.s0[i].s0[j]));
      }
    }
  }
  return 0;
}

int print_jA3D(strip3D A) {
  printf("----------- \n");
  for (int i=A.min; i<=A.max; i++) {
    for (int j=A.s0[i].min; j<=A.s0[i].max; j++) {
      for (int k=A.s0[i].s0[j].min; k<=A.s0[i].s0[j].max; k++) {
	if (A.s0[i].s0[j].s0[k]) {
	  printf("A[%d,%d,%d] is: %f \n",i,j,k,*(A.s0[i].s0[j].s0[k]));
	}
      }
    }
  }
  return 0;
}


int print_jA4D(strip4D A) {
  printf("----------- \n");
  for (int i=A.min; i<=A.max; i++) {
    for (int j=A.s0[i].min; j<=A.s0[i].max; j++) {
      for (int k=A.s0[i].s0[j].min; k<=A.s0[i].s0[j].max; k++) {
	for (int l=A.s0[i].s0[j].s0[k].min; l<=A.s0[i].s0[j].s0[k].max; l++) {
	  if (A.s0[i].s0[j].s0[k].s0[l]) {
	    printf("A[%d,%d,%d,%d] is: %f \n",i,j,k,l,*(A.s0[i].s0[j].s0[k].s0[l]));
	  }
	}
      }
    }
  }
  return 0;
}


int print_jA5D(strip5D A) {
  printf("----------- \n");
  for (int i=A.min; i<=A.max; i++) {
    for (int j=A.s0[i].min; j<=A.s0[i].max; j++) {
      for (int k=A.s0[i].s0[j].min; k<=A.s0[i].s0[j].max; k++) {
	for (int l=A.s0[i].s0[j].s0[k].min; l<=A.s0[i].s0[j].s0[k].max; l++) {
	  for (int m=A.s0[i].s0[j].s0[k].s0[l].min; m<=A.s0[i].s0[j].s0[k].s0[l].max; m++) {
	    if (A.s0[i].s0[j].s0[k].s0[l].s0[m]) {
	      printf("A[%d,%d,%d,%d,%d] is: %f \n",i,j,k,l,m,*(A.s0[i].s0[j].s0[k].s0[l].s0[m]));
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
  for (int i=A.min; i<=A.max; i++) {
    for (int j=A.s0[i].min; j<=A.s0[i].max; j++) {
      for (int k=A.s0[i].s0[j].min; k<=A.s0[i].s0[j].max; k++) {
	for (int l=A.s0[i].s0[j].s0[k].min; l<=A.s0[i].s0[j].s0[k].max; l++) {
	  for (int m=A.s0[i].s0[j].s0[k].s0[l].min; m<=A.s0[i].s0[j].s0[k].s0[l].max; m++) {
	    for (int n=A.s0[i].s0[j].s0[k].s0[l].s0[m].min; n<=A.s0[i].s0[j].s0[k].s0[l].s0[m].max; n++) {
	      if (A.s0[i].s0[j].s0[k].s0[l].s0[m].s0[n]) {
		printf("A[%d,%d,%d,%d,%d,%d] is: %f \n",i,j,k,l,m,n,*(A.s0[i].s0[j].s0[k].s0[l].s0[m].s0[n]));
	      }
	    }
	  }
	}
      }
    }
  }
  return 0;
}




/************************************************************** 
*
* Freeing memory functions for 1D-6D memoization jagged arrays 
*
**************************************************************/

int mem_free_1D(strip1D *A) {
  for (int i=A->min; i <= A->max; i++) if (A->s0[i]) free(A->s0[i]);
  if (A->s) {
    free(A->s);
    A->s = NULL;
    A->s0 = NULL;
  }
  return 0;
}

int mem_free_2D(strip2D *A) {
  for (int i=A->min; i <= A->max; i++) mem_free_1D(&(A->s0[i]));
  if (A->s) {
    free(A->s);
    A->s = NULL;
    A->s0 = NULL;
  }
  return 0;
}

int mem_free_3D(strip3D *A) {
  for (int i=A->min; i <= A->max; i++) mem_free_2D(&(A->s0[i]));
  if (A->s) {
    free(A->s);
    A->s = NULL;
    A->s0 = NULL;
  }
  return 0;
}

int mem_free_4D(strip4D *A) {
  for (int i=A->min; i <= A->max; i++) mem_free_3D(&(A->s0[i]));
  if (A->s) {
    free(A->s);
    A->s = NULL;
    A->s0 = NULL;
  }
  return 0;
}

int mem_free_5D(strip5D *A) {
  for (int i=A->min; i <= A->max; i++) mem_free_4D(&(A->s0[i]));
  if (A->s) {
    free(A->s);
    A->s = NULL;
    A->s0 = NULL;
  }
  return 0;
}

int mem_free_6D(strip6D *A) {
  for (int i=A->min; i <= A->max; i++) mem_free_5D(&(A->s0[i]));
  if (A->s) {
    free(A->s);
    A->s = NULL;
    A->s0 = NULL;
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
**************************************************************/
double* elem1D(int l1,strip1D A) {
  if (l1 >= A.min && l1 <= A.max) return A.s0[l1];
  return NULL;
}

double* elem2D(int l1,int l2,strip2D A) {
  if (l1 >= A.min && l1 <= A.max && A.s0[l1].s0) return elem1D(l2,A.s0[l1]);
  return NULL;
}

double* elem3D(int l1,int l2,int l3,strip3D A) {
  if (l1 >= A.min && l1 <= A.max && A.s0[l1].s0) return elem2D(l2,l3,A.s0[l1]);
  return NULL;
}

double* elem4D(int l1,int l2,int l3,int l4,strip4D A) {
  if (l1 >= A.min && l1 <= A.max && A.s0[l1].s0) return elem3D(l2,l3,l4,A.s0[l1]);
  return NULL;
}

double* elem5D(int l1,int l2,int l3,int l4,int l5,strip5D A) {
  if (l1 >= A.min && l1 <= A.max && A.s0[l1].s0) return elem4D(l2,l3,l4,l5,A.s0[l1]);
  return NULL;
}

double* elem6D(int l1,int l2,int l3,int l4,int l5,int l6,strip6D A) {
  if (l1 >= A.min && l1 <= A.max && A.s0[l1].s0) return elem5D(l2,l3,l4,l5,l6,A.s0[l1]);
  return NULL;
}

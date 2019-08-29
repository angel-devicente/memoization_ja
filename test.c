#include <stdlib.h>
#include <stdio.h>

int insert(int l1, int l2, int *s1, int *s2, double val, double ****A) {
  if (*A) {
    /* first dimenstion exists */
    if (l1 < *s1) {
      /* first dimenstion big enough to store this value */
      if ((*A)[l1]) {
	/* second dimension exists */
	if (l2 < *s2) {
	  /* second dimension big enough to store this value */
	  if ((*A)[l1][l2]) {
	    /* link to element does exist, so already stored */
	    /* 	    printf("%f already stored. SKIPPPING \n",val); */
	  } else {
	    /* no link to element, adding new value */
	    /* printf("%f ADDING \n",val); */
	    (*A)[l1][l2] = (double *)malloc(sizeof(double));
	    *(*A)[l1][l2] = val;
	  }
	} else {
	  /* second dimension not big enough. need to realloc, from here we have to create everything */
	  int p_s2 = *s2;
	  *s2 = l2+1;
	  double **tmp = realloc((*A)[l1],sizeof(double*)*(*s2));
	  if(tmp) {
	    (*A)[l1]=tmp;
	  } else { // realloc failed
	    printf("Could not reallocate \n");
	    return 1;
	  }
          for (int j=p_s2; j<=l2; j++) {
	    if (j == l2) {
	      (*A)[l1][j] = (double *)malloc(sizeof(double));
	      *(*A)[l1][j] = val;
	    } else {
	      (*A)[l1][j] = NULL; 
	    }			 
	  }
	}
      } else {
	/* second dimension does not exist, from here we have to create everything */
	(*A)[l1] = (double **)malloc(sizeof(double*)*(*s2));
	for (int j=0; j<=l2; j++) {
	  if (j == l2) {
	    (*A)[l1][j] = (double *)malloc(sizeof(double));
	    *(*A)[l1][j] = val;
	  } else {
	    (*A)[l1][j] = NULL; 
	  }
	}
      }
    } else {
      /* first dimension not big enough, need to realloc, from here we have to create everything */
      int p_s1 = *s1;
      *s1 = l1+1;
      double ***tmp = realloc((*A),sizeof(double**)*(*s1));
      if(tmp) {
	(*A)=tmp;
      } else { // realloc failed
	printf("Could not reallocate \n");
	return 1;
      }

      for(int i=p_s1; i<=l1; i++){
	if (i == l1) {
	  *s2 = l2+1;
	  (*A)[i] = (double **)malloc(sizeof(double*)*(*s2));
	  for (int j=0; j<=l2; j++) {
	    if (j == l2) {
	      (*A)[l1][l2] = (double *)malloc(sizeof(double));
	      *(*A)[i][j] = val; 
	    } else {
	      (*A)[i][j] = NULL; 
	    }
	  }
	} else {
	  (*A)[i] = NULL;
	}
      }
    }
  } else {
    /* first dimension does not exist yet */
    *s1 = l1+1;
    *A = (double***)malloc(sizeof(double**)*(*s1));
    for(int i=0; i<=l1; i++){
      if (i == l1) {
	*s2 = l2+1;
	(*A)[i] = (double **)malloc(sizeof(double*)*(*s2));
	for (int j=0; j<=l2; j++) {
	  if (j == l2) {
	    (*A)[i][j] = (double *)malloc(sizeof(double));
	    *(*A)[i][j] = val;
	  } else {
	    (*A)[i][j] = NULL; 
	  }
	}
      } else {
	(*A)[i] = NULL;
      }
    }
  }
  
  return 0;
}


int print_jA(int s1, int s2, double ***A) {
  //  printf("A is at: %p \n",(void*)A); 
  for (int i=0; i<s1; i++) {
    //    printf("A[%d] is at: %p \n",i,(void*)A[i]); 
    if (A[i]) {
      for (int j=0; j<s2; j++) {
	//	printf("A[%d,%d] is at: %p \n",i,j,(void*)A[i][j]); 
  	if (A[i][j]) {
	  printf("A[%d,%d] is: %f \n",i,j,*(A[i][j]));
	}
      }
    }
  }
}
  

int main(int argc, char const *argv[]) {

  int l1,l2,l3,l4,l5,l6;
  int s1=0,s2=0,s3=0,s4=0,s5=0,s6=0;
  double val;
  double ***A = NULL;

  printf("\n2,3\n");
  insert(2,3,&s1,&s2,0.12345,&A);
  print_jA(s1,s2,A);

  printf("\n2,3\n");
  insert(2,3,&s1,&s2,0.12345,&A);
  print_jA(s1,s2,A);

  printf("\n2,2\n");
  insert(2,2,&s1,&s2,2.12345,&A);
  print_jA(s1,s2,A);

  printf("\n2,4 \n");
  insert(2,4,&s1,&s2,21.2345,&A);
  print_jA(s1,s2,A);

  printf("\n3,4 \n");
  insert(3,4,&s1,&s2,31.2345,&A);
  print_jA(s1,s2,A);
  
  return 0;
}




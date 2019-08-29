#include <stdlib.h>
#include <stdio.h>


typedef struct strip1D {
  int size;
  double** s;
} strip1D;

typedef struct strip2D {
  int size;
  strip1D* s;
} strip2D;

typedef struct strip3D {
  int size;
  strip2D* s;
} strip3D;

typedef struct strip4D {
  int size;
  strip3D* s;
} strip4D;

typedef struct strip5D {
  int size;
  strip4D* s;
} strip5D;

typedef struct strip6D {
  int size;
  strip5D* s;
} strip6D;


int place_val1D(int st, int l1, double val, strip1D *A) {
  for(int i=st; i<=l1; i++){
    if (i == l1) {
      A->s[i] = (double *)malloc(sizeof(double));
      *(A->s[i]) = val; 
    } else {
      A->s[i] = NULL;
    }
  }
  return 0;
}

int insert1D(int l1, double val, strip1D *A) {
  if (A->size > 0) {
    if (l1 < A->size) {
      if (A->s[l1]) {   // already stored, noop 
      } else {          // no link to value, adding  
	A->s[l1] = (double *)malloc(sizeof(double));
	*(A->s[l1]) = val;
      }
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      double **tmp = realloc(A->s,sizeof(double*)*(s1));
      if(tmp) {
	A->s=tmp;
      } else {   
	return 1;
      }
      place_val1D(p_s1,l1,val,A);
      
    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    A->s = (double**)malloc(sizeof(double*)*(s1));
    place_val1D(0,l1,val,A);
  }

  return 0;
}


int insert2D(int l1, int l2, double val, strip2D *A) {
  if (A->size > 0) {
    if (l1 < A->size) {
      insert1D(l2,val,&(A->s[l1]));
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      strip1D* tmp = realloc(A->s,sizeof(strip1D)*(s1));
      if(tmp) {
	A->s=tmp;
      } else {
	return 1;
      }

      for(int i=p_s1; i<=l1; i++){
	(A->s[i]).size = 0;
      }
      insert1D(l2,val,&(A->s[l1]));

    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    A->s = (strip1D*)malloc(sizeof(strip1D)*(s1));
    for(int i=0; i<=l1; i++){
      A->s[i].size = 0;
    }
    insert1D(l2,val,&(A->s[l1]));
  }

  return 0;
}


int insert3D(int l1, int l2, int l3, double val, strip3D *A) {
  if (A->size > 0) {
    if (l1 < A->size) {
      insert2D(l2,l3,val,&(A->s[l1]));
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      strip2D* tmp = realloc(A->s,sizeof(strip2D)*(s1));
      if(tmp) {
	A->s=tmp;
      } else {
	return 1;
      }

      for(int i=p_s1; i<=l1; i++){
	(A->s[i]).size = 0;
      }
      insert2D(l2,l3,val,&(A->s[l1]));

    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    A->s = (strip2D*)malloc(sizeof(strip2D)*(s1));
    for(int i=0; i<=l1; i++){
      A->s[i].size = 0;
    }
    insert2D(l2,l3,val,&(A->s[l1]));
  }

  return 0;
}


int insert4D(int l1, int l2, int l3, int l4, double val, strip4D *A) {
  if (A->size > 0) {
    if (l1 < A->size) {
      insert3D(l2,l3,l4,val,&(A->s[l1]));
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      strip3D* tmp = realloc(A->s,sizeof(strip3D)*(s1));
      if(tmp) {
	A->s=tmp;
      } else {
	return 1;
      }

      for(int i=p_s1; i<=l1; i++){
	(A->s[i]).size = 0;
      }
      insert3D(l2,l3,l4,val,&(A->s[l1]));

    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    A->s = (strip3D*)malloc(sizeof(strip3D)*(s1));
    for(int i=0; i<=l1; i++){
      A->s[i].size = 0;
    }
    insert3D(l2,l3,l4,val,&(A->s[l1]));
  }

  return 0;
}


int insert5D(int l1, int l2, int l3, int l4, int l5, double val, strip5D *A) {
  if (A->size > 0) {
    if (l1 < A->size) {
      insert4D(l2,l3,l4,l5,val,&(A->s[l1]));
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      strip4D* tmp = realloc(A->s,sizeof(strip4D)*(s1));
      if(tmp) {
	A->s=tmp;
      } else {
	return 1;
      }

      for(int i=p_s1; i<=l1; i++){
	(A->s[i]).size = 0;
      }
      insert4D(l2,l3,l4,l5,val,&(A->s[l1]));

    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    A->s = (strip4D*)malloc(sizeof(strip4D)*(s1));
    for(int i=0; i<=l1; i++){
      A->s[i].size = 0;
    }
    insert4D(l2,l3,l4,l5,val,&(A->s[l1]));
  }

  return 0;
}


int insert6D(int l1, int l2, int l3, int l4, int l5, int l6, double val, strip6D *A) {
  if (A->size > 0) {
    if (l1 < A->size) {
      insert5D(l2,l3,l4,l5,l6,val,&(A->s[l1]));
    } else {           // not big enough: realloc and place value
      int p_s1 = A->size;
      int s1 = l1+1;
      A->size = s1;
      strip5D* tmp = realloc(A->s,sizeof(strip5D)*(s1));
      if(tmp) {
	A->s=tmp;
      } else {
	return 1;
      }

      for(int i=p_s1; i<=l1; i++){
	(A->s[i]).size = 0;
      }
      insert5D(l2,l3,l4,l5,l6,val,&(A->s[l1]));

    }
  } else {            // dimension does not exist yet: create and place value
    int s1 = l1+1;
    A->size = s1;
    A->s = (strip5D*)malloc(sizeof(strip5D)*(s1));
    for(int i=0; i<=l1; i++){
      A->s[i].size = 0;
    }
    insert5D(l2,l3,l4,l5,l6,val,&(A->s[l1]));
  }

  return 0;
}


int present6D(int l1,int l2,int l3,int l4,int l5,int l6,strip6D A) {
  if (A.size > l1 &&
      A.s[l1].size > l2 &&
      A.s[l1].s[l2].size > l3 &&
      A.s[l1].s[l2].s[l3].size > l4 &&
      A.s[l1].s[l2].s[l3].s[l4].size > l5 &&
      A.s[l1].s[l2].s[l3].s[l4].s[l5].size > l6 &&
      A.s[l1].s[l2].s[l3].s[l4].s[l5].s[l6]) {
    return 1;
      } else {
    return 0;
      }
}

double elem6D(int l1,int l2,int l3,int l4,int l5,int l6,strip6D A) {
  return *(A.s[l1].s[l2].s[l3].s[l4].s[l5].s[l6]);
}


int print_jA1D(strip1D A) {
  printf("----------- \n"); 
  for (int i=0; i<A.size; i++) {
    if (A.s[i]) {
      printf("A[%d] is: %f \n",i,*(A.s[i]));
    }
  }
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
}


int main(int argc, char const *argv[]) {

  printf("\n\nTesting 1D \n");
  printf("========== \n");
  strip1D A1D; A1D.size = 0;

  insert1D(2,2.0,&A1D);
  print_jA1D(A1D);

  insert1D(1,1.0,&A1D);
  print_jA1D(A1D);

  insert1D(2,2.0,&A1D);
  print_jA1D(A1D);

  insert1D(5,5.0,&A1D);
  print_jA1D(A1D);

  insert1D(5,5.0,&A1D);
  print_jA1D(A1D);

  insert1D(7,7.0,&A1D);
  print_jA1D(A1D);
  
  
  printf("\n\nTesting 2D \n");
  printf("========== \n");
  strip2D A2D; A2D.size = 0;
  
  insert2D(2,3,2.3,&A2D);
  print_jA2D(A2D);

  insert2D(2,2,2.2,&A2D);
  print_jA2D(A2D);

  insert2D(2,4,2.4,&A2D);
  print_jA2D(A2D);

  insert2D(3,4,3.4,&A2D);
  print_jA2D(A2D);


  printf("\n\nTesting 3D \n");
  printf("========== \n");
  strip3D A3D; A3D.size = 0;
  
  insert3D(2,3,4,2.34,&A3D);
  print_jA3D(A3D);

  insert3D(2,3,5,2.35,&A3D);
  print_jA3D(A3D);
  
  insert3D(2,1,5,2.15,&A3D);
  print_jA3D(A3D);
  
  insert3D(1,1,5,1.15,&A3D);
  print_jA3D(A3D);
  
  insert3D(1,1,5,1.15,&A3D);
  print_jA3D(A3D);
  
  insert3D(3,1,5,3.15,&A3D);
  print_jA3D(A3D);


  printf("\n\nTesting 4D \n");
  printf("========== \n");
  strip4D A4D; A4D.size = 0;
  
  insert4D(2,3,4,8,2.34,&A4D);
  print_jA4D(A4D);

  insert4D(2,3,5,7,2.35,&A4D);
  print_jA4D(A4D);
  
  insert4D(6,2,1,5,2.15,&A4D);
  print_jA4D(A4D);
  
  insert4D(5,1,1,5,1.15,&A4D);
  print_jA4D(A4D);
  
  insert4D(1,9,5,5,1.15,&A4D);
  print_jA4D(A4D);
  
  insert4D(3,10,5,4,3.15,&A4D);
  print_jA4D(A4D);


  printf("\n\nTesting 5D \n");
  printf("========== \n");
  strip5D A5D; A5D.size = 0;
  
  insert5D(2,3,2,4,8,2.34,&A5D);
  print_jA5D(A5D);

  insert5D(2,3,5,8,7,2.35,&A5D);
  print_jA5D(A5D);
  
  insert5D(4,6,2,1,5,2.15,&A5D);
  print_jA5D(A5D);
  
  insert5D(9,5,1,1,5,1.15,&A5D);
  print_jA5D(A5D);
  
  insert5D(12,1,9,5,5,1.15,&A5D);
  print_jA5D(A5D);
  
  insert5D(1,3,10,5,4,3.15,&A5D);
  print_jA5D(A5D);


  printf("\n\nTesting 6D \n");
  printf("========== \n");
  strip6D A6D; A6D.size = 0;
  
  insert6D(1,2,3,2,4,8,2.34,&A6D);
  print_jA6D(A6D);

  insert6D(3,2,3,5,8,7,2.35,&A6D);
  print_jA6D(A6D);
  
  insert6D(4,6,8,2,1,5,2.15,&A6D);
  print_jA6D(A6D);
  
  insert6D(9,15,1,1,5,2,1.15,&A6D);
  print_jA6D(A6D);
  
  insert6D(12,13,9,5,5,20,1.15,&A6D);
  print_jA6D(A6D);
  
  insert6D(1,3,1,5,40,2,3.15,&A6D);
  print_jA6D(A6D);


  printf("\n Testing search functions in 6D \n");
  printf("Testing: 1,3,1,5,40,2\n");
  if (present6D(1,3,1,5,40,2,A6D)) printf("%f \n",elem6D(1,3,1,5,40,2,A6D));

  printf("Testing: 3,3,1,5,40,2\n");
  if (present6D(3,3,1,5,40,2,A6D)) printf("%f \n",elem6D(3,3,1,5,40,2,A6D));

  printf("Testing: 1,2,3,2,4,8\n");
  if (present6D(1,2,3,2,4,8,A6D)) printf("%f \n",elem6D(1,2,3,2,4,8,A6D));


  
  return 0;
}




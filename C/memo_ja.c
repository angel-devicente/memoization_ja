/* Copyright (C) 2019 by Angel de Vicente, angel@iac.es 
   https://github.com/angel-devicente/                     */

/******************************************************************
* Angel de Vicente 
*
* A simple test function for 6D memoizatioin_ja.c
* 
******************************************************************
* TO DO: 
*   + add proper tests 
******************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "memoization_ja.h"

int main(int argc, char *argv[]) {
  // poistion and value in array
  int l1,l2,l3,l4,l5,l6;
  double v;

  // jagged array, plus initialization.
  // val pointer to result of search in array
  strip6D A6D; A6D.size = 0; 
  double* val;

  // command line argument default values 
  int nvals=1000;
  int nsearch=1000;
  int maxc=40;
  int d=0;

  // timing
  clock_t t1,t2;
  double cpu_time = 0.0;
  
  // 
  int opt;

  /*---------------------------------------------------------------*/
  
  /* Read command line arguments */
  while ((opt = getopt(argc, argv, "hdn:w:s:")) != -1) {
    switch (opt) {
    case 'n': nvals = atoi(optarg); break;
    case 'w': maxc = atoi(optarg); break;
    case 's': nsearch = atoi(optarg); break;
    case 'd': d=1;break;
    case 'h':   
      fprintf(stderr, "Usage: %s [-h] [-n nvals] [-w maxc] [-s nsearch]\n", argv[0]);
      fprintf(stderr, "  -h         : displays this help\n");
      fprintf(stderr, "  -d         : debug mode (will print all insertions, info on searches and state of the array)\n");
      fprintf(stderr, "  -n nvals   : nvals (default=1000) is the number of values to add to the array\n");
      fprintf(stderr, "  -w maxc    : maxc (default=40) is the maximum length of each of the array dimensions\n");
      fprintf(stderr, "  -s nsearch : nsearch (default=1000) is the number of elements to search for in the array\n");
      exit(EXIT_FAILURE);
    }
  }
  for (int index = optind; index < argc; index++) {
    printf ("Invalid argument %s - EXITING\n", argv[index]);
    exit(EXIT_FAILURE);
  }

  printf("\nTesting 6D memoization with Jagged Arrays \n");
  printf("========================================== \n");

  printf("Inserting %d random values in random positions of the array (max dimension value: %d)\n\n",nvals,maxc);

  for (int rv=0 ; rv < nvals ; rv++) {
    l1 = rand() % (maxc+1);
    l2 = rand() % (maxc+1);
    l3 = rand() % (maxc+1);
    l4 = rand() % (maxc+1);
    l5 = rand() % (maxc+1);
    l6 = rand() % (maxc+1);
    v = drand48();
    
    if (d) printf("Inserting val: %f at positions: %d %d %d %d %d %d\n",v,l1,l2,l3,l4,l5,l6);     
    insert6D(l1,l2,l3,l4,l5,l6,v,&A6D);
    if (d) {
      printf("Jagged array:\n"); 
      print_jA6D(A6D);
      printf("\n\n"); 
    }
  }


  printf("Checking for %d random positions of the array (max dimension value: %d)\n\n",nsearch,maxc);
  
  for (int rv=0 ; rv < nsearch ; rv++) {
    l1 = rand() % (maxc+1);
    l2 = rand() % (maxc+1);
    l3 = rand() % (maxc+1);
    l4 = rand() % (maxc+1);
    l5 = rand() % (maxc+1);
    l6 = rand() % (maxc+1);
    v = drand48();
    
    if (d) printf("Checking position: %d %d %d %d %d %d \n",l1,l2,l3,l4,l5,l6);

    t1 = clock();
    val = elem6D(l1,l2,l3,l4,l5,l6,A6D);
    t2 = clock();
    cpu_time += (t2-t1);

    if (d && val) printf("%f \n",*val); 
  }

  printf("%d positions searched in a 6D array of size %d in %f seconds\n",nsearch,maxc,((double)cpu_time)/CLOCKS_PER_SEC);

  return 0;
}


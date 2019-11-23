#ifndef MEMOIZATION_JA_H
#define MEMOIZATION_JA_H

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

int place_val1D(int st, int l1, double val, strip1D *A);
int insert1D(int l1, double val, strip1D *A);
int insert2D(int l1, int l2, double val, strip2D *A);
int insert3D(int l1, int l2, int l3, double val, strip3D *A);
int insert4D(int l1, int l2, int l3, int l4, double val, strip4D *A);
int insert5D(int l1, int l2, int l3, int l4, int l5, double val, strip5D *A);
int insert6D(int l1, int l2, int l3, int l4, int l5, int l6, double val, strip6D *A);

int print_jA1D(strip1D A);
int print_jA2D(strip2D A);
int print_jA3D(strip3D A);
int print_jA4D(strip4D A);
int print_jA5D(strip5D A);
int print_jA6D(strip6D A);

int mem_free_1D(strip1D *A);
int mem_free_2D(strip2D *A);
int mem_free_3D(strip3D *A);
int mem_free_4D(strip4D *A);
int mem_free_5D(strip5D *A);
int mem_free_6D(strip6D *A);

double* elem6D(int l1,int l2,int l3,int l4,int l5,int l6,strip6D A);

#endif

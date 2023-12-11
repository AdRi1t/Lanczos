#ifndef VECTOR_H
#define VECTOR_H 

typedef struct
{
  double *array_real;
  double *array_imag;
  bool isAllocated;
  bool isComplex;
  unsigned int n;
}Vector;

Vector createVector(int n, bool isComplex);
bool allocateVector(Vector* v);
bool fillRandom(Vector* v);
void fillConst(Vector* v, double k);
void copyVector(Vector* dest, Vector* src);
void printVector(Vector* v);
void freeVector(Vector* v);
#endif
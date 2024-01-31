/**
 * @file vector.c
 * @brief Implementation of all vector management routines,
 *        from creation to memory release
 */
#include "lanczos.h"
#include "vector.h"

Vector createVector(int n, bool isComplex)
{
  assert(n > 0);
  Vector v;
  v.n = n;
  v.array_real = NULL;
  v.array_imag = NULL;
  v.isAllocated = false;
  v.isComplex = isComplex;
  return v;
}

bool allocateVector(Vector *v) 
{
  assert(v->n > 0);
  v->array_real = (double*)malloc(sizeof(double)* v->n);
  v->array_imag = (double*)malloc(sizeof(double)* v->n);
  v->isAllocated = true;
  return true;
}

bool fillRandom(Vector *v)
{ 
  srand(10);
  for (size_t i = 0; i < v->n; i++)
  {
    v->array_real[i] = (double) rand() / (double) RAND_MAX;
    v->array_imag[i] = 0;
  }
  return true;
}

void fillConst(Vector *v, const double k)
{
  for (size_t i = 0; i < v->n; i++)
  {
    v->array_real[i] = k;
    v->array_imag[i] = 0;
  }
  return;
}

void copyVector(Vector *dest, Vector *src)
{
  assert(dest->n == src->n);
  if(dest->isAllocated)
  {
    freeVector(dest);
  }
  *dest = createVector(src->n, false);
  allocateVector(dest);
  #pragma omp parallel for simd
  {
    for (size_t i = 0; i < dest->n; i++)
    {
      dest->array_real[i] = src->array_real[i];
    }
  }
}

void printVector(Vector *v)
{
  if(v->isComplex)
  {
    for (size_t i = 0; i < v->n; i++)
    {
      printf("(%6.3e,%6.3e) ",v->array_real[i], v->array_imag[i]);
    }
  }
  else
  {
    for (size_t i = 0; i < v->n; i++)
    {
      printf("%6.3e ",v->array_real[i]);
    }
  }
  printf("\n");
}

void freeVector(Vector *v)
{
  free(v->array_real);
  free(v->array_imag);
  v->n = 0;
  v->isAllocated = false;
  return;
}

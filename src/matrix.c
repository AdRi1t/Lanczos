#include "lanczos.h"
#include "matrix.h"

// "High level"

Matrix createMatrix(Matrix_type type, bool setComplex) 
{ 
  Matrix M;
  switch (type)
  {
    case General:
      M.type = General;
      break;
    case Symmetric:
      M.type = Symmetric;
      break;
    default:
      break;
  }
  M.isComplex = setComplex;
  M.array_size = 0;
  M.array_real = NULL;
  M.array_imag = NULL;
  M.isAllocated = false;
  M.n_cols = 0;
  M.n_rows = 0;
  return M;
}

bool setDimensionMatrix(Matrix *M, int n_rows, int n_cols)
{
  assert(n_rows > 0);
  assert(n_cols > 0);
  M->n_rows = n_rows;
  M->n_cols = n_cols;
  return true;
}

bool allocateMatrix(Matrix *M)
{
  switch (M->type)
  {
  case General:
    allocateGeneralMatrix(M);
    break;
  case Symmetric:
    allocateSymmetric(M);
    break;
  default:
    return false;
    break;
  }  
  return true;
}

void freeMatrix(Matrix *M)
{
  free(M->array_real);
  if(M->isComplex)
  {
    free(M->array_imag);
  }
  M->isAllocated = false;
  M->n_rows = 0;
  M->n_cols = 0;
}

void canBeComplex(Matrix *M, bool isComplex)
{
  M->isComplex = isComplex;
}

void fillRandomMatrix(Matrix *M)
{
  srand(10);
  for (size_t i = 0; i < M->array_size; i++)
  {
    M->array_real[i] = (double) rand() / (double) RAND_MAX;
  }
  if (M->isComplex)
  {
    for (size_t i = 0; i < M->array_size; i++)
    {
      M->array_imag[i] = 0;
    }
  }
  return;
}

void fillConstMatrix(Matrix *M, double k)
{
  for (size_t i = 0; i < M->array_size; i++)
  {
    M->array_real[i] = k;
  }
  return;
}
  
void printMatrix(Matrix *M) {
  switch (M->type)
  {
  case General:
    printGeneral(M);
    break;
  case Symmetric:
    printSymmetric(M);
    break;
  default: 
    break;
  }  
  return;
}

// "Low Level"

bool allocateGeneralMatrix(Matrix *M) {
  M->array_size = M->n_cols * M->n_rows;
  M->array_real = (double*)calloc(M->array_size, sizeof(double));
  if(M->isComplex)
  {
    M->array_imag = (double*)calloc(M->array_size, sizeof(double));
  }
  M->isAllocated = true;
  return true;
}

bool allocateSymmetric(Matrix *M)
{
  assert(M->n_cols == M->n_rows);
  M->array_size = ((M->n_rows) * (M->n_cols + 1))/2;
  M->array_real = (double*)calloc(M->array_size, sizeof(double));
  if(M->isComplex)
  {
    M->array_imag = (double*)calloc(M->array_size, sizeof(double));
  }
  M->isAllocated = true;
  return true;
}

void printSymmetric(const Matrix *M)
{
  unsigned int shift = 0;
  for (size_t i = 0; i < M->n_rows; i++)
  {
    if(i != 0)
    {
      printf("%*c", i*11, ' ');
    }
    for (size_t j = 0; j < M->n_cols - i; j++)
    {
      printf("% 6.3e ",M->array_real[shift + j]); 
    }
    shift += M->n_cols - i;
    printf("\n");
  }
}

void printGeneral(const Matrix *M)
{
  for (size_t i = 0; i < M->n_rows; i++)
  {
    for (size_t j = 0; j < M->n_cols; j++)
    {
      printf("% 6.3e ",M->array_real[i*M->n_cols + j]);
    }
    printf("\n"); 
  }
}



void fillA1TestMatrix(Matrix *M)
{
  assert(M->type == Symmetric);
  assert(M->n_rows == M->n_cols);
  assert(M->n_rows == 8);
  const double a = 11111111;
  const double b = 9090909;
  const double c = 10891089;
  const double d = 8910891;
  const double e = 11108889;
  const double f = 9089091;
  const double g = 10888911;
  const double h = 8909109;
  unsigned int shift = 0;
  for (int i = 0; i < 8; i++)
  {
    M->array_real[shift] = a;
    if(i == 0)
    {
      M->array_real[shift + 1] = -b;
      M->array_real[shift + 2] = -c;
      M->array_real[shift + 3] = d;
      M->array_real[shift + 4] = -e;
      M->array_real[shift + 5] = f;
      M->array_real[shift + 6] = g;
      M->array_real[shift + 7] = -h;
    }
    else if(i == 1)
    {
      M->array_real[shift + 1] = d;
      M->array_real[shift + 2] = -c;
      M->array_real[shift + 3] = f;
      M->array_real[shift + 4] = -e;
      M->array_real[shift + 5] = -h;
      M->array_real[shift + 6] = g;

    }else if(i == 2)
    {
      M->array_real[shift + 1] = -b;
      M->array_real[shift + 2] = g;
      M->array_real[shift + 3] = -h;
      M->array_real[shift + 4] = -e;
      M->array_real[shift + 5] = f;
    }
    else if(i == 3)
    {
      M->array_real[shift + 1] = -h;
      M->array_real[shift + 2] = g;
      M->array_real[shift + 3] = f;
      M->array_real[shift + 4] = -e;
    }
    else if(i == 4)
    {
      M->array_real[shift + 1] = -b;
      M->array_real[shift + 2] = c;
      M->array_real[shift + 3] = d;
    }
    else if(i == 5)
    {
      M->array_real[shift + 1] = d;
      M->array_real[shift + 2] = -c;
    }
    else if(i == 6)
    {
      M->array_real[shift + 1] = -b;
    }
    shift += M->n_cols  - i;
  }
}


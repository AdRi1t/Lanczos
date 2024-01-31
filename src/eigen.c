#include <lapacke.h>
#include <cblas.h>
#include "lanczos.h"
#include "eigen.h"

double c_norm(double x ,double y)
{
  return sqrt(x*x + y*y);
}

EigenProblem computeEigen(Matrix* A)
{
  assert(A->isAllocated);
  assert(A->isComplex == false);
  assert(A->n_cols == A->n_rows);

  EigenProblem result;
  result.eigen_value = createVector(A->n_rows, true);
  result.eigen_vector = createMatrix(General, true);
  setDimensionMatrix(&result.eigen_vector, A->n_rows, A->n_rows);
  allocateVector(&result.eigen_value);
  allocateMatrix(&result.eigen_vector);

  double* a;
  a = (double*)malloc(A->n_cols * A->n_rows * sizeof(double));
  if(A->type == Symmetric)
  {
    unsigned int shift = 0;
    for (size_t i = 0; i < A->n_rows; i++)
    {
      for (size_t j = i ; j < A->n_cols; j++)
      {
        a[i * A->n_cols + j] = A->array_real[shift + j];
        a[j * A->n_rows + i] = A->array_real[shift + j];
      }
      shift += A->n_cols - i - 1;
    }
  }
  else
  {
    for (size_t i = 0; i < A->n_rows; i++)
    {
      for (size_t j = 0; j < A->n_cols; j++)
      {
        a[i*A->n_cols + j] = A->array_real[i*A->n_cols + j];
      }
    }
  }
  // On exit, A has been overwritten.
  LAPACKE_dgeev(LAPACK_ROW_MAJOR,
                'N',
                'V',
                A->n_rows,
                a,
                A->n_rows,
                result.eigen_value.array_real,
                result.eigen_value.array_imag,
                NULL,
                1,
                result.eigen_vector.array_real,
                A->n_rows);
  free(a);
  return result;
}

EigenProblem order_and_select(EigenProblem P, unsigned int m)
{
  assert(m < P.eigen_vector.n_cols);
  unsigned int n = P.eigen_value.n;
  int* index = (int*)malloc(n * sizeof(int));
  
  for (size_t i = 0; i < n; i++)
  {
    index[i] = i;
  }
  for (size_t i = 0; i < n; i++)
  { 
    for (size_t j = i  ; j < n; j++)
    {
      // i < j si v(i) < v(j)
      if (fabs(P.eigen_value.array_real[i]) < fabs(P.eigen_value.array_real[j]))
      {
        double a,b;
        a = P.eigen_value.array_real[i];
        b = P.eigen_value.array_imag[i];
        P.eigen_value.array_real[i] = P.eigen_value.array_real[j];
        P.eigen_value.array_imag[i] = P.eigen_value.array_imag[j];
        P.eigen_value.array_real[j] = a;
        P.eigen_value.array_imag[j] = b;
        int tmp_pos = i;
        index[i] = j;
        index[j] = tmp_pos;
      }
    }
  }
  EigenProblem result;
  result.eigen_value = createVector(m, true);
  result.eigen_vector = createMatrix(General,true);
  allocateVector(&result.eigen_value);
  setDimensionMatrix(&result.eigen_vector, P.eigen_vector.n_rows, m);
  allocateMatrix(&result.eigen_vector);

  // copy eigen values
  for (size_t i = 0; i < m; i++)
  {
    result.eigen_value.array_real[i] = P.eigen_value.array_real[i];
    result.eigen_value.array_imag[i] = P.eigen_value.array_imag[i];
  }
  // copy eigen vectors
  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 0; j < m; j++)
    {
      result.eigen_vector.array_real[i*m+j] =  P.eigen_vector.array_real[index[i]*n + j];
      result.eigen_vector.array_imag[i*m+j] =  P.eigen_vector.array_imag[index[i]*n + j];
    }
  }
  return result;
}

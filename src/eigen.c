#include <lapacke.h>
#include <cblas.h>
#include "lanczos.h"
#include "eigen.h"

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
   for (size_t i = 0; i < A->n_rows; i++)
  {
    for (size_t j = 0; j < A->n_cols; j++)
    {
      printf("%6.3e ",a[i*A->n_cols + j]);
    }
    printf("\n");
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
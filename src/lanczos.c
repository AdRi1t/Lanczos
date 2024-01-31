/**
 * @file lanczos.c
 * @brief Lanczos algorithm file
 */
#include "lanczos.h"


Vector completeReorthogonalization(double *currentVector,Matrix *V, int currentIndex) {
    double *w = (double*)calloc(V->n_rows, sizeof(double));
    double *w_j = (double*)calloc(V->n_rows, sizeof(double));
    Vector vect;

    #pragma omp parallel for
    for (size_t i = 0; i < V->n_rows; i++)
    {
        w[i] = currentVector[i];
    }

    for (int j = 0; j < currentIndex; j++) {
        #pragma omp parallel for
        for (size_t i = 0; i < V->n_rows; i++)
        {
            w_j[i] = V->array_real[i*V->n_cols + j];
        }

        double r_jk = DotProduct(w,w_j,V->n_rows);
        #pragma omp parallel for
        for (size_t i = 0; i < V->n_rows; i++)
        {
            w[i] -= r_jk*w_j[i];
        }

    }

    double r_kk = NormVector(w,V->n_rows);

    #pragma omp parallel for
    for (size_t i = 0; i < V->n_rows; i++)
    {
        w[i] /= r_kk;
    }

    vect = createVector(V->n_rows,false);
    allocateVector(&vect);
    #pragma omp parallel for
    for (size_t i = 0; i < vect.n; i++)
    {
        vect.array_real[i]=w[i];
        vect.array_imag[i] = 0;
    }

    return vect;
}

LanzcosOut computeLanzcosAlgo(LanzcosIn init)
{
  LanzcosOut result;
  result.H = createMatrix(General, false);
  result.V = createMatrix(General, false);
  setDimensionMatrix(&result.H, init.m, init.m);
  setDimensionMatrix(&result.V, init.A.n_rows, init.m);
  allocateMatrix(&result.H);
  allocateMatrix(&result.V);
  double B_j = init.B_0;
  double a_j = 0.0;
  Vector v_j = createVector(init.A.n_rows, false);
  Vector v_j_1 = createVector(init.A.n_rows, false);
  copyVector(&v_j, &init.v_0);
  copyVector(&v_j_1, &init.v_0);
  OP_Real_scaleVector(&v_j, 1/OP_Real_Norm(&v_j));
  for (int j = 0; j < init.m; j++)
  {
    // 3 w_j = A*v_j + B_j*v_j-1
    Vector tmp_1 = OP_MatrixVector(&init.A, &v_j);
    OP_Real_scaleVector(&v_j_1, -B_j);
    Vector tmp_2 = OP_Real_AddVector(&tmp_1, &v_j_1);
    
    // 4 a_j = (w_j,v_j)
    a_j = OP_Real_DotProduct(&tmp_2, &v_j);
    
    // 5 w_j = w_j - a_j*v_j
    OP_Real_scaleVector(&v_j, - a_j);
    Vector w_j = OP_Real_AddVector(&tmp_2, &v_j);
    
    // 6 b_j = ||w_j||
    B_j = OP_Real_Norm(&w_j);

    result.H.array_real[j*result.H.n_cols + j] = a_j;
    if(j > 0)
    {
      result.H.array_real[(j-1)*result.H.n_cols + j] = B_j;
      result.H.array_real[j*result.H.n_cols + j - 1] = B_j;
    }
    
    // 7 v_j+1 = w_j/b_j+1
    copyVector(&v_j,&w_j);
    OP_Real_scaleVector(&v_j, 1/B_j);

    double *currentVector = (double*)calloc(v_j.n, sizeof(double));
    for(size_t i=0;i<v_j.n;i++){
        currentVector[i] = v_j.array_real[i];
    }
    v_j = completeReorthogonalization(currentVector,&result.V,j);
    copyVector(&v_j_1, &v_j);
    
    freeVector(&w_j);
    freeVector(&tmp_1);
    freeVector(&tmp_2);
  
    #pragma omp parallel
    {
      for (size_t i = 0; i < result.V.n_rows; i++)
      {
        result.V.array_real[i*result.V.n_cols + j] = v_j.array_real[i]; 
      }
    }
  }
  freeVector(&v_j);
  freeVector(&v_j_1);
  return result;
}

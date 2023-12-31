#include "lanczos.h"


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
      result.H.array_real[j*result.H.n_cols + j - 1] = B_j;
    }
    if(j < init.m - 1)
    {
      result.H.array_real[j*result.H.n_cols + j + 1] = B_j;
    }
    
    // 7 v_j+1 = w_j/b_j+1
    copyVector(&v_j,&w_j);
    OP_Real_scaleVector(&v_j, 1/B_j);
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
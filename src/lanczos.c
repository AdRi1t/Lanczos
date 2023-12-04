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
  Vector v_j = OP_Real_scaleVector(&init.v_0, 1/OP_Real_Norm(&init.v_0));
  Vector v_j_1 = init.v_0;
  for (int j = 0; j < init.m; j++)
  {
    Vector w_j = OP_MatrixVector(&init.A, &v_j);
    Vector tmp = OP_Real_scaleVector(&v_j_1, -B_j);
    w_j = OP_Real_AddVector(&w_j, &tmp);

    a_j = OP_Real_DotProduct(&w_j, &v_j);
    tmp = OP_Real_scaleVector(&v_j, - a_j);
    w_j = OP_Real_AddVector( &w_j, &tmp);

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
    v_j_1 = v_j;
    v_j = OP_Real_scaleVector(&w_j,1/B_j);
    #pragma omp parallel
    {
      for (size_t i = 0; i < result.V.n_rows; i++)
      {
        result.V.array_real[i*result.V.n_cols + j] = v_j.array_real[i]; 
      }
    }
  }
  return result;
}
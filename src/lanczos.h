#ifndef LANZCOS_H
#define LANZCOS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#include "config.h"
#include "matrix.h"
#include "vector.h"
#include "operations.h"
#include "eigen.h"

// Structure for Lanczos algorithm input data
typedef struct
{
  int m;
  double B_0;
  Vector v_0;
  Matrix A;
}LanzcosIn;

typedef struct
{
  Matrix H;
  Matrix V;
}LanzcosOut;

Vector completeReorthogonalization(double *currentVector,Matrix *V, int currentIndex);
LanzcosOut computeLanzcosAlgo(LanzcosIn init);

#endif
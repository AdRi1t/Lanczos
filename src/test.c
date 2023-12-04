#include "lanczos.h"

int main(int argc, char const *argv[])
{ 
  runConfig config;
  Matrix A;
  Vector v,r;
  config = parseCommand(argc,argv);

  // Vector test 
  v = createVector(config.n, false);
  allocateVector(&v);

  printf("Rand vector Test : \n");
  fillRandom(&v);
  printVector(&v);
  printf("\n");

  printf("Const vector Test : \n");
  fillConst(&v, 2);
  printVector(&v);
  printf("\n");

  printf("v := v + v : \n");
  v = OP_Real_AddVector(&v,&v);
  printVector(&v);
  printf("\n");

  printf("k = ||v||_2 : \n");
  double k = OP_Real_Norm(&v);
  printf("%f \n", k);
  printf("\n");

  // General Test 
  printf("General matrix Test : \n");
  A = createMatrix(General,false);
  setDimensionMatrix(&A, config.n, config.n);
  allocateMatrix(&A);
  fillRandomMatrix(&A);
  printMatrix(&A);
  printf("\n");

  printf("y = A*v : \n");
  r = OP_Real_General_matrixVector(&A,&v);
  printVector(&r);
  printf("\n");
  freeMatrix(&A);

  // Symmetric test 
  printf("Symmetric matrix Test : \n");
  A = createMatrix(Symmetric, false);
  setDimensionMatrix(&A,config.n,config.n);
  allocateMatrix(&A);
  fillRandomMatrix(&A);
  printMatrix(&A);
  printf("\n");

  printf("y = A*v : \n");
  r = OP_Real_Symmetric_matrixVector(&A,&v);
  printVector(&r);
  printf("\n");
  freeMatrix(&A);

  printf("Test A1 : \n");
  A = createMatrix(Symmetric, false);
  setDimensionMatrix(&A, 8, 8);
  allocateMatrix(&A);
  fillA1TestMatrix(&A);
  printMatrix(&A);
  printf("\n");

  freeVector(&v);
  return 0;  
}


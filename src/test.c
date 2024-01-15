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

  printf("y = v : \n");
  Vector copy = createVector(v.n, false);
  copyVector(&copy,&v);
  printVector(&copy);
  freeVector(&copy);
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

  printf("V2 : y = A*v : \n");
  r = OP_Real_Symmetric_matrixVector_V2(&A,&v);
  printVector(&r);
  printf("\n");

  printf("V3 : y = A*v : \n");
  r = OP_Real_Symmetric_matrixVector_V3(&A,&v);
  printVector(&r);
  printf("\n");

  freeMatrix(&A);

  printf("Test A1 : \n");
  A = createMatrix(Symmetric, false);
  setDimensionMatrix(&A, 8, 8);
  allocateMatrix(&A);
  fillA1TestMatrix(&A);
  printMatrix(&A);
  freeMatrix(&A);
  printf("\n");

  // Read from file
  printf("Read from file : \n");
  A = loadFromFile("mtx/mtx_TEST.mtx");
  printMatrix(&A);
  freeMatrix(&A);
  
  printf("Eigen Test from file : \n");
  A = loadFromFile("mtx/mtx_TEST.mtx");
  EigenProblem res;
  res = computeEigen(&A);
  printVector(&res.eigen_value);
  printMatrix(&res.eigen_vector);
  freeVector(&res.eigen_value);
  freeMatrix(&res.eigen_vector);
  freeMatrix(&A);

  // Test version of Matrix vector product
  printf("V1, V2, V3 : \n");
  A = createMatrix(Symmetric,false);
  setDimensionMatrix(&A, 10000, 10000);
  allocateMatrix(&A);
  fillRandomMatrix(&A);
  v = createVector(10000, false);
  allocateVector(&v);

  double t1,t2,time;
  t1 = getTime();
  for (size_t j = 0; j < 31; j++)
  {
    r = OP_Real_Symmetric_matrixVector(&A,&v);
    freeVector(&r);
  }
  t2 = getTime();
  time = (t2 - t1) / 31;
  printf("v1 time : %6.3f s\n",time);
  t1 = getTime();
  for (size_t j = 0; j < 31; j++)
  {
    r = OP_Real_Symmetric_matrixVector_V2(&A,&v);
    freeVector(&r);
  }
  t2 = getTime();
  time = (t2 - t1) / 31;
  printf("v2 time : %6.3f s\n",time);

  t1 = getTime();
  for (size_t j = 0; j < 31; j++)
  {
    r = OP_Real_Symmetric_matrixVector_V3(&A,&v);
    freeVector(&r);
  }
  t2 = getTime();
  time = (t2 - t1) / 31;
  printf("V3 time : %6.3f s\n",time);
 
  freeVector(&v);
  freeMatrix(&A);


  return 0;  
}


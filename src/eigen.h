#ifndef EIGEN_H
#define EIGEN_H


typedef struct 
{
  Vector eigen_value;
  Matrix eigen_vector;
}EigenProblem;

EigenProblem computeEigen(Matrix* A);
EigenProblem order_and_select(EigenProblem P, unsigned int m);

#endif
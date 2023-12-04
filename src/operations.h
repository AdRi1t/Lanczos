#ifndef OPERATIONS_H
#define OPERATIONS_H


Vector OP_MatrixVector(Matrix* M, Vector* v);

// "Low Level"
Vector OP_Real_Symmetric_matrixVector(Matrix* M, Vector* v);
Vector OP_Complex_General_matrixVector(Matrix* M, Vector* v);
Vector OP_Real_General_matrixVector(Matrix* M, Vector* v);

Vector OP_Real_scaleVector(Vector* v, double real);
Vector OP_Real_AddVector(Vector* x, Vector *y);
double OP_Real_DotProduct(Vector* x, Vector *y);
double OP_Real_Norm(Vector* v);


#endif
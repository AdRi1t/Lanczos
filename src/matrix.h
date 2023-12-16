#ifndef MATRIX_H
#define MATRIX_H

typedef enum
{
  General,
  Symmetric,
}Matrix_type; 

typedef struct 
{
  double* array_real;
  double* array_imag;
  Matrix_type type;
  size_t array_size;
  unsigned int n_rows;
  unsigned int n_cols;
  bool isComplex;
  bool isAllocated;
}Matrix;

// "High level"
Matrix createMatrix(Matrix_type type, bool setComplex);
Matrix loadFromFile(char* filePath);
bool setDimensionMatrix(Matrix *M, int n_rows, int n_cols);
bool allocateMatrix(Matrix* M);
void canBeComplex(Matrix* M , bool isComplex);
void fillRandomMatrix(Matrix* M);
void fillConstMatrix(Matrix* M, double k);
void fillA1TestMatrix(Matrix* M);
void printMatrix(Matrix* M);
void freeMatrix(Matrix* M);

// "Low Level"
bool allocateGeneralMatrix(Matrix* M);
bool allocateSymmetric(Matrix* M);
void printSymmetric(const Matrix *M);
void printGeneral(const Matrix *M);

#endif
#include "lanczos.h"

int main(int argc, char const *argv[])
{ 
  runConfig config;
  LanzcosIn in;
  LanzcosOut out;
  config = parseCommand(argc,argv);
  
  in.B_0 = config.b_0;
  in.m = config.m;
  in.A = createMatrix(Symmetric, false);
  in.v_0 = createVector(config.n, false);
  setDimensionMatrix(&in.A, config.n, config.n);
  allocateMatrix(&in.A);
  allocateVector(&in.v_0);
  fillConst(&in.v_0, 1.0);
  fillRandomMatrix(&in.A);
  
  FILE* result_file = NULL;
  char *file_name = (char*)malloc(sizeof(char)*256);
  sprintf(file_name,"lanczosResult_%d_%d.txt", config.n, config.m);
  result_file = fopen(file_name ,"w");
  fprintf(result_file, "%10s %10s %10s\n", "Threads", "Time", "Gflops");
  
  int thread_exp[9] = {1,2,4,8,12,16,24,32,40};
  const int nb_exp = 9;
  int threads = 1;
  double time;
  double Gflops;
  for (size_t i = 0; i < nb_exp; i++)
  {
    omp_set_num_threads(thread_exp[i]);
    double t1 = getTime();
    for (size_t j = 0; j < 10; j++)
    {
      out = computeLanzcosAlgo(in);
    }
    double t2 = getTime();
    time = (t2 - t1) / 10;
    Gflops = (in.m*(2*pow(config.n,2)+9*config.n) / time ) * 1e-9;
    threads = omp_get_max_threads();
    fprintf(result_file, "%10d %10.4f %10.4f\n", threads, time, Gflops);
  }
  
  fclose(result_file);
  
  /*
  printMatrix(&out.H);
  printf("\n");
  printMatrix(&out.V);
  */
  freeMatrix(&in.A);
  freeMatrix(&out.H);
  freeMatrix(&out.V);
  
  return 0;
}

#include "lanczos.h"

int bench_1(runConfig config);
int bench_2(runConfig config);

int main(int argc, char const *argv[])
{ 
  runConfig config;
  LanzcosIn in;
  config = parseCommand(argc,argv);
  in.A = createMatrix(Symmetric, false);
  if (config.haveFile)
  {
    in.A = loadFromFile(config.filePath);
    config.n = in.A.n_rows;
  }
  else
  {
    setDimensionMatrix(&in.A, config.n, config.n);
    allocateMatrix(&in.A);
    fillRandomMatrix(&in.A);
  }

  if(config.B == 1)
  {
    bench_1(config);
  }
  else if (config.B == 2)
  {
    bench_2(config);
  }
  else
  {
    LanzcosOut out;
    in.B_0 = config.b_0;
    in.m = config.m;
    in.v_0 = createVector(config.n, false);
    allocateVector(&in.v_0);
    fillConst(&in.v_0, 1.0);   

    out = computeLanzcosAlgo(in);
    
    printMatrix(&out.H);
    printf("\n");
    printMatrix(&out.V);
    
    freeMatrix(&out.H);
    freeMatrix(&out.V);
    freeVector(&in.v_0);
    freeMatrix(&in.A);
  }
  
  return 0;
}

// printf("test : %d\n",__LINE__);

int bench_1(runConfig config)
{
  LanzcosIn in;
  LanzcosOut out;
  in.A = createMatrix(Symmetric, false);
  if (config.haveFile)
  {
    in.A = loadFromFile(config.filePath);
    config.n = in.A.n_rows;
  }
  else
  {
    setDimensionMatrix(&in.A, config.n, config.n);
    allocateMatrix(&in.A);
    fillRandomMatrix(&in.A);
  }
  in.B_0 = config.b_0;
  in.m = config.m;
  in.v_0 = createVector(config.n, false);
  allocateVector(&in.v_0);
  fillConst(&in.v_0, 1.0);  
  
  FILE* result_file = NULL;
  char *file_name = (char*)malloc(sizeof(char)*256);
  sprintf(file_name,"lanczosOmpResult_%d_%d.txt", config.n, config.m);
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
      freeMatrix(&out.H);
      freeMatrix(&out.V);
    }
    double t2 = getTime();
    time = (t2 - t1) / 10;
    Gflops = (in.m*(2*pow(config.n,2)+9*config.n) / time ) * 1e-9;
    threads = omp_get_max_threads();
    fprintf(result_file, "%10d %10.4f %10.4f\n", threads, time, Gflops);
  }
  fclose(result_file);
  freeVector(&in.v_0);
  freeMatrix(&in.A);
  return 0;
}

int bench_2(runConfig config)
{
  LanzcosIn in;
  LanzcosOut out;
  in.A = createMatrix(Symmetric, false);
  if (config.haveFile)
  {
    in.A = loadFromFile(config.filePath);
    config.n = in.A.n_rows;
  }
  else
  {
    setDimensionMatrix(&in.A, config.n, config.n);
    allocateMatrix(&in.A);
    fillRandomMatrix(&in.A);
  }
  in.B_0 = config.b_0;
  in.m = config.m;
  in.v_0 = createVector(config.n, false);
  allocateVector(&in.v_0);
  fillConst(&in.v_0, 1.0);  
  
  FILE* result_file = NULL;
  char *file_name = (char*)malloc(sizeof(char)*256);
  sprintf(file_name,"lanczosMresult_%d.txt", config.n);
  result_file = fopen(file_name ,"w");
  fprintf(result_file, "%10s %10s %10s\n", "m", "Time", "Gflops");
  const int nb_rep = 9;
  omp_set_num_threads(1);
  double time;
  double Gflops;
  
  for (size_t i = 1; i <= 10; i++)
  {
    in.m = 5*i;
    double t1 = getTime();
    for (size_t j = 0; j < nb_rep; j++)
    {
      out = computeLanzcosAlgo(in);
      freeMatrix(&out.H);
      freeMatrix(&out.V);
    }
    double t2 = getTime();
    time = (t2 - t1) / nb_rep;
    Gflops = (in.m*(2*pow(config.n,2)+9*config.n) / time ) * 1e-9;
    fprintf(result_file, "%10d %10.4f %10.4f\n", in.m, time, Gflops);
  }
  fclose(result_file);
  return 0;
}

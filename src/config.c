#include "lanczos.h"

runConfig parseCommand(int argc, char* argv[])
{
  extern char* optarg;
  int opt;
  runConfig config;
  config.n = 0;
  config.m = 0;
  config.b_0 = 1.0;
  if(argc == 1)
  {
    printUsage(argv[0]);
    exit(EXIT_SUCCESS);
  }
  while((opt = getopt(argc, argv, "hn:m:b:")) != -1)
  {
    switch(opt)
    {
      case 'h':
        printUsage(argv[0]);
        exit(EXIT_SUCCESS);
        break;
      case 'n':
        config.n = atoi(optarg);
        break;
      case 'm':
        config.m = atoi(optarg);
        break;
      case 'b':
        config.b_0 = atof(optarg);
        break;
    }
  }
  return config;
}

void printUsage(const char* progName)
{
  printf("Usage: \n");
  printf("%s -n [dimension] -m [nombre de valeurs propres] -b [valeur de B_0] \n",progName);
}

double getTime(void)
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec*1e0 + ts.tv_nsec*1e-9;
}


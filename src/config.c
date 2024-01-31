/**
 * @file config.c
 * @brief Manages arguments and runtime configuration
 */
#include "lanczos.h"

runConfig parseCommand(int argc, char* argv[])
{
  extern char* optarg;
  int opt;
  runConfig config;
  config.n = 1;
  config.m = 1;
  config.B = 0;
  config.b_0 = 1.0;
  config.filePath = (char*)calloc(256,sizeof(char));
  config.haveFile = false;
  if(argc == 1)
  {
    printUsage(argv[0]);
    exit(EXIT_SUCCESS);
  }
  while((opt = getopt(argc, argv, "hn:m:b:f:B:")) != -1)
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
      case 'B':
        config.B = atoi(optarg);
        break;
      case 'f':
        strcpy(config.filePath, optarg);
        config.haveFile = true;
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
  printf("%s -n [dimension] -m [nombre de valeurs propres] -b [valeur de B_0] -f [file path to .mtx] -B [Benchmark see docs]\n",progName);
}

double getTime(void)
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec*1e0 + ts.tv_nsec*1e-9;
}


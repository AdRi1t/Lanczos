#ifndef CONFIG_H
#define CONFIG_H

typedef struct
{
  int n;
  int m;
  double b_0;
}runConfig;

runConfig parseCommand(int argc, char* argv[]);
void printUsage(const char* progName);
double getTime(void);
#endif
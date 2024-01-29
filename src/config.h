#ifndef CONFIG_H
#define CONFIG_H

typedef struct
{
  int n;
  int m;
  int B;
  double b_0;
  char* filePath;
  bool haveFile;
}runConfig;

runConfig parseCommand(int argc, char* argv[]);
void printUsage(const char* progName);
double getTime(void);
#endif
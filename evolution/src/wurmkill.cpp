#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
  int pid; 
  pid = atoi(argv[1]);
  
  if (pid > 100) kill (pid, 9);  
  return 0;
}


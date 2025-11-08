#include "types.h"
#include "user.h"
#include "pstat.h"

int
main(int argc, char **argv)
{
  struct pstat buf[64];
  int n = pstat(buf, 64);
  if(n < 0){
    printf(2, "pstat failed\n");
    exit();
  }
  printf(1, "PID\tSTATE\tSIZE\tNAME\n");
  for(int i=0;i<n;i++){
    printf(1, "%d\t%d\t%d\t%s\n", buf[i].pid, buf[i].state, buf[i].sz, buf[i].name);
  }
  exit();
}

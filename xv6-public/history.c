#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  int fd = open("/.xv6_history", 0);
  if(fd < 0){
    printf(2, "no history\n");
    exit();
  }
  char buf[512];
  int n;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    // write to stdout
    write(1, buf, n);
  }
  close(fd);
  exit();
}

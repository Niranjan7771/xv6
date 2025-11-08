#include "types.h"
#include "user.h"

int
main(int argc, char **argv)
{
  int uid = getuid();
  // xv6 doesn't have user database; treat uid 0 as root
  if(uid == 0)
    printf(1, "root\n");
  else
    printf(1, "user%d\n", uid);
  exit();
}

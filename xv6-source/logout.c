#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(getuid() == 0){
    printf(2, "No user logged in\n");
    exit();
  }
  
  logout();
  printf(1, "Logged out successfully\n");
  exit();
}

#include "types.h"
#include "stat.h"
#include "user.h"
#include "user_auth.h"

int
main(int argc, char *argv[])
{
  int perms;
  
  if(argc != 3){
    printf(2, "Usage: chmod <file> <permissions>\n");
    printf(2, "Permissions: 1=read, 2=write, 3=read+write\n");
    exit();
  }
  
  perms = atoi(argv[2]);
  
  // Convert simple permission number to flags
  int perm_flags = 0;
  if(perms & 1) perm_flags |= PERM_READ;
  if(perms & 2) perm_flags |= PERM_WRITE;
  
  if(chmod(argv[1], perm_flags) < 0){
    printf(2, "chmod failed (admin only)\n");
    exit();
  }
  
  printf(1, "Permissions changed successfully\n");
  exit();
}

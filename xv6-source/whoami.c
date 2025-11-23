#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int uid = getuid();
  
  if(uid == 0){
    printf(1, "No user logged in\n");
  } else if(uid == 1){
    printf(1, "admin (uid: %d)\n", uid);
  } else if(uid == 2){
    printf(1, "user1 (uid: %d)\n", uid);
  } else if(uid == 3){
    printf(1, "user2 (uid: %d)\n", uid);
  } else {
    printf(1, "Unknown user (uid: %d)\n", uid);
  }
  
  exit();
}

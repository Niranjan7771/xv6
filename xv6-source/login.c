#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  char username[16];
  char password[16];
  int uid;
  
  if(argc == 3){
    // Command line login
    uid = login(argv[1], argv[2]);
  } else {
    // Interactive login
    printf(1, "XV6 Login\n");
    printf(1, "Username: ");
    gets(username, sizeof(username));
    username[strlen(username)-1] = 0;  // Remove newline
    
    printf(1, "Password: ");
    gets(password, sizeof(password));
    password[strlen(password)-1] = 0;  // Remove newline
    
    uid = login(username, password);
  }
  
  if(uid < 0){
    printf(2, "Login failed!\n");
    exit();
  }
  
  printf(1, "Login successful! UID: %d\n", uid);
  exit();
}

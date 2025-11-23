// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *sh_argv[] = { "sh", 0 };
char *login_argv[] = { "login", 0 };

int
main(void)
{
  int pid, wpid;
  char username[16];
  char password[16];
  int uid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
    // Login prompt
    printf(1, "\n=== XV6 User Authentication System ===\n");
    printf(1, "Default users:\n");
    printf(1, "  admin/admin (full access)\n");
    printf(1, "  user1/pass1 (read only)\n");
    printf(1, "  user2/pass2 (read+write)\n");
    printf(1, "=====================================\n");
    printf(1, "Username: ");
    gets(username, sizeof(username));
    username[strlen(username)-1] = 0;  // Remove newline
    
    printf(1, "Password: ");
    gets(password, sizeof(password));
    password[strlen(password)-1] = 0;  // Remove newline
    
    uid = login(username, password);
    
    if(uid < 0){
      printf(2, "Login failed! Try again.\n");
      sleep(100);
      continue;
    }
    
    printf(1, "Login successful! Welcome %s (UID: %d)\n", username, uid);
    printf(1, "Starting shell...\n");
    
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", sh_argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
    
    // After shell exits, logout
    logout();
    printf(1, "Shell exited. Please login again.\n");
  }
}

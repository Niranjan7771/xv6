// User authentication header
#ifndef USER_AUTH_H
#define USER_AUTH_H

#define MAX_USERNAME 16
#define MAX_PASSWORD 16
#define MAX_USERS 10

// Permission flags
#define PERM_READ  0x01
#define PERM_WRITE 0x02
#define PERM_EXEC  0x04
#define PERM_ADMIN 0x08

struct user {
  char username[MAX_USERNAME];
  char password[MAX_PASSWORD];
  int uid;
  int permissions;
  int active;
};

#endif

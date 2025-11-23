#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "user_auth.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// User database (simple in-memory storage)
static struct user users[MAX_USERS];
static int users_initialized = 0;

// Initialize default users
void
init_users(void)
{
  if(users_initialized)
    return;
  
  // User 1: admin (full permissions)
  safestrcpy(users[0].username, "admin", MAX_USERNAME);
  safestrcpy(users[0].password, "admin", MAX_PASSWORD);
  users[0].uid = 1;
  users[0].permissions = PERM_READ | PERM_WRITE | PERM_EXEC | PERM_ADMIN;
  users[0].active = 1;
  
  // User 2: user1 (read only)
  safestrcpy(users[1].username, "user1", MAX_USERNAME);
  safestrcpy(users[1].password, "pass1", MAX_PASSWORD);
  users[1].uid = 2;
  users[1].permissions = PERM_READ | PERM_EXEC;
  users[1].active = 1;
  
  // User 3: user2 (read and write)
  safestrcpy(users[2].username, "user2", MAX_USERNAME);
  safestrcpy(users[2].password, "pass2", MAX_PASSWORD);
  users[2].uid = 3;
  users[2].permissions = PERM_READ | PERM_WRITE | PERM_EXEC;
  users[2].active = 1;
  
  users_initialized = 1;
}

// Login system call
int
sys_login(void)
{
  char *username, *password;
  int i;
  struct proc *curproc = myproc();
  
  if(argstr(0, &username) < 0 || argstr(1, &password) < 0)
    return -1;
  
  init_users();
  
  // Check credentials
  for(i = 0; i < MAX_USERS; i++){
    if(users[i].active && 
       strcmp(users[i].username, username) == 0 &&
       strcmp(users[i].password, password) == 0){
      curproc->uid = users[i].uid;
      curproc->permissions = users[i].permissions;
      return users[i].uid;
    }
  }
  
  return -1; // Login failed
}

// Logout system call
int
sys_logout(void)
{
  struct proc *curproc = myproc();
  curproc->uid = 0;
  curproc->permissions = 0;
  return 0;
}

// Get current user ID
int
sys_getuid(void)
{
  return myproc()->uid;
}

// Change file permissions (admin only)
int
sys_chmod(void)
{
  char *path;
  int perms;
  struct inode *ip;
  struct proc *curproc = myproc();
  
  if(argstr(0, &path) < 0 || argint(1, &perms) < 0)
    return -1;
  
  // Check if user has admin permissions
  if(!(curproc->permissions & PERM_ADMIN))
    return -1;
  
  begin_op();
  if((ip = namei(path)) == 0){
    end_op();
    return -1;
  }
  
  ilock(ip);
  ip->permissions = perms;
  iupdate(ip);
  iunlock(ip);
  iput(ip);
  end_op();
  
  return 0;
}

// Reboot system call
int
sys_reboot(void)
{
  // Simple reboot by triple fault
  outb(0x64, 0xFE);
  return 0;
}

int
sys_clearconsole(void)
{
  consoleclear();
  return 0;
}

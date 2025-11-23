#include "types.h"
#include "stat.h"
#include "user.h"

#define CPU_CHILDREN      4
#define SLEEP_CHILDREN    3
#define MIX_CHILDREN      2
#define INTER_CHILDREN    2
#define CPU_SPIN          1600000
#define CPU_ROUNDS        80
#define SLEEP_ROUNDS      60
#define MIX_ROUNDS        80
#define INTERACTIVE_ROUNDS 100

static void
spin_delay(void)
{
  volatile int i;
  for(i = 0; i < CPU_SPIN; i++)
    ;
}

static void
cpu_worker(int id)
{
  int iter;
  for(iter = 0; iter < CPU_ROUNDS; iter++){
    spin_delay();
    if(iter % 8 == 0)
      printf(1, "[mlfq cpu %d pid=%d] iter=%d uptime=%d\n", id, getpid(), iter, uptime());
  }
  printf(1, "[mlfq cpu %d pid=%d] finished\n", id, getpid());
  exit();
}

static void
sleep_worker(int id)
{
  int iter;
  for(iter = 0; iter < SLEEP_ROUNDS; iter++){
    printf(1, "[mlfq sleep %d pid=%d] tick=%d\n", id, getpid(), uptime());
    sleep(5);
  }
  printf(1, "[mlfq sleep %d pid=%d] finished\n", id, getpid());
  exit();
}

static void
mixed_worker(int id)
{
  int iter;
  for(iter = 0; iter < MIX_ROUNDS; iter++){
    if(iter % 2 == 0)
      spin_delay();
    else
      sleep(2);
    if(iter % 4 == 0)
      printf(1, "[mlfq mix %d pid=%d] iter=%d tick=%d\n", id, getpid(), iter, uptime());
  }
  printf(1, "[mlfq mix %d pid=%d] finished\n", id, getpid());
  exit();
}

static void
interactive_worker(int id)
{
  int iter;
  for(iter = 0; iter < INTERACTIVE_ROUNDS; iter++){
    printf(1, "[mlfq interactive %d pid=%d] iter=%d\n", id, getpid(), iter);
    sleep(1);
  }
  printf(1, "[mlfq interactive %d pid=%d] finished\n", id, getpid());
  exit();
}

static void
spawn_cpu_workers(void)
{
  int i;
  for(i = 0; i < CPU_CHILDREN; i++){
    int pid = fork();
    if(pid < 0){
      printf(2, "mlfqtest: failed to fork cpu worker\n");
      exit();
    }
    if(pid == 0)
      cpu_worker(i);
  }
}

static void
spawn_sleep_workers(void)
{
  int i;
  for(i = 0; i < SLEEP_CHILDREN; i++){
    int pid = fork();
    if(pid < 0){
      printf(2, "mlfqtest: failed to fork sleep worker\n");
      exit();
    }
    if(pid == 0)
      sleep_worker(i);
  }
}

static void
spawn_mixed_workers(void)
{
  int i;
  for(i = 0; i < MIX_CHILDREN; i++){
    int pid = fork();
    if(pid < 0){
      printf(2, "mlfqtest: failed to fork mix worker\n");
      exit();
    }
    if(pid == 0)
      mixed_worker(i);
  }
}

static void
spawn_interactive_workers(void)
{
  int i;
  for(i = 0; i < INTER_CHILDREN; i++){
    int pid = fork();
    if(pid < 0){
      printf(2, "mlfqtest: failed to fork interactive worker\n");
      exit();
    }
    if(pid == 0)
      interactive_worker(i);
  }
}

int
main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

    printf(1, "mlfqtest: starting %d cpu, %d sleep, %d mixed, %d interactive workers\n",
      CPU_CHILDREN, SLEEP_CHILDREN, MIX_CHILDREN, INTER_CHILDREN);
  printf(1, "Observe the interleaving to confirm the scheduler remains responsive.\n");

  spawn_cpu_workers();
  spawn_sleep_workers();
  spawn_mixed_workers();
    spawn_interactive_workers();

    int total = CPU_CHILDREN + SLEEP_CHILDREN + MIX_CHILDREN + INTER_CHILDREN;
  while(total-- > 0)
    wait();

  printf(1, "mlfqtest: all workers finished\n");
  exit();
}

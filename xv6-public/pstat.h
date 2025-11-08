// Small pstat structure shared between kernel and userland.
#ifndef PSTAT_H
#define PSTAT_H

#define PSTAT_NAME_LEN 16

struct pstat {
  int pid;
  int state; // enum procstate
  int sz;
  char name[PSTAT_NAME_LEN];
};

#endif

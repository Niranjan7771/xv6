#include "../types.h"
#include "../user.h"

int
main(int argc, char **argv)
{
  const char seq[] = "\x1b[H\x1b[2J";
  write(1, seq, sizeof(seq) - 1);
  exit();
}

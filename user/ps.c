#include "kernel/types.h"
#include "kernel/pstat.h"
#include "kernel/param.h"
#include "user/user.h"

struct pstat p;

int
main(int argc, char *argv[])
{
  int status;

  status = getpinfo(&p);
  if (status < 0) {
    return -1;
  }

  printf("PID\tTICKETS\tTICKS\n");
  for (int i = 0; i < NPROC; i++) {
    if (!p.inuse[i])
      continue;

    printf("%d\t%d\t%d\n", p.pid[i], p.tickets[i], p.ticks[i]);
  }

  return 0;
}

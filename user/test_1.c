#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
fib(int n)
{
  if (n <= 1) {
    return n;
  }
  return fib(n - 1) + fib(n - 2);
}

int
main(int argc, char *argv[])
{
  int pid[2];

  settickets(10);

  pid[0] = fork();
  if (pid[0] == 0) {
    settickets(20);
    printf("I am the child process 1, my PID is %d\n", getpid());
    printf("Child 1 computing fib(34) = %d\n", fib(40));
  } else {
    pid[1] = fork();
    if (pid[1] == 0) {
      settickets(30);
      printf("I am the child process 2, my PID is %d\n", getpid());
      printf("Child 2 computing fib(34) = %d\n", fib(40));
    }
  }

  if (pid[0] > 0 && pid[1] > 0) {
    printf("I am the parent process, my PID is %d\n", getpid());
    printf("Parent computing fib(34) = %d\n", fib(40));
  }
  exit(0);
}

#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int
main(int argc, char *argv[])
{
  int p2c[2];
  int c2p[2];
  if(pipe(p2c)<0){
    printf("create pipe failed\n");
    exit(-1);
  }
  if(pipe(c2p)<0){
    printf("create pipe failed\n");
    exit(-1);
  }
  
  int pid = fork();
  if(pid == 0){
    char buf;
    read(p2c[0], &buf, 1);
    printf("%d: received ping\n", getpid());
    write(c2p[1], "b", 1);
  } else {
    write(p2c[1], "a", 1);
    char buf;
    read(c2p[0], &buf, 1);
    printf("%d: received pong\n", getpid());
    wait(0);
  }

  exit(0);
}
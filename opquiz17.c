#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>


int main(){

  pid_t pid_c, pid_m = getpid();
  printf("hello %d\n",getpid());
  fork();
  fork();
  printf("\nHi I am %d and my parent is %d",getpid(), getppid() );
  if(getpid() == pid_m){
    pid_c = wait(NULL);
    printf("\nPID of terminated child %d",pid_c);
    exit(0);
  }
  return 0;
}

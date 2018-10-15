#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main(){

  pid_t pid = fork();

  if(pid > 0){
    printf("\nMy pid now %d", getpid());
    exit(0);
  }
  else if(pid==0){
    sleep(5);
    printf("in child process");
    printf("\nMy parent process now %d", getppid());
  }

  return 0;
}

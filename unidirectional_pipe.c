#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

#define REND 0
#define WEND 1
#define BS 56

int main(){

  int fd[2];
  pid_t pid;
  char buffersize[BS];
  char wm[BS],rm[BS];
  printf("\nEnter message to be written: ");
  gets(wm);
  pipe(fd);
    pid = fork();

  if(pid>0){

    close(fd[REND]);

    write(fd[WEND],wm,strlen(wm));
    close(fd[WEND]);

  }
  else if(pid==0){
    printf("\nIn Child Block:");
//    close(fd[WEND]);
    read(fd[REND],rm,BS);
    printf("\nMessage: %s ",rm );
    close(fd[REND]);

  }

  return 0;
}

/*
(4)  Simulate the cp command to copy source file to a destination file  using pipes.
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<ctype.h>
#include<fcntl.h>
#include<stdlib.h>

#define REND 0
#define WEND 1
#define BS 56

int main(){

  int fd[2];
  pipe(fd);
  char wm[BS],rm[BS];
  pid_t pid = fork();

  if(pid>0){

    close(fd[REND]);
    FILE *fp = fopen("file_forcp.txt","r");
    fread(wm, BS, 1, fp);
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

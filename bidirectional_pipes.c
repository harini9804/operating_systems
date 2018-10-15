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

  int fd1[2],fd2[2];
  pid_t pid;
  char buffersize[BS];
  char wm1[BS],wm2[BS],rm1[BS],rm2[BS];


  pipe(fd1);
  pipe(fd2);
  pid = fork();

  if(pid>0){

    close(fd1[REND]);
    close(fd2[WEND]);

    printf("\nEnter message 1 to be written: ");
    gets(wm1);

    write(fd1[WEND],wm1,strlen(wm1));
    read(fd2[REND],rm2,BS);
    printf("\nMessage 2: %s ",rm2 );

  }
  else if(pid==0){

    printf("\nIn Child Block:");
    close(fd1[WEND]);
    close(fd2[REND]);
    read(fd1[REND],rm1,BS);
    printf("\nMessage 1: %s ",rm1 );
    printf("\nEnter message 2 to be written: ");
    gets(wm2);
    write(fd2[WEND],wm2,strlen(wm2));

  }

  return 0;
}

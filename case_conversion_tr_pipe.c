#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<ctype.h>


#define REND 0
#define WEND 1
#define BS 56

int main(){

  pid_t pid;


  int nb;
  int fd[2];
  char buffer[BS];

  pipe(fd);
  pid = fork();
  if(pid==0){

    dup2(fd[1],1);
    char *argv[]={"ls",NULL};
    execvp(argv[0],argv);

  }
  else if(pid>0){

    close(fd[WEND]);
    dup2(fd[REND],0);
    execlp("tr","tr","a-z","A-Z",NULL);

  }



  return 0;
}

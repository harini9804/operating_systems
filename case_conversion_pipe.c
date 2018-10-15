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
    while( nb=read(fd[0],buffer,1) >0 ){

      for(int i=0;i<nb;i++){
        buffer[i] = toupper(buffer[i]);
        write(1,buffer,nb);
      }

    }

  }

  return 0;
}

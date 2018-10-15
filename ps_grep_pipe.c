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

  pid_t pid;


  int nb;
  int fd[2];

  char **cmd, **history, *str;
  char *token;
  cmd=(char**)malloc(sizeof(char*)*100);
  history =(char**)malloc(sizeof(char*)*100);

  int no_of_options=0;
  printf("\nEnter grep command: ");
  str = (char*)malloc(sizeof(char)*256);
  gets(str);

  token = strtok(str, " ");
  cmd[no_of_options]=(char*)malloc(sizeof(char)*100);
  cmd[no_of_options] = token;
  no_of_options++;
 // Keep printing tokens while one of the
 // delimiters present in str[].
 while (token != NULL) {
     token = strtok(NULL, " ");
     cmd[no_of_options]=(char*)malloc(sizeof(char)*100);
     cmd[no_of_options] = token;
     no_of_options++;
 }

  char * arg=NULL;
  cmd[no_of_options]=arg;

  pipe(fd);
  pid = fork();
  if(pid==0){

    dup2(fd[1],1);
    char *argv[]={"ps",NULL};
    execvp(argv[0],argv);

  }
  else if(pid>0){

    close(fd[WEND]);
    dup2(fd[REND],0);
    execvp("grep",cmd);

  }



  return 0;
}

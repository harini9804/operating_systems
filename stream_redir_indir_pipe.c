/*
(c) simulate stream redirection and indirection using dup system call.
[try both to/from a pipe and to/from a user created file]
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

//  pipe(fd);
  pid_t pid;
  char wm[BS];
  char *argv[]={"ls",NULL};
  int fd = open("file_redir.txt", O_WRONLY | O_CREAT);
  pid = fork();

  dup2(fd,1);
  execvp(argv[0],argv);


  return 0;
}

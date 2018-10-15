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
  char *argv[]={"ls",NULL};
  int fd = open("file_redir.txt", O_WRONLY | O_CREAT);

  dup2(fd,1);
  execl("/home/lenovo/Documents/lab_files/operating_systems/bin_for_redir","./bin_for_redir",NULL);


  return 0;
}

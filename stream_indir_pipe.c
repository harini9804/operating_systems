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

  char buffer[BS];
  int nb;
  int fd = open("file_redir.txt", O_RDONLY | O_EXCL);

  int fd2 = dup2(fd,0);
  while( nb=read(fd2,buffer,1) >0 ){
    write(1,buffer,nb);

  }
  return 0;
}

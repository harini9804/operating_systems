#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(){

  printf("hello %d\n",getpid());
  fork();
  fork();
  fork();
  printf("world %d",getpid());
  printf("there");
  return 0;
}

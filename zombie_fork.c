#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(){

  pid_t pid = fork();
  if(pid>0){
    sleep(5);
    printf("\nI just woke up.");
  }
  else{
    printf("\nI'm done" );
    exit(0);
  }

  return 0;
}

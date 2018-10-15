#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){

  pid_t pid = fork();
  int status;
  if(pid<0){
    fprintf(stderr, "%s\n", "Could not fork.\n");
  }
  else if(pid==0){
    execl("/","./same",NULL);
  }
  else{
    pid = wait(NULL);
      printf("\nExit status of child process: %d\n",status);
    printf("\nDone\n");
  }

  return 0;
}

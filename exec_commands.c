#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){

  printf("\n-----------------\n");
  printf("\nExecution of 'exec' variants.\n");

  pid_t pid = fork();
  int status=100;
  if(pid<0){
    fprintf(stderr, "%s\n", "Could not fork.\n");
  }
  else if(pid == 0){
    printf("\nIn Child Process C1.\n");
    pid_t pid1 = fork();
    if(pid1==0){
        printf("\nIn Child Process C3.\n");
      execl("/bin/ls","ls","-lt",NULL);
    }
    else if(pid1>0){
      printf("\nIn Child Process C1P.\n");
      execlp("ps","ps",NULL);
    }

  }
  else{
    pid = wait(&status);
    printf("\nExit status of child process: %d\n",status);
    pid_t pid2 = fork();
    if(pid2==0){
      printf("\nIn Main Process.\n");
       char *cmd[] ={"ls", "-l", NULL};
       execvp(cmd[0],cmd);
    }
    else if(pid2>0){
      printf("\nIn Child Process C2.\n");
      execlp("ls","ls","*.c",NULL);
    }
  //  execlp("ls","ls",NULL);

  }

  printf("\nEnd of main.\n");
  return 0;
}

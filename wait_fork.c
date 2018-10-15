#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>


int main(){

  pid_t pid_c, pid_m = getpid();
  printf("hello %d\n",getpid());
  fork();
  fork();
  printf("\nHi I am %d and my parent is %d",getpid(), getppid() );
  if(getpid() == pid_m){
    pid_c = wait(NULL);
    printf("\nPID of terminated child %d",pid_c);
    exit(0);
  }
  return 0;
}

// int main(){
//
//   printf("hello %d\n",getpid());
//   pid_t pid = fork();
//   pid_t pidc1,pidc2,pidc;
//   if(pid>0){
//     pidc1 = fork();
//     pidc2 = fork();
//     pidc = wait(NULL);
//     printf("\nPID of terminated child %d",pidc);
//   }
//   else{
//     printf("\nI'm child process %d and my parent is %d", getpid(), getppid());
//   }
//   return 0;
// }

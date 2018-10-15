#include<stdio.h>

  #include<signal.h>

  #include<stdlib.h>



  int main()

  {

      pid_t child;

      signal(SIGINT,SIG_IGN);

      child=fork();

      switch(child){

          case -1:

              perror("fork");

              exit(1);

          case 0:

              while(1){

                  printf("Child Process\n");

                  sleep(1);

              }

              break;

          default :

              while(1){

                  printf("Parent Process\n");

                  pause();

              }

              break;

      }

      return 0;

  }

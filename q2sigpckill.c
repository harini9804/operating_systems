#include<stdio.h>

   #include<signal.h>

   #include<stdlib.h>



   void response (int);

   void response (int sig_no)

   {

       printf("%s\n",sys_siglist[sig_no]);

       printf("This is singal handler\n");

   }

   int main()

   {

       pid_t child;

       int status;

       child = fork();

       switch (child){

           case -1 :

               perror("fork");

               exit (1);

           case 0 :

               kill(getppid(),SIGKILL);

               printf("I am an orphan process because my parent has been killed by me\n");

               printf("Handler failed\n");

               break;

           default :

               signal(SIGKILL,response);

               wait(&status);

               printf("The parent process is still alive\n");

               break;

       }       return 0;

   }

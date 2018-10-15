#include<stdio.h>

   #include<stdlib.h>

   #include<signal.h>



   void response (int);

   void response (int sig_no)

   {

       printf("%s",sys_siglist[sig_no]);

   }

   int main()

   {

       signal(SIGINT,response);

       while(1){

           printf("Sanfoundry\n");

           sleep(1);

       }

       return 0;

   }

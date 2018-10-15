#include<stdio.h>

  #include<signal.h>



  void response (int);

  void response (int sig_no)

  {

      printf("Linux\n");

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

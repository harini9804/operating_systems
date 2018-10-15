#include<stdio.h>

 #include<pthread.h>

 int main()

 {

     printf("Sanfoundry\n");

     pthread_exit("Bye");

     printf("Linux");

     return 0;

 }

#include<stdio.h>

   #include<pthread.h>

    void *fun_t(void *arg);

   void *fun_t(void *arg)

   {

       pthread_exit("Bye");

   }

   int main()

   {

       pthread_t pt;

       void *res_t;

       int ret;

       ret = pthread_join(pt,&res_t);

       printf("%d\n",ret);

       return 0;

   }

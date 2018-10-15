#include<stdio.h>
#include<pthread.h>

void *runner(void * param);
void *runner(void * param){

  int schedpolicy, scope;
  pthread_t tid = pthread_self();
  pthread_attr_t attr;
  printf("\nI am thread %d",tid);
  pthread_getattr_np(tid,&attr);
  if(pthread_attr_getscope(&attr,&scope)!=0)
   perror("CANNOT GET SCOPE.");
  else if(scope == PTHREAD_SCOPE_PROCESS)
    printf("%s\n","PROCESS CONTENTION SCOPE" );
  else if(scope == PTHREAD_SCOPE_SYSTEM)
    printf("%s\n","SYSTEM CONTENTION SCOPE" );
    else
    printf("%s\n", "Donno scope" );

    int stat = pthread_attr_setschedpolicy(&attr,SCHED_RR);
      if(stat!=0){
        printf("%s\n","CANNOT SET POLICY");
      }else{
        printf("%s" ,"policy set");
      }

  if(pthread_attr_getschedpolicy(&attr,&schedpolicy)!=0)
    printf("\n%s","CANNOT GET SCOPE.");
  else if(schedpolicy == SCHED_RR)
    printf("%s\n","ROUND ROBIN" );
  else if(schedpolicy == SCHED_FIFO)
    printf("%s\n", "SCHED FIFO" );
    else
    printf("\nDonno policy");

    pthread_attr_destroy(&attr);
     pthread_exit("Holla");
}

int main(){

  pthread_t tid;
  void * res_t;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
 //pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);

  pthread_create(&tid,&attr,runner,NULL);

  pthread_join(tid,&res_t);
  printf("%s",res_t);
  printf("%s\n","MAIN DONE" );
  pthread_exit(0);

  return 0;
}

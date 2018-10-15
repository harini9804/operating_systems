#include <pthread.h>
#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#define NUM 5

void *runner(void *param)
{
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
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	int i, scope;
	pthread_t tid[NUM];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	if (pthread_attr_getscope(&attr, &scope) != 0)
		fprintf(stderr, "Unable to get scheduling scope\n");
	else
	{
		if (scope == PTHREAD_SCOPE_PROCESS)
			printf("PTHREAD SCOPE PROCESS");
		else if (scope == PTHREAD_SCOPE_SYSTEM)
			printf("PTHREAD SCOPE SYSTEM");
		else
			fprintf(stderr, "Illegal scope value.\n");
    }

		pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
		pthread_setschedparam(tid,SCHED_RR,NULL);

	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);


	for (i = 0; i < NUM; i++)
		pthread_create(&tid[i],&attr,runner,NULL);
	for (i = 0; i < NUM; i++)
		pthread_join(tid[i], NULL);
}

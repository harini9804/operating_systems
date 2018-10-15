#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>

#define MAX 50

typedef struct Pars
{
	int low;
	int high;
}pars;

void * Quick_Sort(void * Par);
int partition ( int low, int high) ;
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int arr[MAX];

int main(int argc, char const *argv[])
{
	int n;
	printf("%s\n","\n Enter the size of the array" );
	scanf("%d",&n);

	int i;

	printf("%s\n","Enter the array elements" );


	for (i = 0; i < n; ++i)
	{
		scanf("%d",&arr[i]);
	}

	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr,SCHED_RR);

	pars * Ps=(pars *)malloc(sizeof(pars));
	Ps->low=0,Ps->high=n-1;

	pthread_create(&tid,&attr,Quick_Sort,(void*)Ps); // starter thread

	pthread_join(tid,NULL);

	printf("%s\n"," this is sorted" );
	for (i = 0; i < n; ++i)
	{
		printf("%d  ",arr[i]);
	}

	return 0;
}



void * Quick_Sort(void *Par)
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







	// pars * P=(pars *)malloc(sizeof(pars));
		pars * P=(pars * )Par;

		pars * Ps=(pars *)malloc(sizeof(pars));
		if(P->low<P->high)
		{
			pthread_t tid[2];
			pthread_attr_t attr;

			pthread_attr_init(&attr);
			int pi=partition(P->low,P->high);


			Ps->low=P->low,Ps->high=pi-1;

			P->low=pi+1;
			pthread_attr_setschedpolicy(&attr,SCHED_FIFO);

			pthread_create(&tid[0],&attr,Quick_Sort,(void*)Ps);
			pthread_create(&tid[1],&attr,Quick_Sort,(void*)P);

			if(pthread_attr_getschedpolicy(&attr,&schedpolicy)!=0)
				printf("%s\n","CANNOT GET SCOPE.");
			else if(schedpolicy == SCHED_RR)
				printf("%s\n","ROUND ROBIN" );
			else if(schedpolicy == SCHED_FIFO)
				printf("%s\n", "SCHED FIFO" );
				else
				printf("\nDonno policy");


			for (int i = 0; i < 2; ++i)
			{
				pthread_join(tid[i],NULL);
			}

		}
		free(Ps);
}


int partition ( int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

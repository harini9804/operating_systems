/* execute with -lm -lpthread */

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define ITER 10000
int no_cpt;
int no_sqpt;
void *runner(void *param);

void *runner(void *param){

  srand(time(0));
  double randx, randy, distance,pi;

  for(int i=0;i<ITER;i++){
    randx = (double)(rand()%(ITER + 1))/ITER;
    randy = (double)(rand()%(ITER + 1))/ITER;

    distance = (double)(randx*randx+randy*randy);
    distance = sqrt(distance);

    if(distance<=1){
      no_cpt++;
    //  printf("\nin circle");
    }
    no_sqpt++;

  }

}
int main(){


  no_cpt=0;
  no_sqpt=0;
  pthread_t tid[10];

  for(int i=0;i<10;i++)
  {
    pthread_create(&tid[i],NULL,runner,NULL);
  }

 //sleep(10);
 pthread_join(tid,NULL);
 printf("\nNo of circle points: %d",no_cpt );
 printf("\nNo of square points: %d",no_sqpt );
  double pi = 4 * ((double) no_cpt/no_sqpt);

  printf("\nEstimated value of pi: %lf ", pi );

   pthread_exit(NULL);
  return 0;
}

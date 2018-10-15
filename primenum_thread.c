#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void *runner(void *param);
int checkPrime(int x);
void *runner(void *param){
  // pthread_t tid;
  // tid = pthread_self();
  // printf("\nI'm thread number %u\n", tid);

//  sleep(10);
  int num = (int) param;

  for(int i=num;i<=num+10;i++){
    if(checkPrime(i))
      printf(" %d ",i );
  }
  pthread_exit(NULL);
}

int checkPrime(int x){
  if((x==0)||(x==1))
    return 0;
  if(x<0)
    return 0;
  for(int i=2;i<=x/2;i++){
    if(x%i == 0){
      return 0;
    }
  }
  return 1;
}
int main(int argc, char* argv[]){

  int num_l,spl,j;
  if(argc==1){
    printf("\nError.");
    exit(0);
  }
  int num = atoi(argv[1]);
//  printf("%d",num);

  spl = num / 10;
  pthread_t tid;
  pthread_attr_t attr;

  j=0;
  for(int i = 0; i< spl; i++){

    //  printf("%d ",i);
    //pthread_create(&tid,&attr,runner,(void *)i); causes core dump.
      pthread_create(&tid,NULL,runner,(void *)j);
      j+=10;
      pthread_join(tid,NULL);

  }
//  sleep(10);
  pthread_exit(NULL);

  return 0;
}

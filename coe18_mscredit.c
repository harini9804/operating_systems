#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

struct data{

  int N;
  int mat_no;
  int start;
};

int **a_quad[4];

void *fillmatrix(void *param){

  struct data *arg = (struct data*)param;
  int N = arg->N;
  int mat_no = arg->mat_no;
  int start = arg->start;

  int **a = (int **)malloc(sizeof(int *)*N);
  for(int i=0;i<N;i++){
    a[i] = (int *)malloc(sizeof(int)*N);
    for(int j=0;j<N;j++){
      a[i][j]=-1;
    }
  }



  int magic_constant;
  magic_constant = N*(N*N + 1)/2;
  printf("Magic constant %d ",magic_constant);
  int med = N/2;
  int count=1;
  a[0][med] = start;
  start++;
  count++;

  int cur_i = 0, cur_j = med;
  int i,j;
  while(count<=N*N){

    i = cur_i -1;
    j = cur_j + 1;

    if((i<0)&&(j>N-1)){
      i = N-1;
      j=0;
    }
    else if(i<0){
      i = N-1;
    }
    else if(j>N-1){
      j = 0;
    }
    if(a[i][j]!=-1){
      i = cur_i + 1;
      j = cur_j;
    }

    a[i][j] = start;
    start++;
    count++;
    cur_i =i;
    cur_j =j;
  }

  a_quad[mat_no] = a;
  pthread_exit(0);

}

void displayMat(int **a,int N){
  for(int i=0;i<N;i++){
    printf("\n");
    for(int j=0;j<N;j++){
      printf("%d ",a[i][j]);
    }
  }
}

int main(){

  pthread_t tid[4];

  int N;
  printf("\nEnter N: ");
  scanf("%d",&N );
  int N_quad = N/2;
  int range = N*N;

  struct data *arg[4];
  for(int i=0;i<4;i++){

    a_quad[i] = (int **)malloc(sizeof(int *)*N_quad);

    arg[i] = (struct data*)malloc(sizeof(struct data));
    arg[i]->N = N_quad;
    arg[i]->mat_no = i;
  }
  arg[0]->start = 1;
  arg[1]->start = range/2 +1;
  arg[2]->start = (3*range)/4+1;
  arg[3]->start = range/4 + 1;

  for(int i=0;i<4;i++){
    pthread_create(&tid[i],NULL,fillmatrix,arg[i]);
  }
  for(int i=0;i<4;i++){
    pthread_join(tid[i],NULL);
  }

  printf("\nMatrices: ");
  for(int i=0;i<4;i++){
    printf("\n Matrix %d", i);
    displayMat(a_quad[i],N_quad);
  }


  return 0;
}

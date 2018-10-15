#include<stdio.h>
#include<pthread.h>

#define MAX 4
int N;
int mat[MAX][MAX];

void* det_of_matrix(void* param);

void* det_of_matrix(void* param){

  int D =0;
  if(N==1)
    D = mat[0][0];

  int temp[N][N];
  int sign =1;

  for(int f=0;f<N;f++){
    cofactor(temp,0,f,N);
    D+=sign*mat[0][f]*determinant(temp);
    sign = -sign;
  }

  
}


int main(){



  return 0;
}

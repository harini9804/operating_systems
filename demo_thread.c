#include<stdio.h>
#include<pthread.h>


int (*v)(int);
int f(int x){

  return x+1;
}
int main(){

  v =f;
  printf("%d",(*v)(3));

  return 0;
}

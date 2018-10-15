#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){

  for(int i =0;i<3;i++){
    fork();
    printf("* %d",i);
  }

  return 0;
}

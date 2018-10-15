#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>

void collatz_conj(int num);
void collatz_conj(int num){

  int no_of_terms;
  printf("\nEnter the number of terms you want to generate: ");
  scanf("%d",&no_of_terms);
  printf("\n");
  for(int i =0; i<no_of_terms;i++){
    printf("%d, ",num);
    if(num%2==0){
      num/=2;
    }else{
      num = (3*num) + 1;
    }
  }
}
int main(){

  int num;
  printf("\nCollatz Conjecture.");
  printf("\nEnter a positive integer:");
  scanf("%d",&num);
  if(num<=0){
    printf("\nError");
    exit(0);
  }

  pid_t pid = fork();
  if(pid<0){
    fprintf(stderr, "%s\n","Could not fork." );
  }
  else if(pid == 0){
    printf("\nIn Child Process.");
    collatz_conj(num);
  }else{
    pid = wait(NULL);
  }

  return 0;
}

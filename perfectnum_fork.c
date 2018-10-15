#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int isPerfectNumber(int num);
int isPerfectNumber(int num){
  int sum =0;
  for(int i =1;i<num;i++){
    if(num%i == 0){
      sum+=i;
    }
  }
  if(num == sum){
    return 1;
  }
  return 0;
}

int main()
{
  int start, end, num,sum=0, flag=0;
  printf("\nPerfect Number Generation");
  printf("\nEnter start and end of range: ");
  scanf("%d%d",&start,&end);

  pid_t pid = fork();
  if(pid<0){
    fprintf(stderr, "%s\n","Could not fork" );
  }
  else if(pid == 0)
  {
    printf("\nIn Child Process:");
    num = start;
    while(num<=end){
      flag = isPerfectNumber(num);
      if(flag){
        printf("\n%d is a perfect number",num);
      }
      num++;
    }
  }
  else{
    pid = wait(NULL);
  }
  return 0;
}

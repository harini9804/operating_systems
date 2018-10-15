#include<stdio.h>
#include<pthread.h>

int n;

void sort(int *arr);
void* mean(void* param);
void* median(void* param);
void* mode(void* param);
void* mean(void* param){
  printf("\nMean.");
  int sum=0;
  int *arr =  (int *)param;
  for(int i=0;i<n;i++){
    sum+=arr[i];
  }
  float mean = (float) sum/n;
  printf("\nMean is %f",mean );
}
void* median(void* param){
  printf("\nMedian.");
  int *arr =  (int *)param;

  if(n%2==0){
    printf("\nMedians are %d and %d.",arr[n/2 - 1],arr[n/2]);
  }
  else{
    printf("\nMedian is %d",arr[n/2]);
  }
}
void* mode(void* param){
  printf("\nMode.");
  int *arr = (int *)param;
  int count=1,max=1,mode=arr[0];
  for(int i=1;i<n;i++){
    if(arr[i]==arr[i-1]){
      count++;
    }
    else{
      count = 1;
    }
    if(count>=max){
      mode = arr[i];
      max = count;
    }
  }
  printf("\nMode is %d",mode);
}

void sort(int *a){

  int temp;
  for(int i=0;i<n-1;i++){
    for(int j=0;j<n-i-1;j++){
      if(a[j]>a[j+1]){
        temp = a[j];
        a[j]=a[j+1];
        a[j+1]=temp;
      }
    }
  }

}
int main(){

  printf("\nEnter the number of integers: ");
  scanf("%d",&n);
  int arr[n];
  printf("\nEnter the integers: ");
  for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);
  }

  pthread_t tid;

  pthread_create(&tid,NULL,mean,(void*)arr);
  sort(arr);
  pthread_create(&tid,NULL,median,(void*)arr);
  pthread_create(&tid,NULL,mode,(void*)arr);

  pthread_exit(NULL);




  return 0;
}

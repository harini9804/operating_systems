#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

struct med_data{
  int *arr;
  int n;
  int quar_no;
};

#define MAX 10
int q1,med,q3;
int iqr;
int min_out[MAX];
int minsize;
int max_out[MAX];
int maxsize;
void sort(int *a, int n);
void *min_outliers(void* param);
void *min_outliers(void* param){

  struct med_data *data = (struct med_data *) param;
  int *arr = data->arr;
  int n = data->n;
  int k=0;
  for(int i=0;i<n;i++){
    if(q1-arr[i]>=1.5*iqr){
      min_out[k] = arr[i];
      k++;
    }
  }
  minsize = k;
    printf("\nNo of elements in min outliers %d",minsize );
}
void *max_outliers(void* param);
void *max_outliers(void* param){

  struct med_data *data = (struct med_data *) param;
  int *arr = data->arr;
  int n = data->n;
  int k=0;
  for(int i=0;i<n;i++){
    if(arr[i]-q3>=1.5*iqr){
      max_out[k] = arr[i];
      k++;
    }
  }
  maxsize = k;
  printf("\nNo of elements in max outliers %d",maxsize );

}

void sort(int *a, int n){

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
  printf("\nSorted array: ");
  for(int i=0;i<n;i++){
    printf("%d ",a[i]);
  }
}
void* median(void* param);
void* median(void* param){
  printf("\nMedian.");
  struct med_data *data =  (struct med_data *)param;
  int n = data->n;
  int *arr = data->arr;
  // if(n%2==0){
  //   printf("\nMedians are %d and %d.",arr[n/2 - 1],arr[n/2]);
  // }

  printf("\nMedian for %d numbers is %d",n,arr[n/2]);
  if(data->quar_no ==1){
    q1 = arr[n/2];
    printf("\nMedian 1 is %d",arr[n/2]);
  }
  else if(data->quar_no ==2){
    med = arr[n/2];
    printf("\nMedian 2 is %d",arr[n/2]);
  }
  else if(data->quar_no == 3){
    int medpos = (n - n/2)/2 + n/2;
    q3 = arr[medpos];
    printf("\nMedian 3 is %d",arr[n/2]);
  }

}

int main(){

  struct med_data *data1 = (struct med_data*)malloc(sizeof(struct med_data));
  struct med_data *data2 = (struct med_data*)malloc(sizeof(struct med_data));
  struct med_data *data3 = (struct med_data*)malloc(sizeof(struct med_data));


  int n;
  q1=q3=-1;
  printf("\nEnter number of integers: ");
  scanf("%d",&n);
  int arr[n];

  printf("\nEnter the integers: ");
  for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);
  }

  data1->arr = arr;
  data2->arr = arr;
  data3->arr = arr;
  data1->n = n/2;
  data1->quar_no = 1;

  data2->n = n;
  data2->quar_no = 2;

  data3->n = n;
  data3->quar_no = 3;

  pthread_t tid1,tid2,tid3;
  sort(arr, n);

  pthread_create(&tid1,NULL,median,data1);

  pthread_create(&tid2,NULL,median,data2);

  pthread_create(&tid3,NULL,median,data3);

  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);

  printf("\n----------\n");
  printf("\nMin %d \nFirst Quartile %d\nMedian %d\nThird Quartile %d\nMax %d\n",arr[0],q1,med,q3,arr[n-1]);

  int iqr = q3-q1;

  pthread_create(&tid1,NULL,min_outliers,data2);
  pthread_create(&tid2,NULL,max_outliers,data2);

  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  printf("\nMin outliers: ");
  for(int i=0;i<minsize;i++){
    printf("%d ",min_out[i] );
  }

  printf("\nMax outliers: ");
  for(int i=0;i<maxsize;i++){
    printf("%d ",max_out[i] );
  }

    pthread_exit(NULL);

  return 0;
}

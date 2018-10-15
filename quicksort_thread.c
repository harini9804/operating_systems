#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
struct pos{
  int low;
  int high;
};
#define MAX 50
int arr[MAX];
void *quicksort(void *param);
int partition (int low, int high);
void swap(int* a, int* b);
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition (int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void *quicksort(void *param)
{
  struct pos *data = param;
  int low,high;
  low = data->low;
  high = data->high;
  struct pos *arg1 = (struct pos *)malloc(sizeof(struct pos));
  struct pos *arg2 = (struct pos *)malloc(sizeof(struct pos));
  if(low<high){
    int pi = partition(low,high);
    arg1->low = low;
    arg1->high = pi -1;
    arg2->low = pi + 1;
    arg2->high = high;
    pthread_t tid[2];
    pthread_create(&tid[0],NULL,quicksort,arg1);
    pthread_create(&tid[1],NULL,quicksort,arg2);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);

  }
}

int main(){

//  runner = quicksort;
  int n;
  printf("\nEnter the number of integers: " );
  scanf("%d",&n);
  printf("\nEnter the integers: ");
  for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);
  }
  pthread_t tid;
  struct pos *arg = (struct pos *)malloc(sizeof(struct pos));
  arg->low = 0;
  arg->high = n-1;
  pthread_create(&tid,NULL,quicksort,arg);
  pthread_join(tid,NULL);
  printf("\nDone!");
  printf("\nThe integers in sorted order: ");
  for(int i=0;i<n;i++){
    printf("%d ",arr[i]);
  }
  pthread_exit(NULL);


  return 0;

}

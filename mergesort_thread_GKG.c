#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX 5
int a[MAX];
int n;
int part;

// merge function for merging two parts
void merge(int low, int mid, int high)
{
    int* left = (int *) malloc(sizeof(int)*(mid - low + 1));
    int* right = (int *) malloc(sizeof(int)*(high - mid));

    // n1 is size of left part and n2 is size
    // of right part
    int n1 = mid - low + 1, n2 = high - mid, i, j;

    // storing values in left part
    for (i = 0; i < n1; i++)
        left[i] = a[i + low];

    // storing values in right part
    for (i = 0; i < n2; i++)
        right[i] = a[i + mid + 1];

    int k = low;
    i = j = 0;

    // merge left and right in ascending order
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    // insert remaining values from left
    while (i < n1) {
        a[k++] = left[i++];
    }

    // insert remaining values from right
    while (j < n2) {
        a[k++] = right[j++];
    }
}


// merge sort function
void merge_sort_a(int low, int high)
{
    // calculating mid point of array
    int mid = low + (high - low) / 2;
    if (low < high) {

        // calling first half
        merge_sort_a(low, mid);

        // calling second half
        merge_sort_a(mid + 1, high);

        // merging the two halves
        merge(low, mid, high);
    }
}

void* merge_sort(void* arg){

  int thread_part = part++;

  int low = thread_part * ( n / 4);
  int high = (thread_part+1)*(n/4)-1;

  int mid = low+(high - low)/2;
  if (low<high){
    merge_sort_a(low,mid);
    merge_sort_a(mid+1,high);
    merge(low,mid,high);
  }


}

int main()
{
  part=0;
  printf("\nEnter the number of integers: ");
  scanf("%d",&n);
  printf("\nEnter the integers: ");

  for(int i=0;i<n;i++){
    scanf("%d",&a[i]);
  }

  pthread_t threads[4];
  for(int i=0;i<4;i++)
    pthread_create(&threads[i],NULL,merge_sort, (void *)NULL);

  for(int i=0;i<4;i++)
    pthread_join(threads[i],NULL);

  merge(0,(n/2 -1)/2, n/2 -1);
  merge(n/2,n/2+(n-1-n/2)/2, n-1);
  merge(0,(n-1)/2,n-1);

  printf("\nSorted array: ");
  for(int i=0;i<n;i++){
    printf("%d",a[i]);
  }





  return 0;
}

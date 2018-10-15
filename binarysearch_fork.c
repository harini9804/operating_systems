#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int arr_sort(int a[], int n);
int binary_search(int a[], int n, int x);
int arr_sort(int a[], int n){
  int temp;
  for(int i =0; i < n - 1; i++){
    for(int j =0;j<n-i-1;j++){
      if(a[j]>a[j+1]){
        temp = a[j];
        a[j]=a[j+1];
        a[j+1]=temp;
      }
    }
  }
  printf("\nSorted array: " );
  for(int i=0;i<n;i++){
    printf("%d ",a[i]);
  }
}
int binary_search(int a[], int n, int x){
  int beg = 0, end = n-1, mid;


  while(beg<=end){
  //  printf("%d and %d",beg,end);
    mid = (beg+end)/2;
    if(x==a[mid]){
      return mid;
    }
    else if(x<a[mid]){
      end = mid -1;
    }
    else{
      beg = mid+1;
    }
  }
  return -1;
}
int main(){

  int n;
  printf("\nBinary Search.");
  printf("\nEnter the number of elements: ");
  scanf("%d",&n);
  int a[n];
  printf("\nEnter the elements (need not be sorted): ");
  for(int i=0;i<n;i++){
    scanf("%d",&a[i]);
  }
  pid_t pid = fork();
  if(pid<0){
    fprintf(stderr, "%s\n","Could not fork." );
  }
  else if(pid == 0){
    int x,pos=-1;
    printf("\nIn Child Process.");
    printf("\nSorting array..");
     arr_sort(a,n);
    // printf("\nEnter the element you want to search for: ");
    // scanf("%d",&x);
    // pos = binary_search(a,n,x);
    // if(pos>=0){
    //     printf("\n%d is found at position %d",x,pos+1 );
    // }else{
    //   printf("\n%d not found",x);
    // }
  }
  else{

    pid = wait(NULL);
   printf("\nIn Parent Process.");
   int x,pos=-1;
   printf("\nEnter the element you want to search for: ");
   scanf("%d",&x);
   pos = binary_search(a,n,x);
   if(pos>=0){
       printf("\n%d is found at position %d",x,pos+1 );
   }else{
     printf("\n%d not found",x);
   }
    // for(int i=0;i<n;i++){
    //   printf("%d ",a[i]);
    // }
 }

  return 0;
}

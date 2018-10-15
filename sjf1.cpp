
#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include "processclass.h"
using namespace std;

void scheduler::sjf(vector<process> &procList, int n)
{

  int start=0,end=0,i,j,flag;
  int min=0, min_index=0;
  // for first process
  procList[0].ct =procList[0].at + procList[0].bt;
  procList[0].tat = procList[0].ct - procList[0].at;
  procList[0].wt = procList[0].tat - procList[0].bt;

  int cur_exetime = procList[0].ct;
  int arr_time = procList[0].at;

  while(1)
  {
    cout<<"\ncur exe time"<<cur_exetime;
    flag=0;
    for(j=0;j<n;j++){
      if(!procList[j].ct)
      {
        flag=1;
        break;
      }
      else
      cout<<procList[j].ct<<endl;
    }
    if(!flag){
      cout<<"\nProcesses completed";
      break;
    }
    else{
      min = procList[j].bt;
      min_index = j;
    }

    // finding min
    for(i = 0; i<n; i++ )
    {
      if( (!procList[i].ct) && (procList[i].at<=cur_exetime) )
      {
        if(procList[i].bt <= min)
        {
          cout<<"\nPID:"<<procList[i].pid;
          if((procList[i].bt == min) && (procList[i].at <procList[min_index].at)){
            min_index = i;
            min = procList[i].bt;
          }
          else if(procList[i].bt < min){
            min_index = i;
            min = procList[i].bt;
          }

        }
      }

    }
    cout<<"\nshortest job"<<procList[min_index].pid;

    if(procList[min_index].at > cur_exetime){
      procList[min_index].ct = procList[min_index].at + procList[min_index].bt;
      cur_exetime = procList[min_index].ct;
      procList[min_index].tat = procList[min_index].ct - procList[min_index].at;
      procList[min_index].wt = procList[min_index].tat - procList[min_index].bt;
    }
    else{
    procList[min_index].ct = cur_exetime + procList[min_index].bt;
    cur_exetime = procList[min_index].ct;
    procList[min_index].tat = procList[min_index].ct - procList[min_index].at;
    procList[min_index].wt = procList[min_index].tat - procList[min_index].bt;
    }


  }

  int sum =0;
  for(int i =0 ; i<n ;i++){
    procList[i].output();
    sum+= procList[i].wt;
  }
  float avg = (float) sum / n;
  cout<<"\nAverage waiting time: "<<avg;

}

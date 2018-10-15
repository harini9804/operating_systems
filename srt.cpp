#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include "processclass.h"
using namespace std;

typedef vector< pair<int,int> >::iterator iterType;

bool sort_remtime(const process& obj1, const process& obj2){
  return obj1.bt < obj2.bt ;
}

int find_srtprocess(vector<process> procList, int cur_exetime, int n){

  int min_proc,min,i;

  for( i =0 ; i<n;i++)
  {
    if(procList[i].bt != 0)
        break;
  }

  if(i==n)
  {
    return -1; // all processes completed.
  }

  else{
    min_proc = i;
    min = procList[min_proc].bt;
  }

  for( int i = 0; i < n; i++)
  {
    if( (procList[i].at <= cur_exetime )&&(procList[i].bt <= min) &&(procList[i].bt != 0) ) // within arrival time and has min rem time
    {
      if( (procList[i].bt == min) && (procList[i].at < procList[min_proc].at) ){ // if two mins, choose the earlier
        min_proc = i;
        min = procList[i].bt;
      }
      else if (procList[i].bt < min){
        min_proc = i;
        min = procList[i].bt;
      }
      // else stick to min.
    }

  }

  return min_proc;

}

bool sort_atbt(const process& obj1, const process& obj2){

  if(obj1.at==obj2.at){
    return obj1.bt < obj2.bt ;
  }
  return obj1.at < obj2.at;
}
void scheduler::srt(vector<process> &procList, int n)
{
  vector<process> procList1;

  sort(procList.begin(),procList.end(),sort_atbt);

  procList1.assign(procList.begin(),procList.end());

  sort(procList.begin(),procList.end(),sort_atbt);

  int exe_time = 0;
  int cur_process = 0;
  int cur_time = procList[0].at;
  int cur_exetime = procList[0].at;
  int flag =0;

  int next_arrival_time =0;

  int i;
cout<<"\nBefore the while:";
  while(cur_process!=-1)
  {

    cur_time = procList[cur_process].at;

    if(cur_exetime > procList[n-1].at)
    {
      // no more interruptions
      cout<<"\nlike sjf";
      while(cur_process!=-1)
      {
        cur_process = find_srtprocess(procList, cur_exetime, n);


        if(cur_process == -1)
          break;
        else{
          cout<<"\nPID is: "<<procList[cur_process].pid;
          cur_exetime += procList[cur_process].bt;
          procList[cur_process].bt = 0;
          procList[cur_process].ct = cur_exetime;
        }

      }
      for(i =0 ; i<n ;i++){
        procList[i].tat = procList[i].ct - procList[i].at;
        procList[i].bt = procList1[i].bt;
        procList[i].wt = procList[i].tat - procList[i].bt;
        procList[i].output();
      }
      return;

    }

    i = cur_process;
    while( cur_time == procList[i].at)
    {
        i++;

        if(i == n){
          cout<<"no proc";
          break;
        }

    }
    if(i==n){
      next_arrival_time = procList[cur_process].at;
    }
    else
      next_arrival_time = procList[i].at;

    if(next_arrival_time == cur_time){
      cout<<"no new arrivals";
      cur_exetime += procList[cur_process].bt;
      procList[cur_process].bt = 0 ;
      procList[cur_process].ct = cur_exetime;

    }
    else if(next_arrival_time <= cur_time + procList[cur_process].bt)
    {
      exe_time = next_arrival_time - cur_time;
      if(exe_time<0){
        cout<<"error.";
      }
      procList[cur_process].bt -= exe_time;
      cur_exetime += exe_time;

      if(procList[cur_process].bt ==0)
      {
        procList[cur_process].ct = cur_exetime;
      }

    }

    else
    {

      cur_exetime += procList[cur_process].bt;
      procList[cur_process].bt = 0 ;
      procList[cur_process].ct = cur_exetime;

    }
    cout<<"\nCurrent process arrival time: "<<procList[cur_process].at;
    cout<<"\nCurrent PID: "<<procList[cur_process].pid;
    cout<<"\nRemaining time: "<<procList[cur_process].bt;

    cur_process = find_srtprocess(procList, cur_exetime, n);

  }

  for(i =0 ; i<n ;i++){
    procList[i].tat = procList[i].ct - procList[i].at;
    procList[i].bt = procList1[i].bt;
    procList[i].wt = procList[i].tat - procList[i].bt;
    procList[i].output();
  }

}

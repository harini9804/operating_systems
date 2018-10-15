#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include "processclass.h"
using namespace std;


bool sort_atpri(const processPri& obj1, const processPri& obj2){

  if(obj1.at==obj2.at){
    return obj1.pri > obj2.pri ;
  }
  return obj1.at < obj2.at;
}
int find_priprocess(vector<processPri> procPriList, int cur_exetime, int n){

  int max_proc,max,i;

  for( i =0 ; i<n;i++)
  {
    if(procPriList[i].bt != 0)
        break;
  }

  if(i==n)
  {
    return -1; // all processes completed.
  }

  else{
    max_proc = i;
    max = procPriList[max_proc].pri;
  }

  for( int i = 0; i < n; i++)
  {
    if( (procPriList[i].at <= cur_exetime )&&(procPriList[i].pri >= max) &&(procPriList[i].bt != 0) ) // within arrival time and has min rem time
    {
      if( (procPriList[i].pri == max) && (procPriList[i].at < procPriList[max_proc].at) ){ // if two mins, choose the earlier
        max_proc = i;
        max = procPriList[i].pri;
      }
      else if (procPriList[i].pri > max){
        max_proc = i;
        max = procPriList[i].pri;
      }
      // else stick to max.
    }

  }

  return max_proc;
}
void scheduler::priority_pe(vector<process> &procList, int n){

  vector<processPri> procPriList;
  vector<processPri>::iterator itPri;
  processPri procPriObj;

  for(int i=0; i<n; i++)
  {

    procPriObj.at = procList[i].at;
    procPriObj.bt = procList[i].bt;
    procPriObj.pid = procList[i].pid;
    cout<<"\nEnter the priority of process "<<procList[i].pid<<" : ";
    cin>>procPriObj.pri;
    procPriList.push_back(procPriObj);

  }

  sort(procPriList.begin(),procPriList.end(),sort_atpri);


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

    cur_time = procPriList[cur_process].at;

    if(cur_exetime > procList[n-1].at)
    {
      // no more interruptions
      cout<<"\nlike sjf";
      while(cur_process!=-1)
      {
        cur_process = find_priprocess(procPriList, cur_exetime, n);


        if(cur_process == -1)
          break;
        else{
          cout<<"\nPID is: "<<procPriList[cur_process].pid;
          cur_exetime += procPriList[cur_process].bt;
          procPriList[cur_process].bt = 0;
          procPriList[cur_process].ct = cur_exetime;
        }

      }
      for(i =0 ; i<n ;i++){
        procPriList[i].tat = procPriList[i].ct - procPriList[i].at;
        procPriList[i].bt = procList[i].bt;
        procPriList[i].wt = procPriList[i].tat - procPriList[i].bt;
        procPriList[i].output();
      }
      return;

    }

    i = cur_process;
    while( cur_time == procPriList[i].at)
    {
        i++;

        if(i == n){
          cout<<"no proc";
          break;
        }

    }
    if(i==n){
      next_arrival_time = procPriList[cur_process].at;
    }
    else
      next_arrival_time = procPriList[i].at;

    if(next_arrival_time == cur_time){
      cout<<"no new arrivals";
      cur_exetime += procPriList[cur_process].bt;
      procPriList[cur_process].bt = 0 ;
      procPriList[cur_process].ct = cur_exetime;

    }
    else if(next_arrival_time <= cur_time + procPriList[cur_process].bt)
    {
      exe_time = next_arrival_time - cur_time;
      if(exe_time<0){
        cout<<"error.";
      }
      procPriList[cur_process].bt -= exe_time;
      cur_exetime += exe_time;

      if(procPriList[cur_process].bt ==0)
      {
        procPriList[cur_process].ct = cur_exetime;
      }

    }

    else
    {

      cur_exetime += procPriList[cur_process].bt;
      procPriList[cur_process].bt = 0 ;
      procPriList[cur_process].ct = cur_exetime;

    }
    cout<<"\nCurrent process arrival time: "<<procPriList[cur_process].at;
    cout<<"\nCurrent PID: "<<procPriList[cur_process].pid;
    cout<<"\nRemaining time: "<<procPriList[cur_process].bt;

    cur_process = find_priprocess(procPriList, cur_exetime, n);

  }





}

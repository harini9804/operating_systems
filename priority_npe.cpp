#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include "processclass.h"
using namespace std;

bool sort_atpri_npe(const processPri& obj1, const processPri& obj2){

  if(obj1.at==obj2.at){
    return obj1.pri > obj2.pri ;
  }
  return obj1.at < obj2.at;
}

void scheduler::priority_npe(vector<process> &procList, int n){

  vector<processPri> procPriList;
  vector<processPri>::iterator itPri;
  processPri procPriObj;

  for(int i=0; i<n; i++)
  {

    procPriObj.at = procList[i].at;
    procPriObj.bt = procList[i].bt;
    procPriObj.pid = procList[i].pid;
    procPriObj.ct = procList[i].ct;

    cout<<"\nEnter the priority of process "<<procList[i].pid<<" : ";
    cin>>procPriObj.pri;
    procPriList.push_back(procPriObj);

  }

  sort(procPriList.begin(), procPriList.end(),sort_atpri_npe);

    int start=0,end=0,i,j,flag;
    int max=0, max_proc=0;
    // for first process
    procPriList[0].ct =procPriList[0].at + procPriList[0].bt;
    procPriList[0].tat = procPriList[0].ct - procPriList[0].at;
    procPriList[0].wt = procPriList[0].tat - procPriList[0].bt;

    int cur_exetime = procPriList[0].ct;
    int arr_time = procPriList[0].at;

    while(1)
    {
      cout<<"\ncur exe time"<<cur_exetime;
      flag=0;
      for(j=0;j<n;j++){
        if(!procPriList[j].ct)
        {
          flag=1;
          break;
        }
      }
      if(!flag){
        cout<<"\nProcesses completed";
        break;
      }
      else{
        max = procPriList[j].pri;
        max_proc = j;
      }

      // finding min
      for(i = 0; i<n; i++ )
      {
        if( (!procPriList[i].ct) && (procPriList[i].at<=cur_exetime) )
        {
          if(procPriList[i].pri >= max)
          {
            cout<<"\nPID:"<<procPriList[i].pid;
            if((procPriList[i].pri == max) && (procPriList[i].at <procPriList[max_proc].at)){
              max_proc = i;
              max = procPriList[i].pri;
            }
            else if(procPriList[i].pri > max){
              max_proc = i;
              max = procPriList[i].pri;
            }

          }
        }

      }
      cout<<"\n priority job"<<procPriList[max_proc].pid;
      if(procPriList[max_proc].at > cur_exetime){
        procPriList[max_proc].ct = procPriList[max_proc].at + procPriList[max_proc].bt;
        cur_exetime = procPriList[max_proc].ct;
        procPriList[max_proc].tat = procPriList[max_proc].ct - procPriList[max_proc].at;
        procPriList[max_proc].wt = procPriList[max_proc].tat - procPriList[max_proc].bt;
      }
      else
      {
      procPriList[max_proc].ct = cur_exetime + procPriList[max_proc].bt;
      cur_exetime = procPriList[max_proc].ct;
      procPriList[max_proc].tat = procPriList[max_proc].ct - procPriList[max_proc].at;
      procPriList[max_proc].wt = procPriList[max_proc].tat - procPriList[max_proc].bt;
      }

    }

    int sum =0;
    for(int i =0 ; i<n ;i++){
      procPriList[i].output();
      sum+= procPriList[i].wt;
    }
    float avg = (float) sum / n;
    cout<<"\nAverage waiting time: "<<avg;

}

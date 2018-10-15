#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include "processclass.h"
using namespace std;

bool sort_atRR(const processRR& obj1, const processRR& obj2){

  if(obj1.at==obj2.at){
    return obj1.resp_ratio > obj2.resp_ratio ;
  }
  return obj1.at < obj2.at;
}

void scheduler::hrrn(vector<process> &procList, int n){

  vector<processRR> procRRList;
  processRR procRRObj;

  for(int i=0; i<n; i++)
  {

    procRRObj.at = procList[i].at;
    procRRObj.bt = procList[i].bt;
    procRRObj.pid = procList[i].pid;
    procRRObj.ct = procList[i].ct;

    procRRObj.resp_ratio = 1;

    procRRList.push_back(procRRObj);

  }

  sort(procRRList.begin(), procRRList.end(),sort_atRR);

    int start=0,end=0,i,j,flag;
    int max=0, max_proc=0;
    // for first process
    procRRList[0].ct =procRRList[0].at + procRRList[0].bt;
    procRRList[0].tat = procRRList[0].ct - procRRList[0].at;
    procRRList[0].wt = procRRList[0].tat - procRRList[0].bt;

    int cur_exetime = procRRList[0].ct;
    int arr_time = procRRList[0].at;

    while(1)
    {
      cout<<"\ncur exe time"<<cur_exetime;
      flag=0;
      for(j=0;j<n;j++){
        if(!procRRList[j].ct)
        {
          flag=1;
          break;
        }
        else if(procRRList[j].at <= cur_exetime){
          procRRList[j].wt = cur_exetime - procRRList[j].at;
          procRRList[j].resp_ratio = 1 + (float) procRRList[j].wt/procRRList[j].bt;
        }
      }
      if(!flag){
        cout<<"\nProcesses completed";
        break;
      }
      else{
        max = procRRList[j].resp_ratio;
        max_proc = j;
      }

      // finding max
      for(i = 0; i<n; i++ )
      {
        if( (!procRRList[i].ct) && (procRRList[i].at<=cur_exetime) )
        {
          if(procRRList[i].resp_ratio >= max)
          {
            cout<<"\nPID:"<<procRRList[i].pid;
            if((procRRList[i].resp_ratio == max) && (procRRList[i].at <procRRList[max_proc].at)){
              max_proc = i;
              max = procRRList[i].resp_ratio;
            }
            else if(procRRList[i].resp_ratio > max){
              max_proc = i;
              max = procRRList[i].resp_ratio;
            }

          }
        }

      }
      cout<<"\n HRRN job"<<procRRList[max_proc].pid<<' '<<procRRList[j].resp_ratio;

      if(procRRList[max_proc].at > cur_exetime){

        procRRList[max_proc].ct = procRRList[max_proc].at + procRRList[max_proc].bt;
        cur_exetime = procRRList[max_proc].ct;
        procRRList[max_proc].tat = procRRList[max_proc].ct - procRRList[max_proc].at;
        procRRList[max_proc].wt = procRRList[max_proc].tat - procRRList[max_proc].bt;
      }
      else{
      procRRList[max_proc].ct = cur_exetime + procRRList[max_proc].bt;
      cur_exetime = procRRList[max_proc].ct;
      procRRList[max_proc].tat = procRRList[max_proc].ct - procRRList[max_proc].at;
      procRRList[max_proc].wt = procRRList[max_proc].tat - procRRList[max_proc].bt;
    }


    }

    int sum =0;
    for(int i =0 ; i<n ;i++){
      procRRList[i].tat = procRRList[i].ct - procRRList[i].at;
      procRRList[i].wt = procRRList[i].tat - procRRList[i].bt;
      procRRList[i].output();
      sum+= procRRList[i].wt;
    }
    float avg = (float) sum / n;
    cout<<"\nAverage waiting time: "<<avg;

}

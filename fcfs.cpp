#include<stdio.h>
#include<iostream>
#include<vector>
#include "processclass.h"
using namespace std;

void scheduler::fcfs(vector<process> &procList, int no)
{

  for(int i=0;i<no;i++)
  {

    if(i==0)
      procList[i].ct = procList[i].bt + procList[i].at;
    else{
      if(procList[i].at >= procList[i-1].ct)
      {
        procList[i].ct = procList[i].at + procList[i].bt;
      //  idleTime+=procList[i].at - procList[i-1].ct;
      }
      else
        procList[i].ct = procList[i-1].ct + procList[i].bt;
    }

    procList[i].tat = procList[i].ct - procList[i].at;
    procList[i].wt = procList[i].tat - procList[i].bt;

  }

  int sum =0;
  for(int i =0 ; i<no ;i++){
    procList[i].output();
    sum+= procList[i].wt;
  }
  float avg = (float) sum / no;
  cout<<"\nAverage waiting time: "<<avg;

}

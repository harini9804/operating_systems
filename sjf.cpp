#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include "processclass.h"
using namespace std;

bool shorter(const process& obj1, const process& obj2){
  return obj1.bt < obj2.bt ;
}
void compute( vector<process>& procList, int start, int end)
{

  for(int i=start;i<=end;i++)
  {

    if(i==0)
      procList[i].ct = procList[i].bt + procList[i].at;

    else
    {

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

}

void scheduler::sjf(vector<process> &procList, int n)
{

  int start=0,end=0;
  // for first process
  procList[0].ct =procList[0].at + procList[0].bt;
  procList[0].tat = procList[0].ct - procList[0].at;
  procList[0].wt = procList[0].tat - procList[0].bt;

  int flag=0;

  for(int i=1 ; i<n; i++)
  {
    cout<<"start: "<<i<<endl;
    start = i;
    while(procList[i].at <= procList[start-1].ct)
    {
      flag =1;
      i++;

      if(i==n)
      break;
    }

    if(flag)
      i--;

    end = i;

    if(start>end)
    end = start;

    if(end >= n){
      cout<<"error";
      break;
    }

    //cout<<"\nstart: "<<start<<" end: "<<end<<endl;

    if(start<=end){
      sort(procList.begin()+start,procList.begin()+end+1,shorter);
    }

    // cout<<"\nPartial sort: ";
    // for(int j =0 ; j<n ;j++){
    //   procList[j].output();
    // }
    // cout<<endl;
    compute(procList,start,end);

  }

  int sum =0;
  for(int i =0 ; i<n ;i++){
    procList[i].output();
    sum+= procList[i].wt;
  }
  float avg = (float) sum / n;
  cout<<"\nAverage waiting time: "<<avg;

}

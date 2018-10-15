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

int min_remtime(int *a, int n){

  min = a[0][1];
  int pid = a[0][0];

  for(int i=0;i<n;i++){
    if(a[i][1]< min){
      pid = i; // since they are sorted according to arrival times, in case of tie, the earliest is chosen.
    }
  }
  return pid;
}

void scheduler::srt(vector<process> &procList, int n)
{
    int proc_remtime[n][2];
//    vector< pair<int,int> > proc_remtime;

//    pair<int,int> apair; // PID, Remaining time

    int start=0,end=0;
    int flag=0;

    for(int i=0; i<n; i++){

      proc_remtime[i][0] = procList[i].pid;
      proc_remtime[i][1] = procList[i].bt;

    }

    // for ( int i=0; i<n; i++){
    //   apair.first = procList[i].pid;
    //   apair.second = procList[i].bt;
    //
    //   proc_remtime.push_back(apair);
    // }
    //
    // for( iterType it= proc_remtime.begin(); it!=proc_remtime.end();it++ ){
    //   apair = *it;
    //   cout<<"\nPID: "<<apair.first;
    //   cout<<" Rem time: "<<apair.second;
    // }
    int cur_time = procList[0].at;
    int exe_time = 0;
    int cur_process = 0;

    int srt_pid;

    while( cur_process < n-1)
    {
      while( cur_time < = procList[cur_process + 1].at)
      {
        // for current process

        exe_time = procList[cur_process + 1].at - cur_time;
        proc_remtime[cur_process][1] = exe_time;

        // choose shortest remaining time
        
        srt_pid = min_remtime(proc_remtime, n);



      }


    }
    /*

    for(int i=0; i<n; i++)
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

      if(start<=end){
        sort(procList.begin()+start,procList.begin()+end+1,shorter);
      }

    }

    int sum =0;
    for(int i =0 ; i<n ;i++){
      procList[i].output();
      sum+= procList[i].wt;
    }
    float avg = (float) sum / n;
    cout<<"\nAverage waiting time: "<<avg;

*/
}

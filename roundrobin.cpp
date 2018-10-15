#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include "processclass.h"
using namespace std;

int isPresent(queue<process> procQ, process obj){

  process objQ;
  while(!procQ.empty()){

      objQ = procQ.front();
      if(obj.pid == objQ.pid){
        return 1;
      }

      procQ.pop();

  }

  return 0;

}

int getIndex(vector<process> &procList, process obj){
  for(int i =0;i< procList.size();i++)
  {
    if(procList[i].pid == obj.pid)
    return i;
  }
  return -1;
}

void scheduler::roundrobin(vector<process> &procList, int n){

  vector<process> procList1;
  procList1.assign(procList.begin(),procList.end());


  int time_quantum;
  cout<<"\nEnter time quantum: ";
  cin>>time_quantum;
  int i,arr_time = 0;
  int index;
  process procObj;
  queue<process> procQ;

  int cur_time = procList[0].at;
  int cur_exetime = procList[0].at;

  procQ.push(procList[0]);

  while(!procQ.empty())
  {
    procObj = procQ.front();
    cout<<"\nCurrent process PID: "<<procObj.pid;
    index = getIndex(procList, procObj);

    //Executed for time quantum.
    if(procList[index].bt < time_quantum)
    {

      cur_exetime+=procList[index].bt;
      procList[index].bt =0;

    }
    else
    {
      procList[index].bt -= time_quantum;
      cur_exetime += time_quantum;
    }


    i=0;
    arr_time = procList[i].at;

    while( (arr_time <= cur_exetime) )
    {
      if(!isPresent(procQ, procList[i]) && (procList[i].bt!=0))
      {
        procQ.push(procList[i]);
        cout<<"\nAdded PID: "<<procList[i].pid;
      }
      i++;

      if(i == n)
        break;

      arr_time = procList[i].at;
    }

    procQ.pop();
    if(procList[index].bt == 0){
      procList[index].ct = cur_exetime;
    }
    else{
      procQ.push(procObj);
    }

  }

  for(int i = 0;i<n ;i++){
    procList[i].tat = procList[i].ct - procList[i].at;
    procList[i].bt = procList1[i].bt;
    procList[i].wt = procList[i].tat - procList[i].bt;
    procList[i].output();
  }


}

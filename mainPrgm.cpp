#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include "processclass.h"

using namespace std;

void process::output(){

  cout<<"PID: "<<pid<<' ';
  cout<<"AT: "<<at<<' ';
  cout<<"BT: "<<bt<<' ';
  cout<<"CT: "<<ct<<' ';
  cout<<"TAT: "<<tat<<' ';
  cout<<"WT: "<<wt<<endl;
  cout<<"--------------"<<endl;


}
void processPri::output(){

  cout<<"PID: "<<pid<<' ';
  cout<<"Priority: "<<pri<<endl;
  cout<<"AT: "<<at<<' ';
  cout<<"BT: "<<bt<<' ';
  cout<<"CT: "<<ct<<' ';
  cout<<"TAT: "<<tat<<' ';
  cout<<"WT: "<<wt<<endl;
  cout<<"--------------"<<endl;


}
void process::input(int id){
  pid = id;
  cout<<"\nEnter arrival time: ";
  cin>>at;
  cout<<"\nEnter burst time: ";
  cin>>bt;
  ct = 0;
}
void processRR::output(){

  cout<<"PID: "<<pid<<' ';
  cout<<"ResponseRatio: "<<resp_ratio<<endl;
  cout<<"AT: "<<at<<' ';
  cout<<"BT: "<<bt<<' ';
  cout<<"CT: "<<ct<<' ';
  cout<<"TAT: "<<tat<<' ';
  cout<<"WT: "<<wt<<endl;
  cout<<"--------------"<<endl;


}

int main(){
  scheduler sch;
  vector<process> procList;
  process obj;
  int n;

  cout<<"\nEnter number of processes: ";
  cin>>n;

  for(int i=0;i<n;i++){
    obj.input(i);
    procList.push_back(obj);
  }

  sort(procList.begin(),procList.end());
  int switch_opt;

  char ch;
  do{
    cout<<"\nEnter\n1.FCFS\n2.SJF\n3.Shortest Remaining Time\n4.Priority Pre-Emptive\n5.Priority Non pre-emptive\n6.Round Robin\n7.HRRN\n8.Exit";
    cin>>switch_opt;
    switch (switch_opt) {
      case 1: cout<<"\nFCFS:";
              sch.fcfs(procList,n);
              break;
      case 2: cout<<"\nSJF:";
              sch.sjf(procList,n);
              break;
      case 3: cout<<"\nShortest Remaining Time:";
              sch.srt(procList,n);
              break;
      case 4: cout<<"\nPriority Pre-Emptive:";
              sch.priority_pe(procList,n);
              break;
      case 5: cout<<"\nPriority Non pre-emptive:";
              sch.priority_npe(procList,n);
              break;
      case 6: cout<<"\nRound Robin:";
              sch.roundrobin(procList,n);
              break;
      case 7: cout<<"\nHRRN:";
              sch.hrrn(procList,n);
              break;
      case 8: cout<<"\nBye!";
              exit(0);
              break;
    }

    cout<<"\nDo you want to continue y/n";
    cin>>ch;
  }while((ch=='y')||(ch=='Y'));
/*
  sort(procList.begin(),procList.end());
  sch.fcfs(procList,n);
  int sum =0;
  for(int i =0 ; i<n ;i++){
    procList[i].output();
    sum += procList[i].wt;
  }

  float avg = (float) sum / n;
  cout<<"\nAverage waiting time: "<<avg<<endl;

  cout<<"\nSJF: "<<endl;
  sort(procList.begin(),procList.end());
  sch.sjf(procList,n);
  sum =0;
  for(int i =0 ; i<n ;i++){
    procList[i].output();
    sum += procList[i].wt;
  }

  avg = (float) sum / n;
  cout<<"\nAverage waiting time: "<<avg<<endl;
  return 0;
*/
  // sort(procList.begin(),procList.end());
  // sch.srt(procList,n);

  // sort(procList.begin(),procList.end());
  // sch.roundrobin(procList,n);

  // sort(procList.begin(),procList.end());
  // sch.priority_pe(procList,n);

  // sort(procList.begin(),procList.end());
  // sch.priority_npe(procList,n);

  // sort(procList.begin(),procList.end());
  // sch.sjf(procList,n);

  // sort(procList.begin(),procList.end());
  // sch.hrrn(procList,n);


  return 0;

}

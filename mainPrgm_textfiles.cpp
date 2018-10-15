#include<string>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<array>
#include<regex>
#include<vector>
#include<map>

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
  at = id;
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
void map_display(map<int,string> namemap);
void map_display(map<int,string> namemap){
  for( auto &it : namemap){
    cout<<"PID: "<<it.first<<" File Name: "<<it.second<<endl;
  }
}
int main(){

  string command("ls -lt *.txt 2>&1");
  vector<process> procList;
  scheduler sch;

  map<int,string> namemap;

  array<char, 128> buffer;
  string result;

  regex r("\\w+.txt");
  regex rsize("lenovo\\s+(\\d+).+:\\d\\d\\s(\\w+.txt)");

  smatch m;
  string s;

  cout<<"Opening reading pipe: ";
  FILE *pipe = popen(command.c_str(), "r");

  if(!pipe){
    cerr<<"Couldn't start command.";
    return 0;
  }
 int res;
  while(fgets(buffer.data(),128,pipe)!= NULL){
    cout<<"Reading.."<<endl;
    result +=buffer.data();
  }
  auto returnCode = pclose(pipe);

  cout<<result<<endl;
  cout<<returnCode<<endl;

  sregex_iterator iter1(result.begin(),result.end(),rsize);
  sregex_iterator end;

  int count = 0;
  process obj;

  while(iter1 != end){

    cout<<"size: "<<iter1->size()<<endl;
    obj.input(count);
    namemap[count]=(*iter1)[2];
    obj.bt = stoi( (*iter1)[1] );

    procList.push_back(obj);

    count++;
    ++iter1;
  }

  sort(procList.begin(),procList.end());
  int switch_opt;
  int n = procList.size();
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
    map_display(namemap);

    cout<<"\nDo you want to continue y/n";
    cin>>ch;
  }while((ch=='y')||(ch=='Y'));

  return 0;
}

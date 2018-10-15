#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>

class process{

    public:

    int pid;
    int at;
    int bt;
    int ct,tat,wt;

    void input(int id);
    void output();

    bool operator < (const process& obj) const {
      if(at == obj.at){
        return bt < obj.bt;
      }else
      return at < obj.at;

    }

};
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

void process::input(int id){
  pid = id;
  cout<<"\nEnter arrival time: ";
  cin>>at;
  cout<<"\nEnter burst time: ";
  cin>>bt;
}

void compute( vector<process>& procList, int start, int end){

  for(int i=start;i<=end;i++)
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

}

struct compBurst
{
  inline bool operator()(const process &obj1, const process &obj2){
    return obj1.bt < obj2.bt ;
  }
};

bool shorter(const process& obj1, const process& obj2){
  return obj1.bt < obj2.bt ;
}
int main(){

  int n;
  cout<<"\nEnter the number of processes: ";
  cin>>n;
  vector<process> procList;

  process obj;

  for(int i=0;i<n;i++){
    obj.input(i);
    procList.push_back(obj);
  }

  sort(procList.begin(),procList.end());

  int start=0,end=0;
  for(int i =0 ; i<n ;i++){
    procList[i].output();
  }

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
      return -1;
    }

    cout<<"\nstart: "<<start<<" end: "<<end<<endl;

    if(start<=end){
      sort(procList.begin()+start,procList.begin()+end+1,shorter);
    }

    cout<<"\nPartial sort: ";
    for(int j =0 ; j<n ;j++){
      procList[j].output();
    }
    cout<<endl;
    compute(procList,start,end);

  }

  int sum =0;
  for(int i =0 ; i<n ;i++){
    procList[i].output();
    sum+= procList[i].wt;
  }
  float avg = (float) sum / n;
  cout<<"\nAverage waiting time: "<<avg;
  return 0;
}

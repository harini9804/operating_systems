#include<stdio.h>
#include<iostream>
#include<vector>
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
        return pid < obj.pid;
      }else
      return at < obj.at;

    }

};
class processPri: public process{
  public:
    int pri;

  void output();
};
class processRR: public process{
  public:
    float resp_ratio;

  void output();
};
using namespace std;

class scheduler{
public:
  void fcfs(vector<process> &ProcList, int n);
  void sjf(vector<process> &ProcList, int n);
  void srt(vector<process> &ProcList, int n);
  void roundrobin(vector<process> &ProcList, int n);
  void priority_npe(vector<process> &procList, int n);
  void priority_pe(vector<process> &ProcList, int n);
  void hrrn(vector<process> &procList, int n);
};

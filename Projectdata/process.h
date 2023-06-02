#pragma once
#include<iostream>
using namespace std;
#include "PairedQueue.h"
#include "PriorityQueue.h"
#include "Node.h"

class process
{
private:
    int Id = 0; //process ID;
    int cpu_time = 0;
    int Arr_time = 0; //arrival time;
    int R_time = 0;   //response time;
    int T_time = 0;   //termination time;
    int TR_time = 0;  //turnaround time;
    int W_time = 0;   //waiting time;
    int rem_time = 0; //remianning time;
    int exc_time = 0; //executing time;
    int N_ps = 0;     //num of time the process request I/O;
    int IO_R =-1;     //I/O request time;
    int IO_D ;     //I/O duration time;
    int early_dead;
 
    int KT;            //***  Kill Time: Time at which the process is killed 
    Node<process>* lc;  //***  A pointer to the LEFT CHILD of a forked process
    Node<process>* rc;  //***  A pointer to the RIGHT CHILD of a forked process
     //I/O duration time;
    bool Migrated;

    PairedQueue<int> iopairqueue;
    enum Status { NEW, RDY, RUN, BLK, TRM, ORPH };
    Status status;

public:
    //constructor
    process();

    process(int AT, int PID, int CT, int N);
    process(const process& p);//Copy Constructor for process
    //getters and setters
    int getID();
    int getCT();
    int getAT();
    int getTT();
    int getTRT();
    int getRT();
    int getWT();
    int getNUM();
    int getIOR();
    int getIOD();
    int getexc_time();
    int getEarlestDeadline();
    int getKillTime();              //*** Return kill time 

    int getrem_time();

    void peekIor();
    void peekIod();
    bool operator>(process p1);
    void dequeueIOlist_Set();
    void enqueIOlist(int ior, int iod);
    void setID(int ID);
    void setTerminationTime(int t);
    void setCT(int CT);
    void setAT(int AT);
    void setNUM(int N);
    void setIOR(int IOR);
    void setIOD(int IOD);
    void setexc_time(int et);
    void setrem_time(int rt);
    void setTurnAround(int TA);
    void setEarlestDeadline(int eardead);
    void setStatus(int state);// NEW, RDY, RUN, BLK, TRM, ORPH;

    // -------------------- Print and Save Functions ------------------------------------------------------//
    void print();
    void save(ofstream& file); // to save all information on output file

    //-----------------------------------------------------------------------FORKING----------------------------------------------------------------------------------------//
    
    //Setters
    void setLeft(Node<process>* child);             //*** Set the Left child of a forked process
    void setRight(Node<process>* child);            //*** Set the Right child of a forked process
    //Getters
    Node<process>* getLeft() const;                  //*** Get the Left child of a forked process
    Node<process>* getRight() const;                 //*** Get the Right child of a forked process
    process& operator=(const process& p);// Assignment operator for process
    friend ostream& operator<<(ostream&, const process&);
    bool operator<(process p1);
    bool operator<=(process p1);
    bool operator>=(process p1);

};

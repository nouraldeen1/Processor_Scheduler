#pragma once
#pragma once
#include<iostream>
using namespace std;
#include"Queue.h"
#include "PriorityQueue.h"
#include "process.h"
//----------------------------------------This header file includes all possible states of the processor--------------------------------------------------

class Scheduler;   //*** forward declaration

enum cpuState
{
    IDLE,				//The processor is currently in idle state
    BUSY,				//The processor is currently in busy state 
};


class processor
{
protected:
    int busy_t;    //busy_time;
    int IDLE_t;
    bool is_busy=false;
    int estimatedTimeNeeded=0;     //estimate_finish_time;
    int executedTime = 0;
    int pLoad=0;
    int pUtil=0;
    int time_slice;
    int Sumbusy_t;
    int SumIDLE_t;
    Queue<process>* Blocked_Processes;
    Queue<process>* Terminated_Processes;
    Scheduler *pSched;     //***
    bool blockflag = false;
    bool terminateflag = false;
    process lastblocked ;
    process lastterminated;
    cpuState cpu_state;

public:
    //constructor
    processor(Queue<process>* Blocked_Processes, Queue<process>* Terminated_Processes, Scheduler* sched);
    //block and termenating functions
    bool block_Terminate_ifneeded(process* runningProcess,int time);
    bool Is_Busy();
    //setter and getter
    float getpUTIL();
    int getpLOAD();

    void decreaseEstimatedTime(int num);
    process updateTerminated();
    process updateBlocked();
    bool isblocked();
    bool isterminated();
    int getEstimatedFinishTime();
    void increaseEstimatedTime(int num);
    //to be viewed
    virtual bool RDY_Q_IsEmpty();
    int p_load();
    int p_util();
    virtual void scheduleAlgo(int current_time)=0;
    virtual void PrintReadyState()=0;
    virtual void PrintRunState()=0;
    virtual process *terminateprocess()=0;
    int getsumbusy_t();
    int getestimatedTimeNeeded();
    
    void setis_busy(bool x);
};

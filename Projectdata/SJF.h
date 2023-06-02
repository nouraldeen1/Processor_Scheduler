#pragma once
#include"processor.h"
class SJF :public processor
{
private:
    //should be changed to priority queue
    Queue<process>* readyList;
    int estimatedTimeNeeded;
public:
    SJF(Queue<process>* blocked_Processes,Queue<process>* terminated_Processes);
    void scheduleAlgo(int time);
    void PrintReadyState();
    int getEstimatedFinishTime();
    Queue<process>* getreadyList();
    void PrintRunState();
    process* terminateprocess() ;
    bool RDY_Q_IsEmpty();
    void increaseEstimatedTime(int num);
};


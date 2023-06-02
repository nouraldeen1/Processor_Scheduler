#pragma once
#include"processor.h"
#include"Scheduler.h"
class Scheduler;
class RR :public processor
{
private:
    Queue<process>* readyList;
    bool changeprocess;
    int currentReduction;
    int TC;
    
public:
    RR(Queue<process>* blocked_Processes, Queue<process>* terminated_Processes,int RTF);
    int getEstimatedFinishTime();
    void scheduleAlgo(int time_slice);
    Queue<process>* getreadyList();
    void PrintRunState();
    void PrintReadyState();
    process* terminateprocess();
    bool RDY_Q_IsEmpty();
    void increaseEstimatedTime(int num);
    void CheckMigrationRTF(Scheduler* psch);// this function to check if process can migrate the procedures of migration will be executed 
    bool AnyMigrateNeededRTF(Scheduler* pSch); // to check if running process in processor can migrate or not

};


#pragma once
#include"processor.h"
#include"GenericLinkedList.h"
#include"Scheduler.h"
class Scheduler;
#include"LinkedList.h"
#include "PairedQueue.h"
#include "Scheduler.h"

class FCFS : public processor
{
private:
	LinkedList<process>* readyList;
	static PairedQueue<int> KILLSIG_List;				//***  A queue of the Killsignals (KT, PID)
	static int fcfsNum;									//*** Total number of FCFS cpus
	int fcfsId;											//*** Unique id for each cpu
public:

	FCFS(Queue<process>* blocked_Processes,Queue<process>* terminated_Processes);
	void increaseEstimatedTime(int num);
	void scheduleAlgo(int time_slice);
	int getEstimatedFinishTime();
	void PrintReadyState();
	LinkedList<process>* getreadyList();
	process* terminateprocess();
	void PrintRunState();
	bool RDY_Q_IsEmpty();

	//----------------------------------------------------------------------------KILLING-----------------------------------------------------------------------------------------//
	void check_KILL();											//*** Checks to see if a process should be killed after each timestep
	static void addKILLSIG(int killTime, int processID);		//*** Adds a KILLSIG to KILLSIG_List
	int getFcfsId() const;										//*** Return the id of the current FCFS processor		
	void deqKillSig();											//*** Dequeues a signal from the Kill Signals List 

	void CheckMigrationMaxW(Scheduler* psch);// this function to check if process can migrate the procedures of migration will be executed 
	bool AnyMigrateNeededMaxW(Scheduler* pSch); // to check if running process in processor can migrate or not

};




#include "RR.h"

RR::RR(Queue<process>* blocked_Processes,Queue<process>* terminated_Processes, int TC) :processor(Blocked_Processes, Terminated_Processes, pSched) {
	currentReduction = 0;
	changeprocess = false;
	bool changeprocess=false;
	int currentReduction=0;

	readyList = new Queue<process>();
	estimatedTimeNeeded = 0;
	TC = TC;

}
int RR::getEstimatedFinishTime()
{
	return estimatedTimeNeeded;
}
void RR::scheduleAlgo(int time_slice)
{
	process* temp = new process();
	//geting the running process data;
	if (readyList == nullptr) {
		return;
	}
	if (estimatedTimeNeeded == 0) {
		while (readyList != nullptr) {
			readyList->dequeue(*temp);
			return;
		}
		return;

	}


	process* runningProcess = &readyList->peak();
	
	int runProcess_EXCTime = runningProcess->getexc_time();
	int runProcess_IO_R = runningProcess->getIOR();
	


	if (block_Terminate_ifneeded(runningProcess, time_slice) == true) {
		readyList->dequeue(*runningProcess);
		return;
	}
	estimatedTimeNeeded--;
	executedTime++;
	currentReduction++;
	runningProcess->setIOR(runProcess_IO_R);
	runningProcess->setexc_time(++runProcess_EXCTime);
	int runProcess_RemainingTime = runningProcess->getrem_time();
	runningProcess->setrem_time(--runProcess_RemainingTime);
	if (currentReduction == TC) {
		currentReduction = 0;
		readyList->dequeue(*runningProcess);
		readyList->enqueue(*runningProcess);
	}
	//check if estimated time==0
	if (estimatedTimeNeeded == 0)
	{
		is_busy = false;
		return;
	}
	else
		is_busy = true;
	
}
void RR::PrintReadyState()
{
	cout << "[RR]: " << readyList->getCount() << " RDY: ";
	readyList->display();
	cout << endl;
}

void RR::PrintRunState()
{
	if(readyList->isEmpty() == false)
	cout << readyList->peak();

}

Queue<process>* RR::getreadyList()
{
	return readyList;
}
process* RR::terminateprocess()
{
	process* processToTerminated = new process();
	readyList->dequeue(*processToTerminated);
	return processToTerminated;
}
bool RR::RDY_Q_IsEmpty()
{
	return readyList->isEmpty();

}

void RR::increaseEstimatedTime(int num)
{
	estimatedTimeNeeded += num;
}


void RR::CheckMigrationRTF(Scheduler* psch)
{

	while (AnyMigrateNeededRTF(psch))// while loop if we have more than one process that can migrate in the same time step
	{
		process Mp = (readyList->peak());
		if (psch->MigrationRTF(Mp)) // condition to check if migration is done or not
		{
			readyList->dequeue(Mp);// exit this process from ready list and automatically the next process will be in run state
		}
	}

}

bool RR::AnyMigrateNeededRTF(Scheduler* pSch) // to check if running process in processor can migrate or not
{

	if (cpu_state == IDLE && (pSch->CheckRTF(readyList->peak()))) // check processor execute on process and RTF condition
		return false;
	else
		return true;

}

#include<iostream>
#include"processor.h"
#include"process.h"

using namespace std;


processor::processor( Queue<process>* blocked_Processes,
	Queue<process>* terminated_Processes, Scheduler* sched)
{
	Blocked_Processes = blocked_Processes;
	Terminated_Processes = terminated_Processes;
	busy_t = false;
	pLoad = 0;
	pUtil = 0;
	pSched = sched;
	IDLE_t = 0;
	busy_t = 0;
}

bool processor::block_Terminate_ifneeded(process* runningProcess,int time)
{
	//geting the running process data;
	//input or output requested so remove from ready list and call blocked function in scheduler algo

	int runProcess_RemainingTime = runningProcess->getrem_time();
	int runProcess_EXCTime = runningProcess->getexc_time();
	runningProcess->peekIor();
	runningProcess->peekIod();

	int runProcess_IO_R = runningProcess->getIOR();
	//block
	if (runProcess_IO_R == runProcess_EXCTime) {

		estimatedTimeNeeded-=runProcess_RemainingTime;

		runningProcess->setStatus(3);
		runningProcess->setexc_time(++runProcess_EXCTime);
		runningProcess->setexc_time(--runProcess_RemainingTime);
		if (Blocked_Processes == nullptr)
			Blocked_Processes = new Queue<process>();
		Blocked_Processes->enqueue(*runningProcess);
		blockflag = true;
		return true;
		//terminate
	}else if (runProcess_RemainingTime == 1) {
		runProcess_EXCTime++;
		estimatedTimeNeeded--;
		terminateflag = true;
		runningProcess->setStatus(4);
		runningProcess->setrem_time(time);
		runningProcess->setexc_time(++runProcess_EXCTime);
		runningProcess->setexc_time(--runProcess_RemainingTime);
		runningProcess->setTerminationTime(time);
		runningProcess->setTurnAround(time - runningProcess->getAT());
		if (Terminated_Processes == nullptr)
			Terminated_Processes = new Queue<process>();
		Terminated_Processes->enqueue(*runningProcess);
		return true;
	}
	return false;
}

bool processor::Is_Busy()
{
	return is_busy;
}
bool processor::isterminated()
{
	return terminateflag;
}

bool processor::isblocked()
{
	return blockflag;
}



float processor::getpUTIL()
{
	return (Sumbusy_t / (Sumbusy_t + SumIDLE_t)) * 100;
}


int processor::getsumbusy_t()
{
	return Sumbusy_t;
}

process processor::updateTerminated()
{
	if (terminateflag == true) {
		terminateflag = false;
		
		Terminated_Processes->dequeue(lastterminated);
		return lastterminated;
	}
}
process processor::updateBlocked()
{
	if (blockflag == true) {
		blockflag= false;

		Blocked_Processes->dequeue(lastblocked);
		return lastblocked;
	}
}

int processor::getestimatedTimeNeeded()
{
	return estimatedTimeNeeded;

}

void processor::PrintRunState()// base class
{
	cout << "processRunning";
}
int processor::getEstimatedFinishTime()
{
	return estimatedTimeNeeded;
}


void  processor::increaseEstimatedTime(int num)
{
	estimatedTimeNeeded += num;
}

void processor::decreaseEstimatedTime(int num)
{
	estimatedTimeNeeded -= num;
}

bool processor::RDY_Q_IsEmpty()
{
	return false;
}
void processor::setis_busy(bool x) {
	return ;
}

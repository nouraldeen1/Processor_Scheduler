#include "SJF.h"

SJF::SJF(Queue<process>* blocked_Processes,
	Queue<process>* terminated_Processes) :processor(Blocked_Processes, Terminated_Processes, pSched) {
	readyList = new Queue<process>();
	estimatedTimeNeeded = 0;

}
/*void SJF::scheduleAlgo(int current_time)
{
	if(estimatedTimeNeeded>0)
		estimatedTimeNeeded--;
}*/
void SJF::PrintReadyState()
{
	cout << "[SJF]: " << readyList->getCount() << " RDY: ";
	readyList->display();
	cout << endl;
}

void SJF::PrintRunState()
{
	if(readyList->isEmpty()==false)
	cout << readyList->peak();
}

int SJF::getEstimatedFinishTime()
{
	return estimatedTimeNeeded;
}
Queue<process>* SJF::getreadyList()
{
	return readyList;
}
process* SJF::terminateprocess()
{
	process* processToTerminated = new process();
	processToTerminated = &readyList->peak();
	readyList->dequeue(*processToTerminated);
	return processToTerminated;
}
bool SJF::RDY_Q_IsEmpty()
{
	return readyList->isEmpty();

}

void SJF::increaseEstimatedTime(int num)
{
	estimatedTimeNeeded += num;
}

void SJF::scheduleAlgo(int time) {
	process* temp = new process();

	if (estimatedTimeNeeded == 0) {
		is_busy = false;
		return;
	}
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
	process* waitingprocess = &readyList->peak();
	if (waitingprocess == nullptr) {
		return;
	}
	if (readyList->isEmpty() == true)
		return;

	int ExTwaitpro = waitingprocess->getexc_time();
	int RemTwaitpro = waitingprocess->getrem_time();
	int IorTwaitpro = waitingprocess->getIOR();
	if (block_Terminate_ifneeded(waitingprocess, time_slice) == true)
	{
		readyList->dequeue(*waitingprocess);
		return;
	}
	estimatedTimeNeeded--;
	executedTime++;
	waitingprocess->setIOR(IorTwaitpro);
	waitingprocess->setexc_time(++ExTwaitpro);
	waitingprocess->setrem_time(--RemTwaitpro);
	--estimatedTimeNeeded;
	executedTime++;


	waitingprocess->setIOR(IorTwaitpro);

	//check if estimated time==0
	if (estimatedTimeNeeded == 0)
	{
		is_busy = false;
		return;
	}
	else
		is_busy = true;
}
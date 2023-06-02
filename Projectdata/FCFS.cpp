#include "FCFS.h"
#include "process.h"

int FCFS::fcfsNum = 0;		//*** Initialise the number by 0 (it increases to 1 upon first construction)

FCFS::FCFS(Queue<process>* blocked_Processes,
	Queue<process>* terminated_Processes) :processor(Blocked_Processes, Terminated_Processes, pSched)
{
	readyList = new LinkedList<process>();
	estimatedTimeNeeded = 0;
	fcfsNum++;				//*** Increase the number by 1
	fcfsId = fcfsNum-1;		//*** fcfsId for first FCFS is 0
}
/*void FCFS::scheduleAlgo(int current_time)
{
	/*
	if (busy_t == true) {
		int exc = Queue_Ready_list->peak().getexc_time();
		int cpu = Queue_Ready_list->peak().getCT();
		int remaining = cpu - exc;

		if (remaining == 1)
		{
			busy_t = false; //ideal;
		}
		Queue_Ready_list->peak().setrem_time(--remaining);
		Queue_Ready_list->peak().setexc_time(++exc);

	}
	else {
		//termination
		process movedProcess;
		Queue_Ready_list->dequeue(movedProcess);
		Terminated_Processes->enqueue(movedProcess);
	}

	

	if (estimatedTimeNeeded > 0)
		estimatedTimeNeeded--;
}*/

int FCFS::getEstimatedFinishTime()
{
	return estimatedTimeNeeded;
}
void FCFS::PrintReadyState()
{
	cout << "[FCFS]: " << readyList->count() << " RDY: ";
	readyList->displayList();
	cout << endl;
}

void FCFS::PrintRunState()
{
	if (readyList->isEmpty() == false)
	cout << readyList->getHead();
}
LinkedList<process>* FCFS::getreadyList()
{
	return readyList;
}
process* FCFS::terminateprocess()
{
	process* processToTerminated = new process();
	readyList->removeHead(*processToTerminated);
	return processToTerminated;
}
bool FCFS::RDY_Q_IsEmpty()
{
	return readyList->isEmpty();

}
void  FCFS::increaseEstimatedTime(int num)
{
	estimatedTimeNeeded += num;
}
void FCFS::scheduleAlgo(int time_slice) {
	 
	process* temp = new process();

	//check if estimated time==0
	if (estimatedTimeNeeded == 0)
	{
		is_busy = false;
		return;
	}
	if (readyList == nullptr) {
		return;
	}
	if (estimatedTimeNeeded == 0) {
		while (readyList != nullptr) {
			readyList->removeHead(*temp);
			return;
		}
		return;

	}

	process* runningProcess = &readyList->getHead();
	int runprocessExe = runningProcess->getexc_time();
	int runprocessRem = runningProcess->getrem_time();
	int runprocessIor = runningProcess->getIOR();
	if(pSched!=nullptr)
		pSched->forkProcess(readyList->getHeadPTR());				//***

	if (block_Terminate_ifneeded(  runningProcess, time_slice) == true)
	{
		readyList->removeHead(*runningProcess);

		return;
	}
	estimatedTimeNeeded--;
	executedTime++;
	runningProcess->setrem_time(--runprocessRem);
	runningProcess->setexc_time(++runprocessExe);

	runningProcess->setIOR(runprocessIor);

	//check if estimated time==0
	if (estimatedTimeNeeded == 0)
	{
		readyList= new LinkedList<process>();
		is_busy = false;
		return;
	}
	else
		is_busy = true;


}

//***

int FCFS::getFcfsId() const
{
	return fcfsId;
}

//----------------------------------------------------------------------------KILLING-----------------------------------------------------------------------------------------//

void FCFS::check_KILL()
{
	// Check KILLlist to see whether a process should be killed
	// If current time == KILLSIG_List.peek()->getKillTime();
	// Dequeue and call sched to terminate the process and remove it from FCFS

	while (!KILLSIG_List.isEmpty() && KILLSIG_List.peak().FirstItem == pSched->getSimulationTime())
	{
		Node<process>* temp = readyList->getHeadPTR();
		//check if the process is present in the processor
		while (temp)					
		{
			if (temp->getItem().getID() == KILLSIG_List.peak().SecondItem)
			{
				//Sends the FCFS ID and the address of the process to be killed 
				pSched->killPrcs(fcfsId, temp);
			}
			//Moves to the next node
			temp = temp->getNext();		
		}
	}
}


PairedQueue<int> FCFS::KILLSIG_List;
void FCFS::addKILLSIG(int killTime, int processID)
{
	//Enqueue a signal to KILLSIG_List
	KILLSIG_List.enqueue(killTime, processID);
}



void FCFS::CheckMigrationMaxW(Scheduler* psch)
{

	while (AnyMigrateNeededMaxW(psch))// while loop if we have more than one process that can migrate in the same time step
	{
		process Mp = (readyList->getHead());
		if (psch->MigrationMaxW(Mp)) // condition to check if migration is done or not
		{
			readyList->removeHead(Mp);// exit this process from ready list and automatically the next process will be in run state
		}
	}

}

void FCFS::deqKillSig()
{
	//Dequeue from kill
	KILLSIG_List.dequeueMod();
}
bool FCFS::AnyMigrateNeededMaxW(Scheduler* pSch) // to check if running process in processor can migrate or not
{

	if (cpu_state == IDLE && (pSch->CheckMaxW(readyList->getHead()))) // check processor execute on process and RTF condition
		return false;
	else
		return true;

}



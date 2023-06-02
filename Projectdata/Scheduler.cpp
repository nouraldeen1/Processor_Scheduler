#include "Scheduler.h"
#include<fstream>
#include<windows.h>
#include <iostream>
using namespace std;
#include <cstdlib>
#include <random>


void Scheduler::addProcessToReadylist(bool blockedTNewF)
{

	//All_processors_Array[currentprocess % TotalNumOfProcessors].getQueue_Ready_list()->enqueue(moved);

	int min = 10000000;
	int freeProcessorIndex=0;

	//min and index of processesor with shortest ready list
	for (int i = 0;i < FCFSarraysize;i++) {
		if (FCFS_Array[i]->getEstimatedFinishTime() <= min) {
			min = FCFS_Array[i]->getEstimatedFinishTime();
			freeProcessorIndex = i;
		}

	}

	for (int i = 0;i < SJFarraysize;i++) {
		if (SJF_Array[i]->getEstimatedFinishTime() <= min) {
			min = SJF_Array[i]->getEstimatedFinishTime();
			freeProcessorIndex = i + FCFSarraysize;

		}
	}
	for (int i = 0;i < RRarraysize;i++) {
		if (RR_Array[i]->getEstimatedFinishTime() <= min) {
			min = RR_Array[i]->getEstimatedFinishTime();
			freeProcessorIndex = i + FCFSarraysize+ SJFarraysize;
		}

	}

	process moved;
	if (blockedTNewF) {
		moved=Blocked_Processes->peak();
		Blocked_Processes->dequeue(moved);
		moved.setrem_time(moved.getrem_time() - 1);

	}else
		new_Processes->dequeue(moved);


	moved.setStatus(1);

	if (freeProcessorIndex >= 0 && freeProcessorIndex < FCFSarraysize) {
		FCFS_Array[freeProcessorIndex]->getreadyList()->insertFirst(moved);// First FCFS Processors
		FCFS_Array[freeProcessorIndex]->increaseEstimatedTime(moved.getrem_time());
		FCFS_Array[freeProcessorIndex]->setis_busy(true);

	}
	else if (freeProcessorIndex >= FCFSarraysize && freeProcessorIndex <= (FCFSarraysize + SJFarraysize - 1)) {
		SJF_Array[(freeProcessorIndex  - FCFSarraysize)]->getreadyList()->enqueueArranged(moved);// Second SJF processors
		SJF_Array[freeProcessorIndex - FCFSarraysize]->increaseEstimatedTime(moved.getrem_time());
		SJF_Array[(freeProcessorIndex - FCFSarraysize)]->setis_busy(true) ;
	}
	else {
		RR_Array[freeProcessorIndex - FCFSarraysize - SJFarraysize]->getreadyList()->enqueue(moved);// Third RR Processors
		RR_Array[freeProcessorIndex - FCFSarraysize - SJFarraysize ]->increaseEstimatedTime(moved.getrem_time());
		RR_Array[freeProcessorIndex - FCFSarraysize - SJFarraysize]->setis_busy(true);

	}




	/*
	int state = 0;// min number 0=FCFS,1=RR,2=EDF,3=SJF
	int min = lastAddedFCFS;
	if(lastAddedRR<min){
		min = lastAddedRR;
		state = 1;
	}if (lastAddedEDF < min) {
		min = lastAddedEDF;
		state = 2;
	}if (lastAddedSJF < min) {
		min = lastAddedSJF;
		state = 3;
	}
	switch (state) {
	case 0:
		//calculate processor turn
		FCFS_Array
	}
	*/



}
Scheduler::Scheduler(UI* pui)
{
	pUI = pui;
	simpleSimulator();
	simulationtime = 0;
	doneKill = 0;
	doneFork = 0;
	FinalNumOfProcesses = 0; 
	SumWT = 0; 
	SumRT = 0; 
	SumTRT = 0;
	MigPRTF = 0; 
	MigPMaxW = 0;
	StealedP = 0;
	ForkedProcesses = 0;
	KilledProcesses = 0;
	TotalUtilization = 0.0;
}

void Scheduler::BlockedProcessing()
{

	process* blocked=new process();
	if(Blocked_Processes!=nullptr)
		blocked = &Blocked_Processes->peak();
	if (blocked->getIOD()-1 == 0) {
		blocked->dequeueIOlist_Set();
		addProcessToReadylist(true);
		
	}
	else {
		blocked->setIOD(blocked->getIOD() - 1);
	}
}



void Scheduler::FileLoadingFunction()
{
	ifstream InputFile;
	InputFile.open("InputFile.txt", ios::in); // Open the existing file to load the information
	if (InputFile.is_open())
	{
		// Read the information
		cout << "fileFound" << endl;
		ReadProccessors(InputFile);
		new_Processes = new Queue <process>();
		ReadProccess(InputFile);
		ReadKillSignals(InputFile);

		InputFile.close();// Close the file after reading it
	}
	else
		cout << "The file is not found try again" << endl;
}
void Scheduler::simpleSimulator()
{
	//initializing last added processor position in the list
	/*lastAddedFCFS = 0;
	lastAddedRR=0;
	lastAddedSJF=0;
	lastAddedEDF=0;
	*/
	Blocked_Processes=new Queue<process>();

	Terminated_Processes = new Queue<process>();
	currentprocess = 0;
	process* dummyprocess = new process();
	bool ProgramState = true;// To demonstrate if program is on (1) or off (0)

	FileLoadingFunction();
	int simulationtime = 0;
	pUI->RecieveChosenMode();

	while (Terminated_Processes->getCount() != NumOfProcess &&simulationtime<200) {

		//-------------------------------new processes----------------------------------------------//

		//check for newly arrived process
		if (new_Processes->isEmpty()==false) {
			while (simulationtime == new_Processes->peak().getAT()) {
				addProcessToReadylist(false);
				currentprocess++;
				if (new_Processes->isEmpty() == true)
					break;

			}
		}
		
		/*
		* phase 1
		* //move from new to ready
		srand((unsigned)time(NULL));
		for (int i = 0; i < TotalNumOfProcessors; i++) {

			All_processors_Array[i].scheduleAlo(simulationtime);
			if (All_processors_Array[i].getQueue_Ready_list().isEmpty() != true) {
				int ior = All_processors_Array[i].getQueue_Ready_list().peak().getIOR();
				if (simulationtime == ior) {
					process movedprocess;
					All_processors_Array[i].getQueue_Ready_list().dequeue(movedprocess);
					Blocked_Processes->enqueue(movedprocess);
				}
				else {
					process movedprocess;
					random_num = rand() % 100 + 1;
					if (random_num <= 15) {
						All_processors_Array[i].getQueue_Ready_list().dequeue(movedprocess);
						Blocked_Processes->enqueue(movedprocess);
					}
					else if (random_num <= 30) {
						All_processors_Array[i].getQueue_Ready_list().dequeue(movedprocess);
						All_processors_Array[i].getQueue_Ready_list().enqueue(movedprocess);
					}
					else if (50 <= random_num && random_num <= 60) {
						All_processors_Array[i].getQueue_Ready_list().dequeue(movedprocess);
						Terminated_Processes->enqueue(movedprocess);
					}
				}
			}
			
		}
		srand((unsigned)time(NULL));
		random_num = rand() % 100 + 1;
		process movedprocess;
		if (random_num <= 10) {
			Blocked_Processes->dequeue(movedprocess);
			All_processors_Array[currentprocess % TotalNumOfProcessors].getQueue_Ready_list().enqueue(movedprocess);
			currentprocess++;
		}
		*/
		/*
		srand((unsigned)time(NULL));
		random_num = rand() % 100 + 1;
		for (int i = 0; i < FCFSarraysize; i++) {
			process* pointer = new process();
			pointer = &All_processors_Array[i].getQueue_Ready_list()->peak();
			for (int j = 0; j < All_processors_Array[i].getQueue_Ready_list()->getCount(); j++) {

				if (random_num == pointer->getID()) {
					Terminated_Processes->enqueue(*pointer);
					delete pointer;
				}
				pointer++;

			}
		}
		*/
		//-------------------------------scheduleAlgo----------------------------------------------//
		//values for work stealing and loops for schedule algo
		int min = 999999, max = -1,minIndex = 0,maxIndex = 0,minType = 0,maxType = 0;
		//type fcfs=1 sjf=2 rr=3

		for (int i = 0;i < FCFSarraysize;i++) {
			FCFS_Array[i]->scheduleAlgo(simulationtime);
			if (FCFS_Array[i]->isblocked())
				Blocked_Processes->enqueue(FCFS_Array[i]->updateBlocked());
			if (FCFS_Array[i]->isterminated())
				Terminated_Processes->enqueue(FCFS_Array[i]->updateTerminated());
			if (FCFS_Array[i]->getEstimatedFinishTime() <= min) {
				min=FCFS_Array[i]->getEstimatedFinishTime();
				minIndex = i;
				minType = 1;
			}
				

			if (FCFS_Array[i]->getEstimatedFinishTime() >= max) {
				max = FCFS_Array[i]->getEstimatedFinishTime();
				maxIndex = i;
				maxType = 1;
			}
		}
	
		for (int i = 0;i < SJFarraysize;i++) {
			SJF_Array[i]->scheduleAlgo(simulationtime);
			if (SJF_Array[i]->isblocked())
			Blocked_Processes->enqueue(SJF_Array[i]->updateBlocked());
			if (SJF_Array[i]->isterminated())
			Terminated_Processes->enqueue(SJF_Array[i]->updateTerminated());
			if (SJF_Array[i]->getEstimatedFinishTime() <= min) {
				min = SJF_Array[i]->getEstimatedFinishTime();
				minIndex = i;
				minType = 2;

			}
			if (SJF_Array[i]->getEstimatedFinishTime() >= max) {
				max = SJF_Array[i]->getEstimatedFinishTime();
\
				maxIndex = i;
				maxType = 2;
			}
		}
		for (int i = 0;i < RRarraysize;i++) {
			RR_Array[i]->scheduleAlgo(simulationtime);
			if (RR_Array[i]->isblocked())
			Blocked_Processes->enqueue(RR_Array[i]->updateBlocked());
			if (RR_Array[i]->isterminated())
			Terminated_Processes->enqueue(RR_Array[i]->updateTerminated());
			if (RR_Array[i]->getEstimatedFinishTime() <= min) {
				min = FCFS_Array[i]->getEstimatedFinishTime();
				minIndex = i;
				minType = 3;

			}
			if (RR_Array[i]->getEstimatedFinishTime() >= max){
				max = RR_Array[i]->getEstimatedFinishTime();
				maxIndex = i;
				maxType = 3;
			}
		}

		if (Blocked_Processes->isEmpty() == false) {
			BlockedProcessing();
		}


		//-------------------------------work stealing----------------------------------------------//
		int i = 0;
		while (simulationtime % STL ==0&&max>0&&simulationtime!=0&& max>=0&&(max - min) / max>0.4&&i<1) {
			process* temp = new process();
			process* move = new process();
			switch (maxType)
			{
			case 1:
				*move = FCFS_Array[maxIndex]->getreadyList()->getHead();
				FCFS_Array[maxIndex]->getreadyList()->removeHead(*temp);
				FCFS_Array[maxIndex]->decreaseEstimatedTime(move->getrem_time());
				break;
			case 2:
				if(SJF_Array[maxIndex]->getreadyList()!=nullptr&& SJF_Array[maxIndex]->getreadyList()->isEmpty()==false)
				SJF_Array[maxIndex]->getreadyList()->dequeue(*move);
				SJF_Array[maxIndex]->decreaseEstimatedTime(move->getrem_time());
				break;
			case 3:
				*move = RR_Array[maxIndex]->getreadyList()->peak();
				RR_Array[maxIndex]->getreadyList()->dequeue(*temp);;
				RR_Array[maxIndex]->decreaseEstimatedTime(move->getrem_time());

				break;
			default:
				break;
			}
			min += move->getrem_time();
			switch (minType)
			{
			case 1:
				if (FCFS_Array[maxIndex]->getreadyList() == nullptr || FCFS_Array[maxIndex]->getreadyList()->isEmpty() == true)
					break;
					FCFS_Array[minIndex]->getreadyList()->insertLast(*move);
					FCFS_Array[minIndex]->getreadyList()->insertFirst(*move);
				FCFS_Array[minIndex]->increaseEstimatedTime(move->getrem_time());

				break;
			case 2:
				if (SJF_Array[maxIndex]->getreadyList() == nullptr || SJF_Array[maxIndex]->getreadyList()->isEmpty() == true)
					break;
				*move = SJF_Array[minIndex]->getreadyList()->peak();
				SJF_Array[minIndex]->getreadyList()->enqueueArranged(*move);
				SJF_Array[minIndex]->increaseEstimatedTime(move->getrem_time());


				break;
			case 3:
				if (RR_Array[minIndex]->getreadyList() == nullptr || RR_Array[minIndex]->getreadyList()->isEmpty() == true)
					break;
				*move = RR_Array[minIndex]->getreadyList()->peak();
				RR_Array[minIndex]->getreadyList()->enqueue(*move);
				RR_Array[minIndex]->increaseEstimatedTime(move->getrem_time());
				break;
			default:
				break;
			}
			max -= move->getrem_time();
			i++;

		}

		//next time step
		pUI->ActivateProgramMode(simulationtime, ProgramState, FCFS_Array, FCFSarraysize, SJF_Array, SJFarraysize, RR_Array, RRarraysize, Blocked_Processes, Terminated_Processes);
		simulationtime++;
	}
	ProgramState = false;
	pUI->ActivateProgramMode(simulationtime, ProgramState, FCFS_Array, FCFSarraysize, SJF_Array, SJFarraysize, RR_Array, RRarraysize, Blocked_Processes, Terminated_Processes);

	OutputFormat();

}
//----------------------------------------- Read Input Functions ---------------------------------------//
void Scheduler::ReadProccessors(ifstream& file)
{

	// EDFarraysize;
	file >> FCFSarraysize >> SJFarraysize >> RRarraysize;// Read number of each type processors 
	TotalNumOfProcessors = SJFarraysize + RRarraysize + FCFSarraysize;
	//initializing processors' Array with processors
	SJF_Array = new SJF*[SJFarraysize];
	RR_Array = new RR*[RRarraysize];
	FCFS_Array = new FCFS*[FCFSarraysize];
	file >> TC;// Read Time slice for RR
	file >> RTF >> MaxW >> STL >> ForkProb; // Read the following: Remaining Time Finish, Max Waiting, Stealing time , Fork Probability


	int fcfsCurrent = 0, sjfCurrent = 0, rrCurrent = 0;
	for (int i = 0; i < TotalNumOfProcessors; i++) // Decleration the processors in list of processors
	{
		if (i >= 0 && i < FCFSarraysize) {
			FCFS_Array[i] = new FCFS(Blocked_Processes,Terminated_Processes);// First FCFS Processors
			fcfsCurrent++;
		}
		else if (i >= FCFSarraysize && i <= (FCFSarraysize + SJFarraysize - 1)) {
			SJF_Array[(i - FCFSarraysize)] = new SJF(Blocked_Processes, Terminated_Processes);// Second SJF processors
			sjfCurrent++;

		}
		else {
			RR_Array[i - FCFSarraysize - SJFarraysize] =new RR(Blocked_Processes, Terminated_Processes, TC);// Third RR Processors
			rrCurrent++;

		}
		//All_processors_Array[i] = processor();
	}

	cout << "processors read finished with count " << TotalNumOfProcessors << endl;

}

void Scheduler::ReadProccess(ifstream& file)
{
	NumOfProcess = 0;
	file >> NumOfProcess;
	// In for loop read information of each processors
	for (int i = 0; i < NumOfProcess; i++)
	{

		int AT, PID, CT, N;
		file >> AT >> PID >> CT >> N; // Read the following: Arrival Time, Process ID, CPU Time, Number of time the process request I/O
		

		process* newProcess = new process(AT, PID, CT, N); // Decleration process that store this data
		if (N > 0)
		{
			
			for (int j = 0; j < N ; j++) // If Number of time the process request I/O greater than zero Read the following
			{
				int IO_R, IO_D; char c;

				if (j == 0)
					file >> c >> IO_R >> c >> IO_D >> c;// I/O Request time, I/O Duration
				else
					file >>c>> c >> IO_R >> c >> IO_D >> c ;// I/O Request time, I/O Duration
				// Add this pair to I/O list
				newProcess->enqueIOlist(IO_R, IO_D);
			}
		
		}
		new_Processes->enqueue(*newProcess);
	}
	cout << "processes read finished with count " << new_Processes->getCount() << endl;

}

//***
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void Scheduler::addTrmList(process prcs)
{
	prcs.setStatus(5);								//TRM State
	Terminated_Processes->enqueue(prcs);			//Move process to the Terminated list
}

void Scheduler::incPrcsCount()
{
	//Increase number of processes by 1
	NumOfProcess++;
}

int Scheduler::getPrcsCount() const
{
	//Gets the number of processes
	return NumOfProcess;
}

void Scheduler::inserLeastFcfs(Node<process>* child)
{
	//Searching for minimum FCFS (according to expected finish time)
	int min = FCFS_Array[0]->getEstimatedFinishTime();
	int index;
	for (int i = 0; i < FCFSarraysize; i++)
	{
		if (FCFS_Array[i]->getEstimatedFinishTime() < min)
		{
			min = FCFS_Array[i]->getEstimatedFinishTime();
			index = i;
		}
	}
	child->getItem().setStatus(2);						//RDY State

	//assign to shortest FCFS
	FCFS_Array[index]->getreadyList()->insertLast(child->getItem());
}

int Scheduler::getSimulationTime() const
{
	//Get the program ellapsed time
	return simulationtime;
}

void Scheduler::incSimulationTime()
{
	//increase simulation time by 1
	simulationtime++;
}

//-----------------------------------------------------------------------KILLING----------------------------------------------------------------------------------------//

void Scheduler::ReadKillSignals(ifstream& file)
{

	int pID, time;
	while (!(file.eof())) // Read signal kills untill reach to the end of file
	{
		file >> pID >> time;// Read the following: process ID, Kill Time
		// then add this signal kill to Signal Kill list 

		FCFS::addKILLSIG(pID, time);
	}

}

void Scheduler::killPrcs(int cpuID, Node<process>* temp)
{
	process removedPrcs;

	//Remove the process with different functions according to its position in the linkedlist

	for (int i = 0; i < FCFSarraysize; i++)
	{
		if (temp == FCFS_Array[cpuID]->getreadyList()->getHeadPTR())
		{
			
			FCFS_Array[cpuID]->getreadyList()->removeHead(removedPrcs);
		}
		else if (temp->getNext())
		{
			removedPrcs = FCFS_Array[cpuID]->getreadyList()->deleteNode(temp);
		}
		else
		{
			removedPrcs = FCFS_Array[cpuID]->getreadyList()->deleteLast();
		}
		removedPrcs.setStatus(5);					//TRM State
		addTrmList(removedPrcs);					//Adds the terminated process to terminated list
		FCFS_Array[cpuID]->deqKillSig();			//Orders the FCFS to dequeue one of its killsignals
		doneKill++;									//Increase the successful killings by 1
	}
}



//-----------------------------------------------------------------------FORKING----------------------------------------------------------------------------------------//

void Scheduler::forkProcess(Node<process>* prcs)
{
	// Random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 100);
	int randNumLeft = dist(gen);
	int randNumRight = dist(gen);

	// Forking if condition is met


	if (randNumLeft >= 0 && randNumLeft <= ForkProb && prcs->getLeft() == nullptr)
	{
		// Creating a new child process
		incPrcsCount();
		incDoneFork();
		Node<process>* child = new Node<process>(process(getSimulationTime(), getPrcsCount(), prcs->getItem().getrem_time(), 0));
		child->getItem().setStatus(1);				//NEW State
		inserLeastFcfs(child);
		prcs->setLeft(child);
	}

	if (randNumRight >= 0 && randNumRight <= ForkProb && prcs->getRight() == nullptr)
	{
		// Creating a new child process
		incPrcsCount();
		incDoneFork();
		Node<process>* child = new Node<process>(process(getSimulationTime(), getPrcsCount(), prcs->getItem().getrem_time(), 0));
		child->getItem().setStatus(1);				//NEW State
		inserLeastFcfs(child);
		prcs->setRight(child);
	}
}

void Scheduler::incDoneFork()
{
	doneFork++;
}

//-----------------------------------------------------------------------KILL ORPH----------------------------------------------------------------------------------------//
void Scheduler::terminateOrphProcess(Node<process>* prcs) 
{
	prcs->getItem().setStatus(6);		//ORPH State
	if (prcs == nullptr) { return;}		//base condition
	if (prcs->getLeft() != nullptr) 
	{
		// Recursively terminate the left child process
		addTrmList(prcs->getLeft()->getItem());
		terminateOrphProcess(prcs->getLeft());
	}
	if (prcs->getRight() != nullptr) 
	{
		// Recursively terminate the right child process
		addTrmList(prcs->getRight()->getItem());
		terminateOrphProcess(prcs->getRight());
	}
	delete prcs;
}


//void Scheduler::terminatePrcs(process* prcs, )
//{
//	block_terminator_ifneeeded
//}


// ---------------------------------- Output Functions ------------------------------------------------------//

void Scheduler::TerminatedProcessesInformation(ofstream& file)
{
	file << "TT   PID   AT  CT  IO_D    WT  RT  TRT" << endl;
	FinalNumOfProcesses = Terminated_Processes->getCount();
	while (!(Terminated_Processes->isEmpty())) // loop on Terminated list until becoming empty
	{
		process p;
		Terminated_Processes->dequeue(p); // extract the process from terminated list
		p.save(file);// save all its infomation
	}

}

void Scheduler::ProcessesStatistics(ofstream& file)
{
	file << "Processes: " << FinalNumOfProcesses << endl;
	file << "Avg WT: " << SumWT / FinalNumOfProcesses << ",    " << "Avg RT: " << SumRT / FinalNumOfProcesses << ",    " << "Avg TRT: " << SumTRT / FinalNumOfProcesses << endl;
	file << "Migration %: " << "     " << "RTF= " << (MigPRTF / FinalNumOfProcesses) * 100 << "%,    " << "MaxW= " << (MigPMaxW / FinalNumOfProcesses) * 100 << "%" << endl;
	file << "Work Steal%: " << (StealedP / FinalNumOfProcesses) * 100 << "%" << endl;
	file << "Forked Process: " << (ForkedProcesses / FinalNumOfProcesses) * 100 << "%" << endl;
	file << "Killed Process: " << (KilledProcesses / FinalNumOfProcesses) * 100 << "%" << endl;
}

void Scheduler::ProcessorsStatistics(ofstream& file)
{
	file << "Processors: " << TotalNumOfProcessors << " [" << FCFSarraysize << " FCFS, " << SJFarraysize << " SJF, " << RRarraysize << " RR]" << endl;
	file << "Processors Load" << endl;
	file << endl;
	file << "Processors Utiliz" << endl;
	file << endl;
	file << "Avg Utilization = " << TotalUtilization / TotalNumOfProcessors << "%" << endl;


}

void Scheduler::OutputFormat()
{
	ofstream OutputFile;
	OutputFile.open("Output_File", ios::out);
	TerminatedProcessesInformation(OutputFile);
	OutputFile << endl;
	ProcessesStatistics(OutputFile);
	OutputFile << endl;
	ProcessorsStatistics(OutputFile);
	OutputFile.close();
}

void Scheduler::SaveProcessorLoad(ofstream& file)
{
	for (int i = 0; i < FCFSarraysize; i++) // loop on FCFS Array
	{
		file << "p" << i + 1 << "=" << (FCFS_Array[i]->getsumbusy_t() / (SumTRT)) * 100; // save the processor load of each FCFS processor
		file << "%  ";
		TotalUtilization += FCFS_Array[i]->getpUTIL();
	}
	for (int i = 0; i < SJFarraysize; i++)// loop on SJF Array
	{
		file << "p" << i + FCFSarraysize + 1 << "=" << ((SJF_Array[i]->getsumbusy_t() / (SumTRT)) * 100); // save the processor load of each SJF processor
		file << "%  ";
		TotalUtilization += SJF_Array[i]->getpUTIL();
	}
	for (int i = 0; i < RRarraysize - 1; i++)// loop on RR Array except the last element
	{
		file << "p" << i + FCFSarraysize + SJFarraysize + 1 << "=" << (RR_Array[i]->getsumbusy_t() / (SumTRT)) * 100 << "%,   "; // save the processor load of each RR processor except the last

	}

	file << "p" << TotalNumOfProcessors << "=" << (RR_Array[RRarraysize - 1]->getsumbusy_t() / (SumTRT)) * 100; // save the processor load of last RR processor

}


void Scheduler::SaveProcessorUtilize(ofstream& file)
{
	for (int i = 0; i < FCFSarraysize; i++) // loop on FCFS Array
	{
		file << "p" << i + 1 << "=" << FCFS_Array[i]->getpUTIL(); // save the processor utilize of each FCFS processor
		file << "%  ";
		TotalUtilization += FCFS_Array[i]->getpUTIL();
	}
	for (int i = 0; i < SJFarraysize; i++)// loop on SJF Array
	{
		file << "p" << i + FCFSarraysize + 1 << "=" << SJF_Array[i]->getpUTIL(); // save the processor utilize of each SJF processor
		file << "%  ";
		TotalUtilization += SJF_Array[i]->getpUTIL();
	}
	for (int i = 0; i < RRarraysize - 1; i++)// loop on RR Array except the last element
	{
		file << "p" << i + FCFSarraysize + SJFarraysize + 1 << "=" << RR_Array[i]->getpUTIL() << "%,   "; // save the processor utilize of each RR processor except the last
		TotalUtilization += RR_Array[i]->getpUTIL();
	}

	file << "p" << TotalNumOfProcessors << "=" << RR_Array[RRarraysize - 1]->getpUTIL(); // save the processor utilize of last RR processor
	TotalUtilization += SJF_Array[RRarraysize - 1]->getpUTIL();
}

bool Scheduler::CheckRTF(process p)
{
	return (p.getCT() < RTF);

}

bool Scheduler::MigrationRTF(process p)
{
	if (SJFarraysize != 0)
	{
		int sch = 1000000; // index of SJF processor that have shortest queue
		int min = 0; // the minimum expexted finish time
		for (int i = 0; i < SJFarraysize; i++)
		{
			if (SJF_Array[i]->getestimatedTimeNeeded() < min)// loop on SJF_Array to get the SJF processor that has shortest queue
			{
				sch = i;
				min = SJF_Array[i]->getestimatedTimeNeeded();
			}
		}
		SJF_Array[sch]->getreadyList()->enqueueArranged(p); // add the migrated process to the RR processor that has shortest queue
		MigPRTF++;
		return true;
	}
	else
		return false; // if we do not have any SJF processors

}


bool Scheduler::CheckMaxW(process p)
{
	return (p.getWT() > MaxW);

}

bool Scheduler::MigrationMaxW(process p)
{
	if (RRarraysize != 0)
	{
		int sch = 0; // index of RR processor that have shortest queue
		int min = 0; // the minimum expexted finish time
		for (int i = 0; i < RRarraysize; i++) // loop on RR_Array to get the RR processor that has shortest queue
		{
			if (RR_Array[i]->getestimatedTimeNeeded() < sch)
			{
				sch = i;
				min = RR_Array[i]->getestimatedTimeNeeded();
			}
		}
		RR_Array[sch]->getreadyList()->enqueue(p); // add the migrated process to the RR processor that has shortest queue
		MigPMaxW++;
		return true;
	}
	else
		return false; // if we do not have any RR processors

}

#pragma once
#include "Node.h"
#include "processor.h"
#include"process.h"
#include"FCFS.h"
#include"SJF.h"
#include"RR.h"
#include"Queue.h"
#include <iostream>
#include "LinkedList.h"
#include"UI.h"
class FCFS;
class RR;
class SJF;
using namespace std;
class FCFS;
class UI;
class Scheduler {
private:
	int TC, RTF, MaxW, STL, ForkProb;
	int NumOfProcess;
	int TotalNumOfProcessors;
	int simulationtime; //*** The Elapsed time (total time) of the program
	int doneFork;		//*** Number of successful forkings
	int doneKill;		//*** Number of successful killings

	int FCFSarraysize;
	int RRarraysize;
	int SJFarraysize;
	int EDFarraysize;

	process* pPrcs;		//*** 

	//processor* All_processors_Array;
	FCFS** FCFS_Array;
	RR** RR_Array;
	SJF** SJF_Array;
	//processor* EDF_Array = new processor[EDFarraysize];

	int currentprocess;
	/*
	int lastAddedFCFS;
	int lastAddedRR;
	int lastAddedSJF;
	int lastAddedEDF;
	*/


	Queue<process>* new_Processes;
	Queue<process>* Blocked_Processes;
	Queue<process>* Terminated_Processes;




	//function for adding a new process to a ready list
	void addProcessToReadylist(bool blocked);
	//function for managing  block queue every time step
	void BlockedProcessing();

	// --------------------------- Interface Modes Data Members and Functions ---------------------------- //
	UI* pUI;

	// ----------------------------- Statistics Data Memebers and Functions ------------------------------ //
	int FinalNumOfProcesses; // The number of terminated processes in the end of program
	int SumWT; // Summation of the waiting time of all terminated processes
	int SumRT; // Summation of the response time of all terminated processes
	int SumTRT; // Summation of the turnaround time of all terminated processes
	int MigPRTF; // Total number of Migrated processes as result of RTF
	int MigPMaxW;// Total number of Migrated processes as result of MaxW
	int StealedP;// Total number of stealed processes 
	int ForkedProcesses;// Total number of forked processes
	int KilledProcesses;// Total number of killed processes
	float getProcessorLoad(processor* p);
	float TotalUtilization;

public:
	Scheduler(UI* pui);

	void FileLoadingFunction();// General function is used for read inputs of the program
	void simpleSimulator();
	void ReadProccessors(ifstream& file);// Funtions that used for read inputs that pertaining to proccessors
	void ReadProccess(ifstream& file);// Funtions that used for read inputs that pertaining to proccesses
	
	//---------------------------------------------- KILLING ----------------------------------------------------//
	
	void ReadKillSignals(ifstream& file);//  Funtions that used for read inputs that pertaining to Killed processes
	void killPrcs(int cpuID, Node<process>* prcsPtr);//***	Recieves the FCFS ID and checks for the process to be killed in the FCFS

	
	// --------------------------- Migration Data Members and Functions -----------------------------------//
	bool CheckRTF(process p);
	bool MigrationRTF(process p);
	bool CheckMaxW(process p);
	bool MigrationMaxW(process p);

	//---------------------------------------------- FORKING ----------------------------------------------------//

	void forkProcess(Node<process>* process);//*** Forking a process function
	void incPrcsCount();//*** Increase the number of processes by 1
	int	getPrcsCount() const;//*** Gets the number of processes
	int getSimulationTime() const;//*** Gets the Simulation elapsed time
	void incSimulationTime();//*** Increase the simulation time by 1
	void incDoneFork();//*** Increases doneFork by 1
	void inserLeastFcfs(Node<process>* child);//*** Inserts the child in the FCFS with the least expected time

	//---------------------------------------------- ORPH KILLING ----------------------------------------------------//
	void terminateOrphProcess(Node<process>* prcs);
	void addTrmList(process prcs);//*** Add a process to TRMlist
	// ---------------------------------- Output Functions ------------------------------------------------------//

	// This functions will be implemented in phase 2
	void TerminatedProcessesInformation(ofstream& file); // write terminated processes information on output file
	void ProcessesStatistics(ofstream& file); // write special statistics for processes on output file
	void ProcessorsStatistics(ofstream& file); // write special statistics for processors on output file
	void OutputFormat(); // General function to write output file and show statistics
	void SaveProcessorLoad(ofstream& file);
	void SaveProcessorUtilize(ofstream& file);

};


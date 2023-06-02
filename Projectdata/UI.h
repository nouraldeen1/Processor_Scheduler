#pragma once
#ifndef UI_H
#define UI_H
#include"processor.h"
#include"Queue.h"
#include<iosfwd>
#include"FCFS.h"
#include"SJF.h"
#include"RR.h"
class RR;
class SJF;
class FCFS;
class UI
{
private:
	int NumofChosenMode;// integer that represented the number that user pressed on it that translated to particular program mode
public:
	UI();
	UI(int s);
	// -------------------- Activate Program Mode Functions ------------------------------------------------------//

	void RecieveChosenMode();// To revieve the mode that user selected
	void ActivateProgramMode(int CurrentTimestep, bool ProgramState, FCFS* arr1[], int size1, SJF* arr2[], int size2, RR* arr3[], int size3, Queue<process>* Q1, Queue<process>* Q2);// General function is used to  activate the appropiate mode
	void DisplayOutput(int CurrentTimestep, FCFS* arr1[], int size1, SJF* arr2[], int size2, RR* arr3[], int size3, Queue<process>* Q1, Queue<process>* Q2); // special function inside ActivateProgramMode function to display all outputs on console for interactive and step by step modes
	void ActivateSilentMode(bool n, int CurrentTimestep);// special function inside ActivateProgramMode function to activate silent mode
	void RDYProcessesInformation(FCFS* arr1[], int size1, SJF* arr2[], int size2, RR* arr3[], int size3);// print Ready state information on console
	void BLKProcessesInformation(Queue<process>* Q1);// print Blocked state information on console
	void RUNProcessesInformation(FCFS* arr1[], int size1, SJF* arr2[], int size2, RR* arr3[], int size3);// print Running state information on console
	void TRMProcessesInformation(Queue<process>* Q2);// print Terminated state information on console


};
#endif



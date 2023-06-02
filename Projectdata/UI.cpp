#include "UI.h"
#include <iostream>
using namespace std;

#include"UI.h"
#include"process.h"
#include<windows.h>
UI::UI()
{
	NumofChosenMode = 0;


}

UI::UI(int s)
{
	NumofChosenMode = s;

}

//----------------------------------------- Activate Program Mode Functions ---------------------------------------//	

void UI::RecieveChosenMode()
{
	cout << "Please press the number of mode that you want to activate:" << endl;
	cout << "1 - Interactive Mode." << endl;
	cout << "2 - Step by step Mode." << endl;
	cout << "3 - Silent Mode." << endl;
	cin >> NumofChosenMode;
}

void UI::ActivateProgramMode(int CurrentTimestep, bool ProgramState, FCFS* arr1[], int size1, SJF* arr2[], int size2, RR* arr3[], int size3, Queue<process>* Q1, Queue<process>* Q2)
{
	switch (NumofChosenMode)
	{
	case 1: // Interactive Mode
		DisplayOutput(CurrentTimestep, arr1, size1, arr2, size2, arr3, size3, Q1, Q2);
		cout << "PRESS ANY KEY TO MOVE TO NEXT STEP! " << endl;
		cin.get(); // wait from user to press any key 
		break;
	case 2: // Step By Step Mode
		DisplayOutput(CurrentTimestep, arr1, size1, arr2, size2, arr3, size3, Q1, Q2);
		Sleep(1000);// Sleep one second (= 1000 milliseconds)
		break;
	case 3: // Silent Mode
		ActivateSilentMode(ProgramState, CurrentTimestep);
		break;
	}
}



void UI::ActivateSilentMode(bool n, int CurrentTimestep)
{
	switch (n)
	{
	case true:
		if (CurrentTimestep == 0)
			cout << "Silent Mode....  Simulation Starts..." << endl;// print the message only at the begianing of program
		break;
	case false:
		cout << "Simulation ends, Output file created" << endl;// print the message only at the ending of program
		break;
	}
}

void UI::DisplayOutput(int CurrentTimestep, FCFS* arr1[], int size1, SJF* arr2[], int size2, RR* arr3[], int size3, Queue<process>* Q1, Queue<process>* Q2)

{
	cout << "Current Timestep: " << CurrentTimestep << endl;// print current timestep
	RDYProcessesInformation(arr1, size1, arr2, size2, arr3, size3);// print Ready state information
	cout << endl;
	BLKProcessesInformation(Q1);// print Blocked state information
	cout << endl;
	RUNProcessesInformation(arr1, size1, arr2, size2, arr3, size3);// print Running state information
	cout << endl;
	TRMProcessesInformation(Q2);// print Terminated state information
	cout << endl;
}


void UI::RDYProcessesInformation(FCFS* arr1[], int size1, SJF* arr2[], int size2, RR* arr3[], int size3)
{
	cout << "------------------- RDY Processes -------------------------" << endl;
	
	for (int i = 0; i < size3; i++) {
		cout << "processor " << 1+i  << " "; // display the correct processor number 
		arr3[i]->PrintReadyState();

	}
	for (int i = 0; i < size2; i++) {
		cout << "processor " << i + size3 +1 << " "; // display the correct processor number 
		arr2[i]->PrintReadyState();

	}
	
	for (int i = 0; i < size1; i++) {
		cout << "processor " << i + size2+ size3+1 << " "; // display the correct processor number 
		arr1[i]->PrintReadyState();// call function print RDY state
	}
}


void UI::BLKProcessesInformation(Queue<process>* Q1)
{
	cout << "------------------- BLK Processes -------------------------" << endl;
	cout << Q1->getCount() << " BLK: ";// call function to get number of elements of the list
	Q1->display();// call function to print elements information of the list
	cout << endl;
}

void UI::RUNProcessesInformation(FCFS* arr1[], int size1, SJF* arr2[], int size2, RR* arr3[], int size3)
{
	cout << "------------------- RUN Processes -------------------------" << endl;
	for (int i = 0; i < size3; i++) {
		if (arr3[i]->Is_Busy())
		{
			arr3[i]->PrintRunState();// call function to get the process that in run state of particular processor
			cout << "(p" << i  + 1 << ")";// display the correct processor number 
			if (i != size3 - 1)
				cout << ", ";
		}
	}
	
	for (int i = 0; i < size2; i++) {
		if (arr2[i]->Is_Busy())
		{
			arr2[i]->PrintRunState();// call function to get the process that in run state of particular processor
			cout << "(p" << i + size3 + 1 << ")";// display the correct processor number 
			if (i != size2 - 1)
				cout << ", ";
		}

	}
	for (int i = 0; i < size1; i++) {
		if (arr1[i]->Is_Busy())
		{
			arr1[i]->PrintRunState();// call function to get the process that in run state of particular processor
			cout << "(p" << i + size3+size2+ 1 << ")";// display the correct processor number 
			if (i != size1 - 1)
				cout << ", ";
		}
	}
	
	cout << endl;
}



void UI::TRMProcessesInformation(Queue<process>* Q2)
{
	cout << "------------------- TRM Processes -------------------------" << endl;
	cout << Q2->getCount() << " TRM: ";// call function to get number of elements of the list  
	Q2->display();// call function to print elements information of the list
	cout << endl;
}


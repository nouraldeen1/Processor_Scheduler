#include "process.h"
#include <fstream>
#include "Node.h"


process::process()
{
}

process::process(int AT, int PID, int CT, int N) :Id(PID)
{
	cpu_time = CT;
	Arr_time = AT;
	N_ps = N;
	status = NEW;
	rem_time = CT;
	exc_time = 0;

}

process::process(const process& p)
{
	cpu_time = p.cpu_time;
	Arr_time = p.Arr_time;
	IO_D = p.IO_D;
	IO_R = p.IO_R;
	N_ps = p.N_ps;
	R_time = p.R_time;
	TR_time = p.TR_time;
	T_time = p.T_time;
	W_time = p.W_time;
	rem_time = p.rem_time;
	exc_time = p.exc_time;
	status = p.status;
	iopairqueue = p.iopairqueue;
	Id = p.Id;
}

process& process::operator=(const process& p)
{
	if (this == &p)
		return *this;
	else
	{
		this->cpu_time = p.cpu_time;
		this->Arr_time = p.Arr_time;
		this->IO_D = p.IO_D;
		this->IO_R = p.IO_R;
		this->N_ps = p.N_ps;
		this->R_time = p.R_time;
		this->TR_time = p.TR_time;
		this->T_time = p.T_time;
		this->W_time = p.W_time;
		this->rem_time = p.rem_time;
		this->exc_time = p.exc_time;
		this->status = p.status;
		this->iopairqueue = p.iopairqueue;
		this->Id = p.Id;
		return *this;
	}
}

int process::getID()
{
	return Id;
}

int process::getCT()
{
	return cpu_time;
}
void process::setTerminationTime(int t)
{
	T_time = t;
}
void process::setCT(int CT)
{
	cpu_time = CT;
}
int process::getAT()
{
	return Arr_time;
}
void process::setAT(int AT)
{
	Arr_time = AT;
}
int process::getTT()
{
	return T_time;
}

int process::getTRT()
{
	return T_time - Arr_time;
}

int process::getRT()
{
	return R_time;
}

int process::getWT()
{
	return T_time - Arr_time - cpu_time;
}

int process::getNUM()
{
	return N_ps;
}
void process::setNUM(int N)
{
	N_ps = N;
}
int process::getIOR()
{
	return IO_R;
}
void process::setIOR(int IOR)
{
	IO_R = IOR;
}
int process::getIOD()
{
	return IO_D;
}
void process::setIOD(int IOD)
{
	IO_D = IOD;
}
void process::setexc_time(int et)
{
	exc_time = et;
}
void process::setrem_time(int rt)
{
	rem_time = rt;
}
void process::setTurnAround(int TA)
{
	TR_time = TA;
}
void process::print()
{
}
void process::setStatus(int state)
{
	switch (state)
	{
	case 0:
		status = NEW;
		break;
	case 1:
		status = RDY;
		break;
	case 2:
		status = RUN;
		break;
	case 3:
		status = BLK;
		break;
	case 4:
		status = TRM;
		break;
	case 5:
		status = ORPH;
		break;
	default:
		break;
	}
}
int process::getexc_time()
{
	return exc_time;
}
int process::getEarlestDeadline()
{
	return early_dead;
}
int process::getrem_time()
{
	return rem_time;
}

bool process::operator>(process p1)
{
	if (rem_time > p1.rem_time)
		return true;
	else
		return false;

}
bool process::operator<(process p1)
{
	if (rem_time < p1.rem_time)
		return true;
	else
		return false;

}
void process::dequeueIOlist_Set()
{
	item<int>IO;
	iopairqueue.dequeue(IO);
	if (iopairqueue.isEmpty() == false) {
		IO = iopairqueue.peak();
		IO_R = IO.FirstItem;
		IO_D = IO.SecondItem;
	}
	
}

void process::enqueIOlist(int ior, int iod)
{
	item<int>IO;
	IO.FirstItem = ior;
	IO.SecondItem = iod;
	iopairqueue.enqueue(IO.FirstItem, IO.SecondItem);
}
void process::peekIor()
{
	if (iopairqueue.isEmpty() == false)
		setIOR(iopairqueue.peak().FirstItem);
	

}
void process::peekIod()
{
	if (iopairqueue.isEmpty() == false)
		setIOD(iopairqueue.peak().SecondItem);

}

void process::setID(int ID)
{
	Id = ID;
}
void process::setEarlestDeadline(int eardead) 
{
	early_dead = eardead;
}

//*** get KILL TIME

int process::getKillTime()
{
	return KT;
}




void process::save(ofstream& file)
{
	file << T_time << "  " << Id << "  " << Arr_time << "  " << exc_time << "  " << IO_D << "  " << W_time << "  ";
	file << R_time << " " << TR_time << "  " << endl;
}

ostream& operator<<(ostream& output, process& p)
{
	output << p.getID();
	return output;
}
ostream& operator<<(ostream& output, const process& p) {
	output << p.Id;
	return output;
}
	bool process::operator<=(process p1)
	{
		if ((rem_time < p1.rem_time) || (rem_time == p1.rem_time))
			return true;
		else
			return false;

	}

	bool process::operator>=(process p1)
	{
		if ((rem_time > p1.rem_time)||  (rem_time == p1.rem_time))
			return true;
		else
			return false;

	}



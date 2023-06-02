#pragma once
#include <iostream>
#include "Scheduler.h"
using namespace std;
#include"UI.h"

int main()
{

	UI oUI(2);
	UI* pUI = new UI(oUI);
	Scheduler scheduler = Scheduler(pUI);

	return 0;
}

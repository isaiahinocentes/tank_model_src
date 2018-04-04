// Tank_Model_Source.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream> //For Cout and CIN
#include "Compute.h" //Nandito mga computation functions
#include "Model.h" //Tank Model Functions
#include "Functions.h" //System Usable Functions

using namespace std;

int main()
{
	//c_hA();
	srand(time(NULL));
	
	read_file_init();
	init_Qs();
	compute_h();
	compute_H();

	system("Pause>0");
    return 0;
}


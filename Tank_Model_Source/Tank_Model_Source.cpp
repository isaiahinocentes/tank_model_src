// Tank_Model_Source.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream> //For Cout and CIN
#include "Compute.h" //Nandito mga computation functions
#include "Model.h" //Tank Model Functions
#include "Functions.h" //System Usable Functions

using namespace std;

int main()
{
	srand(time(NULL));
	
	read_file_init("C:\\Users\\isaia\\Desktop\\sample.txt");
	
	init_Qs();
	COMPUTE();
	COMPUTE_OEF(3);
	
	system("Pause>0");
    return 0;
}


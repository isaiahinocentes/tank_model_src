// Tank_Model_Source.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream> //For Cout and CIN
#include "Compute.h" //Nandito mga computation functions
#include "Model.h" //Tank Model Functions
#include "Functions.h" //System Usable Functions

using namespace std;

int main()
{
	//Read file and Save Entries
	cout << "_______Read file and Save Entries_______" << endl;
	read_file_init("C:\\Users\\isaia\\Desktop\\sample.txt");
	
	//Initialize Qs
	cout << "_______Initialize Qs and Tank Height..._______" << endl;
	init_parameters();

	//Do all Computation
	cout << "_______Doing all Computation...________" << endl << endl;
	COMPUTE();
	
	//Compute for OEF
	cout << "_______Computing OEFs...________" << endl << endl;
	COMPUTE_OEF(5);
	
	system("Pause>0");
    return 0;
}


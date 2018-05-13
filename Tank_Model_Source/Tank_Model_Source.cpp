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

	do {

		//Initialize Qs
		//cout << "_______Initialize Qs and Tank Height..._______" << endl;
		//init_parameters();

		//Do all Computation
		cout << "_______Doing all Computation...________" << endl << endl;
		COMPUTE();
		showHeights();
		showQs();
		showQCs();
		showQCvQO();

		//Compute for OEF
		cout << "_______Computing OEFs...________" << endl;
		COMPUTE_OEF(0);

		cout << "\t **** ROUND 1: " << ACCEPTED << " ****" << endl << endl;
		
		system("Pause > 0");

	} while (ACCEPTED == 0);

	save_file();

	system("Pause>0");
    return 0;
}


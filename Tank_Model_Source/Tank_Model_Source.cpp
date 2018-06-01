// Tank_Model_Source.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream> //For Cout and CIN
#include "Compute.h" //Nandito mga computation functions
#include "Model.h" //Tank Model Functions
#include "Functions.h" //System Usable Functions

using namespace std;

int main()
{
	/*double min = .43;
	double max = .45;
	double d = 0;
	for (int i = 0; i < 100; i++) {
		d = (max - min) * ((double)rand() / (double)RAND_MAX) + minj;
		cout << d << endl;
	}
	system("Pause>0");
	*/

	YA1 = 0;
	YA2 = 10.68488165;
	YB1 = 7.613009048;
	YC1 = 10.37997893;
	YD1 = 18.74818991;


	double pr[] = {
		32.43917744,
		31.30934903,
		14.73307713,
		1.96934458,
		21.56093085,
		7.571884838,
		1.137823166
	};
	
	for each (double db in pr){
		cout << endl << " | " << db << "\t" << predictRainfall(db)-db << "\t" << endl;
	}
	system("Pause > 0");


	//Read file and Save Entries
	//cout << "_______Read file and Save Entries_______" << endl;
	//read_file_init("C:\\Users\\isaia\\Desktop\\sample_data.txt");
	//init_Heights(QO_ave);

	//system("Pause > 0");

	//do {

		//Initialize Qs
		//cout << "_______Initialize Qs and Tank Height..._______" << endl;
		//init_Heights(QO_ave);
		//init_parameters();

		//Do all Computation
		//cout << "_______Doing all Computation...________" << endl << endl;
		//compute();
		//showHeights();
		//showQs();
		//showQCs();
		//showQCvQO();

		//Compute for OEF
		//cout << "_______Computing OEFs...________" << endl;
		//COMPUTE_OEF(0);

		//cout << "\t **** ROUND 1: " << ACCEPTED << " ****" << endl << endl;
		
		//system("Pause > 0");

	//} while (ACCEPTED == 0);
	//} while (0);

	//save_file(2);

	system("Pause>0");
    return 0;
}


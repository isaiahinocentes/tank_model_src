#pragma once
#include <fstream>	//filestream
#include <sstream>	//for istringstream iss
#include <iostream>	//cout / cin
#include <string>	//for: cout << <string>
#include <string.h>	//String Manipulation
#include <vector>	//Vectors
#include <iomanip>	//Showing Precisions
#include "Model.h"	//Tank Model Variables	
#include "Compute.h" //Computations and Conversions

using namespace std;

//Read file with the filepath and set Values for Tank Model Variables
static void read_file_init(string path) {
	ifstream file(path);
	if (file.fail()) {
		//Show dialog that file Can't be opened
	}

	int row = 0;
	string str;

	//Set the Drainage Area to mm units
	file >> str;
	DA_km2 = atof(str.c_str());
	DA_mm2 = km22mm2(DA_km2);


	file >> str;
	TankHeight = atof(str.c_str());

	/*cout << "Drainage Area: " << DA_km2 << "\t|\t" << setprecision(5) << DA_mm2 << endl;
	cout << "Tank Height: " << TankHeight << endl << endl;;*/

	while (!file.eof()) {

		file >> str;
		vPrecipiation.push_back(atof(str.c_str()));
		
		file >> str;
		double qo = atof(str.c_str());
		qo = lps2mmd(qo); //Convert the QO liters/sec to mm/day
		vQObserved.push_back(qo);

		/*cout << "Data[" << row << "]:" << endl
			<< "P: " << vPrecipiation.at(row) << endl
			<< "QO: " << vQObserved.at(row) << endl;*/
		row++;
	}

	QO_ave = ave_QO();
	Prec_ave = ave_Prec();
	cout << "Done Reading File and Initilizations..." << endl << endl;
}

static void save_file() {
	cout << endl << "_______ Saving File ________" << endl;
	//Change this with current time
	srand(time(NULL));

	string filepath = "C:\\Users\\isaia\\Desktop\\model.txt";
	//strcat(filepath, filepath);
	//filepath += filepath + ".txt";

	cout << "Filepath: " << filepath << endl;

	ofstream file(filepath);

	if (file.good()) {

		cout << "File is Good, saving Values..." << endl;
		
		file << setprecision(10);

		//Save Qs
		file << "QA1:" << QA1 << endl;
		file << "QA2:" << QA2 << endl;
		file << "QA0:" << QA0 << endl;

		file << "QB1:" << QB1 << endl;
		file << "QB0:" << QB0 << endl;

		file << "QC1:" << QC1 << endl;
		file << "QC0:" << QC0 << endl;

		file << "QD1:" << QD1 << endl;

		//Save Tank Height
		file << "TankHeight:" << TankHeight << endl;

		//Save Ys = Height of Orifices
		file << "YA1:" << YA1 << endl;
		file << "YA2:" << YA2 << endl;
		file << "YB1:" << YB1 << endl;
		file << "YC1:" << YC1 << endl;
		file << "YD1:" << YD1;

		cout << "file Saved!.." << endl;
	}
	else {
		cout << "File Can't be created..." << endl;
	}

}
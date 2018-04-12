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
	DA_km = atof(str.c_str());
	DA_mm = km2mm(DA_km);


	file >> str;
	TA = atof(str.c_str());

	cout << "Drainage Area: " << DA_km << "\t|\t" << setprecision(5) << DA_mm << endl;
	cout << "Tank Height: " << TA << endl << endl;;

	while (!file.eof()) {

		file >> str;
		vPrecipiation.push_back(atof(str.c_str()));
		file >> str;
		double qo = atof(str.c_str());
		qo = lps2mmd(qo);
		vQObserved.push_back(qo);

		cout << "Data[" << row << "]:" << endl
			<< "P: " << vPrecipiation.at(row) << endl
			<< "QO: " << vQObserved.at(row) << endl;
		row++;
	}

	cout << endl;
	QO_ave = ave_QO();
	cout << QO_ave << endl;
	Prec_ave = ave_Prec();
	cout << Prec_ave << endl;
}
#pragma once
#include <fstream>	//filestream
#include <sstream>	//for istringstream iss
#include <iostream>	//cout / cin
#include <string>	//for: cout << <string>
#include <string.h>	//String Manipulation
#include <vector>	//Vectors
#include <iomanip>	//Showing Precisions
#include "Model.h"	//	
#include "Functions.h" //

using namespace std;


static void read_file_init() {
	
	ifstream in("C:\\Users\\isaia\\Desktop\\sample.txt");
	if (in.fail()) {
		cout << "File Not Found";
		system("Pause > 0");
		exit(0);
	}

	int row = 0;
	string str;
	
	in >> str;
	DA_km = atof(str.c_str());
	DA_mm = km2mm(DA_km);
	in >> str;
	TA = atof(str.c_str());
	
	cout << "Drainage Area: " << DA_km << "\t|\t" << setprecision(5) << DA_mm << endl;
	cout << "Tank Height: " << TA << endl << endl;;
	
	while (!in.eof()) {
		
		in >> str;
		vPrecipiation.push_back(atof(str.c_str()));
		in >> str;
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
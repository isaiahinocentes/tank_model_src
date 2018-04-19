#pragma once
#include <iostream> //for COUT and CIN
#include <cmath>	//For Computation
#include <string.h> //For String
#include <string>	//For cout << string
#include <stdlib.h>	//srand, rand
#include <time.h>	//time
#include <iomanip>	//For Output Formatting
#include <vector>	//Vectors

using namespace std;

//Function Prototypes
static void init_QA(double);
static void init_QB(double);
static void init_QC(double);
static void init_QD(double);
//
static double random_h(double);
static double random_v(double);
static double random_vh(double);
//
static void line(double);
static void line(string, double);
static void line(string);
//
double n;

//Model Variables
static double QComp, QC_ave;
static vector<double> vQCalculated;
static double QObs, QO_ave;
static vector<double> vQObserved;

//RainFall mm/day
static double RFall;

//Drainage Area in km²
static double DA_km2;
//Drainage Area in mm²
static double DA_mm2;

//Tank Height in mm
static double TankHeight;

//Precipitaiton in mm/day
static double Prec = 0, Prec_ave;
static vector<double> vPrecipiation;
//Evaporation mm/day
static double Evap = 0, Evap_ave;
static vector<double> vEvaporation;

//Discharges mm/day | Random/calibrated Values
static double QA1, QA2, QA0;
static double QB1, QB0;
static double QC1, QC0;
static double QD1;

//Discharges on Tanks A-D mm³/day
static double hA;
static double hB;
static double hC;
static double hD;

//Water Level on Tanks mm
static double  HA;
static double  HB;
static double  HC;
static double  HD;

//Height of the Orifice in the Tanks
static double YA1 = 0; //The top level orifice.
static double YA2;
static double YB1;
static double YC1;
static double YD1;

//Discharge(Qx) Multipliers | 0 or 1
static double nA1, nA2, nB1, nC1, nD1;

//Initialize Qs Parameters
static void init_QA(double max) {
	

	QA1 = random_h(max);
	QA2 = random_h(QA1);
	QA0 = QA1 - QA2;
	//QA0 = random_v(QA2);
	
	//Conditions
	//Where Conditions
	/*do {
		if (QA1 <= QA2) {
			cout << "QA2 is >= QA1" << endl;
			QA2 = random_h(QA1); //Repeat for QA2
		}
		if (QA2 <= QA0) {
			cout << "QA0 >= QA2";
			QA0 = random_h(QA2); 
		}
		//If 40, 30, 11
		//30+11 > 40, 11= 10
		if (QA2 + QA0 > QA1) {
			QA0 = QA1 - QA2;
		}
		if ((QA2+QA0) > QA1) {
			break;
		}
	} while (false);*/

	line("QA1: ", QA1);
	line("QA2: ", QA2);
	line("QA0: ", QA0);
}
static void init_QB(double max) {
	QB1 = random_h(max);
	QB0 = QA0 - QB1;
	//QB0 = random_v(QB1);

	line("QA0: ", QA0);
	line("QB1: ", QB1);
	line("QB0: ", QB0);
}
static void init_QC(double max) {
	QC1 = random_h(max);
	QC0 = QB0 - QC1;
	//QC0 = random_h(QC1);

	line("QB0: ", QB0);
	line("QC1: ", QC1);
	line("QC0: ", QC0);
}
static void init_QD(double max) {
	QD1 = QC1 - QC0;
	//QD1 = random_vh(max);

	line("QD1: ", QD1);
}
static void init_parameters() {
	srand(time(NULL));

	line("\nQO Ave: ", QO_ave);
	init_QA(QO_ave);
	init_QB(QA0);
	init_QC(QB0);
	init_QD(QC0);
}

//TO EDIT
static void showResults() {

	cout << "P, E, A | mm/day:" << "\n";
	cout << "\nPrecipitation: " << Prec << "\n";
	cout << "Evaporation: " << Evap << "\n";
	cout << "Drainage Area: " << DA_mm2 << "\n";
	cout << "\n";
	cout << "Discharge (Q) Values | mm/day: " << "\n";
	cout << "QA1,2,0: " << QA1 << "\t" << QA2 << "\t" << QA0 << "\n";
	cout << "QB1, 0: " << QB1 << "\t" << QB0 << "\n";
	cout << "QC1, 0: " << QC1 << "\t" << QC0 << "\n";
	cout << "QD1: " << QD1 << "\n";
	cout << "\n";
	cout << "Values of Water Levels(h) | mm/day" << "\n";
	cout << "hA: " << hA << "\n";
	cout << "hB: " << hB << "\n";
	cout << "hC: " << hC << "\n";
	cout << "hD: " << hD << "\n";
	cout << "\n";
	cout << "Height of Orifice (Y) | mm[/day]: " << "\n";
	cout << "YA1: " << YA1 << " | " << nA1 << "\n";
	cout << "YA2: " << YA2 << " | " << nA2 << "\n";
	cout << "YB1: " << YB1 << " | " << nB1 << "\n";
	cout << "YC1: " << YC1 << " | " << nC1 << "\n";
	cout << "YD1: " << YD1 << " | " << nD1 << "\n";
	cout << "\n";
	cout << "QC | mm[/day]: " << "\n";
	cout << "QC = QA1 + QA2 + QB1 + QC1 + QD1\n";
	cout << QA1*nA1 << " + " <<
		QA2*nA2 << " + " <<
		QB1*nB1 << " + " <<
		QC1*nC1 << " + " <<
		QD1*nD1 << " = " << QComp;
}

//generate randome
static double random_h(double max) {
	n = max;
	srand(max);
	while (n >= max) {
		n = rand();
	}
	return n;
}
static double random_v(double max) {
	n = max;
	while (n < max) {
		n = rand();
	}
	return n;
}
static double random_vh(double max) {
	n = max + 1;
	while (n <= max) {
		n = rand();
	}
	return n;
}

//Printing Functions
static void line(double db) {
	cout << db << "\n";
}
static void line(string st, double db) {
	cout << st << setprecision(11) << fixed << db << "\n";
}
static void line(string db) {
	cout << db << "\n";
}
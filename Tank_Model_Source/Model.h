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
static void init();
static double random();
static void line(double);
static void line(string, double);
static void line(string);
double n;

//
static double QComp, QC_ave;
static vector<double> vQCalculated;
static double QObs, QO_ave;
static vector<double> vQObserved;

//RainFall mm/day
static double RFall;

//Drainage Area in km²
static double DA_km;
//Drainage Area in mm²
static double DA_mm;

//Tank Height
static double TA;

//Precipitaiton in mm/day
static double Prec = 0, Prec_ave;
//Precipitaiton in mm/day
static vector<double> vPrecipiation;
//Evaporation mm/day
static double Evap = 0, Evap_ave;
//Evaporation mm/day
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

//Intialize the variables
static void init() {

	Prec = pow(random(), 2); //The output value was to small.
	line("Prec: ", Prec);

	Evap = 0;

	QA1 = fmod(random(), Prec);
	line("QA1: ", QA1);

	QA2 = fmod(random(), QA1);
	line("QA2: ", QA2);

	QA0 = fmod(random(), QA2);
	line("QA0: ", QA0);

	QB1 = fmod(random(), QA0);
	line("QB1: ", QB1);

	QB0 = fmod(random(), QB1);
	line("QB0: ", QB0);

	QC1 = fmod(random(), QB0);
	line("QC1: ", QC1);

	QC0 = fmod(random(), QC1);
	line("QC0: ", QC0);

	QD1 = fmod(random(), QC0);
	line("QD1: ", QD1);

	YD1 = random();
	line("YD1: ", YD1);

	YC1 = fmod(random(), YD1);
	line("YC1: ", YC1);

	YB1 = fmod(random(), YC1);
	line("YB1: ", YB1);

	YA2 = fmod(random(), YB1);
	line("YA2: ", YA2);

	YA1 = 0;
	line("YA1: ", YA1);
}

static void init_Qs() {

	//Say QO = 100;

	/*
	50
	35
	10
	5

	1 QA1 90
	2 QA2 80
	3 QA0 70

	4 QB1 60
	5 QB0 50

	6 QC1 40
	7 QC0 30

	8 QD1 20
	*/

	//QA1 = fmod(random(), 0);
	QA1 = QO_ave * .9;
	line("QA1: ", QA1);

	//QA2 = fmod(random(), QA1);
	QA2 = QO_ave * .8;
	line("QA2: ", QA2);

	//QA0 = fmod(random(), QA2);
	QA0 = QO_ave * .7;
	line("QA0: ", QA0);

	//QB1 = fmod(random(), QA0);
	QB1 = QO_ave * .6;
	line("QB1: ", QB1);

	//QB0 = fmod(random(), QB1);
	QB0 = QO_ave * .5;
	line("QB0: ", QB0);

	//QC1 = fmod(random(), QB0);
	QC1 = QO_ave * .4;
	line("QC1: ", QC1);

	//QC0 = fmod(random(), QC1);
	QC0 = QO_ave * .3;
	line("QC0: ", QC0);

	//QD1 = fmod(random(), QC0);
	QD1 = QO_ave * .2;
	line("QD1: ", QD1);
	cout << endl;

}

static void showResults() {

	cout << "P, E, A | mm/day:" << "\n";
	cout << "\nPrecipitation: " << Prec << "\n";
	cout << "Evaporation: " << Evap << "\n";
	cout << "Drainage Area: " << DA_mm << "\n";
	cout << "\n";
	cout << "Discharge (Q) Values | mm/day: " << "\n";
	cout << "QA1, 2,0: " << QA1 << "\t" << QA2 << "\t" << QA0 << "\n";
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
	cout << "Values of Height(H) | mm[/day]:" << "\n";
	cout << "HA: " << HA << " \n";
	cout << "HB: " << HB << " \n";
	cout << "HC: " << HC << " \n";
	cout << "HD: " << HD << " \n";
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
static double random() {
	n = rand();
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
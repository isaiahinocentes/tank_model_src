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
static void init_Qs(double);
static void init_Heights(double);
static double random(double, double);
static void init_Qs_Orifice(double);
static void line(double);
static void line(string, double);
static void line(string);
double n;

//liters/second = mm³/day
static double QComp, QC_ave;
static vector<double> vQCalculated;
static double QObs, QO_ave;
static vector<double> vQObserved;
//OEF
static double OEFv;

//RainFall mm³/day
static double RFall;

//Drainage Area in km²
static double DA_km;
//Drainage Area in mm²
static double DA_mm;

//Precipitaiton in mm/day
static double Prec = 0, Prec_ave;
//Precipitaiton in mm/day
static vector<double> vPrecipitation;
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

//Tank Height
static double TankHeight;
//Height of the Orifice in the Tanks
static double YA1; //The top level orifice.
static double YA2;
static double YB1;
static double YC1;
static double YD1;

//Discharge(Qx) Multipliers | 0 or 1
static double nA1, nA2, nB1, nC1, nD1;

//Init Qs Depending on QO | This uses percentage
static void init_Heights(double base) {

	init_Qs_Orifice(base);

	YA1 = 0;
	YA2 = (QA1 + QA2 + QA0) / 3;
	YB1 = (QB1 + QB0) / 2;
	YC1 = (QC1 + QC0) / 2;
	YD1 = QD1;

	TankHeight = YA1 + YA2 + YB1 + YC1 + YD1;
	cout << YA1 << endl;
	cout << YA2 << " = " << QA1 << " " << QA2 << " " << QA0 << endl;
	cout << YB1 << " = " << QB1 << " " << QB0 << endl;
	cout << YC1 << " = " << QC1 << " " << QC0 << endl;
	cout << YD1 << " = " << QD1 << endl;
	cout << TankHeight << endl;
}

static double ERROR_MARGIN = 0.05;
static double BASE_MARGIN = 0.05;
//Initialize Smaller Tank Heights
static void init_Qs_Orifice(double base) {
	QA1 = random(base * (BASE_MARGIN + ERROR_MARGIN), base * (BASE_MARGIN));
	QA2 = random(base * (BASE_MARGIN + ERROR_MARGIN), base * (BASE_MARGIN));
	QB1 = random(base * (BASE_MARGIN + ERROR_MARGIN), base * (BASE_MARGIN));
	QC1 = random(base * (BASE_MARGIN + ERROR_MARGIN), base * (BASE_MARGIN));
	QD1 = random(base * (BASE_MARGIN + ERROR_MARGIN), base * (BASE_MARGIN));
}

//Init Qs Depending on QO | This uses percentage
static void init_Qs(double QO) {

	QA1 = QO * .48;
	line("QA1: ", QA1);

	QA2 = QO * .33;
	line("QA2: ", QA2);

	QA0 = QO * .17;
	line("QA0: ", QA0);

	QB1 = QO * .9;
	line("QB1: ", QB1);

	QB0 = QO * .6;
	line("QB0: ", QB0);

	QC1 = QO * .3;
	line("QC1: ", QC1);

	QC0 = QO * .2;
	line("QC0: ", QC0);

	QD1 = QO * .1;
	line("QD1: ", QD1);
	cout << endl;

}

//Reset Values
static void resetValues() {

	QComp = 0; QC_ave = 0;
	vQCalculated.clear();

	QObs = 0; QO_ave = 0;
	vQObserved.clear();

	RFall = 0;

	DA_km = 0;
	DA_mm = 0;

	TankHeight = 0;

	Prec = 0; Prec_ave = 0;
	vPrecipitation.clear();

	Evap = 0; Evap_ave = 0;
	vEvaporation.clear();

	QA1 = 0; QA2 = 0; QA0 = 0;
	QB1 = 0; QB0 = 0;
	QC1 = 0; QC0 = 0;
	QD1 = 0;

	hA = 0; hB = 0; hC = 0; hD = 0;
	HA = 0; HB = 0; HC = 0; HD = 0;

	YA1 = 0; YA2 = 0;
	YB1 = 0;
	YC1 = 0;
	YD1 = 0;

}

//generate randome
//generate randome
double random(double max, double min)
{
	return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
}
//Printing Functions
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
//Show the Values to Log textbox
static void getFromFile() {
	std::cout << setprecision(2);
	//Log->Text = "";
	//Log->Text += "Drainage Area: " + DA_mm + "\r\n";
	//Log->Text += "Precipitation | QObserved\r\n";
	for (int i = 0; i < vPrecipitation.size() && i < vQObserved.size(); i++) {
		//Log->Text += vPrecipitation.at(i) + " \t\t| " + vQObserved.at(i) + "\r\n";
		cout << vPrecipitation.at(i) << "\t| " << vQObserved.at(i) << endl;
	}
}

static void line(double db) {
	cout << db << "\n";
}
static void line(string st, double db) {
	cout << st << setprecision(11) << fixed << db << "\n";
}
static void line(string db) {
	cout << db << "\n";
}
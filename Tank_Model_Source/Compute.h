#pragma once
#include "Model.h"
#include <iomanip> //For output formatting

//Conversion 
static double lps2mmd(double lps) {
	return (lps * 1000000) / 87400l;
}
static double km2mm(double km) {
	return km * 1000000000000;
}
static double Qlps2Qmmd() {

}

//Averages
static double ave_QO() {
	double sum = 0;
	for each (double QO in vQObserved)
	{
		sum += QO;
	}
	double ave = sum / sizeof(vQObserved);
	cout << "Average for QO: " << ave << endl;
	return ave;
}
static double ave_Prec() {
	double sum = 0;
	for each (double p in vPrecipiation)
	{
		sum += p;
	}
	double ave = sum / sizeof(vPrecipiation);
	cout << "Average for Precipitation: " << ave << endl;
	return ave;
}

//Compute hA, hB, hC, hD
static double c_hA(double p, double e, double qa1, double qa2, double qa0) {
	return p - e - qa1 - qa2 - qa0;
}
static double c_hB(double qa0, double qb1, double qb0) {
	return qa0 - qb1 - qb0;
}
static double c_hC(double qb0, double qc1, double qc0) {
	return QB0 - QC1 - QC0;
}
static double c_hD(double qc0, double qd1) {
	return qc0 - qd1;
}
static void compute_h() {
	int n = vQObserved.size();
	for (int i = 0; i < n; i++)
	{
		hA = c_hA(vQObserved.at(i), Evap, QA1, QA2, QA0); //The first parameter should be Precipitation.at(i)
		hB = c_hB(QA0, QB1, QB0);
		hC = c_hC(QB0, QC1, QC0);
		hD = c_hD(QC0, QD1);

		cout << "Values for \"h\": " << endl
			<< "hA:" << setprecision(10) << hA << endl
			<< "hB:" << setprecision(10) << hB << endl
			<< "hC:" << setprecision(10) << hC << endl
			<< "hD:" << setprecision(10) << hD << endl << endl;
	}
}

//Compute HA, HB, HC, HD
static double c_HA(double hA) {
	return hA / DA_mm;
}
static double c_HB(double hB) {
	return hB / DA_mm;
}
static double c_HC(double hC) {
	return hC / DA_mm;
}
static double c_HD(double hD) {
	return hD / DA_mm;
}
static void compute_H() {
	int n = vQObserved.size();
	for (int i = 0; i < n; i++)
	{
		HA = c_HA(hA);
		HB = c_HB(hB);
		HC = c_HC(hD);
		HD = c_HD(hD);

		cout << "Values for \"H - Water Levels\": " << endl
			<< "HA:" << setprecision(10) << HA << endl
			<< "HB:" << setprecision(10) << HB << endl
			<< "HC:" << setprecision(10) << HC << endl
			<< "HD:" << setprecision(10) << HD << endl << endl;
	}
}

//Compute for Discharge Multiplirs
static double c_nA1() {
	if (HA > YA1) {
		return 1;
	}
	return 0;
}
static double c_nA2() {
	if (HA > YA2) {
		return 1;
	}
	return 0;
}
static double c_nB1() {
	if (HB > YB1) {
		return 1;
	}
	return 0;
}
static double c_nC1() {
	if (HC > YC1) {
		return 1;
	}
	return 0;
}
static double c_nD1() {
	if (HD > YD1) {
		return 1;
	}
	return 0;
}

//Compute QC
static double c_QC() {
	return
		(QA1 * nA1) +
		(QA2 * nA2) +
		(QB1 * nB1) +
		(QC1 * nC1) +
		(QD1 * nD1);
}
static void computeQCalculated() {
	//Get values for h
	//hA = c_hA();
	//hB = c_hB();
	//hC = c_hC();
	//hD = c_hD();

	//get the height of the tanks
	//HA = c_HA();
	//HB = c_HB();
	//HC = c_HC();
	//HD = c_HD();

	//the Multipliers
	//nA1 = c_nA1();
	//nA2 = c_nA2();
	//nB1 = c_nB1();
	//nC1 = c_nC1();
	//nD1 = c_nD1();

	//Compute QC
	QComp = c_QC();
}
#pragma once
#include "Model.h" //Tank Model Variables
#include "OEF.h"
#include <iomanip> //For output formatting


//l/ps to mm/day
static double lps2mmd(double lps) {
	lps = lps * 1000000 * 86400;
	return lps / DA_mm2;
}

//precipiation mm/day to lps
static double mmd2lps(double value) {
	/*
	ymm * xmm² 
	= xymm³ 
	= xy liters/1000000m³
	== 
	mm/day
	mm³/day
	liters/day
	liters/hrs
	liters/min
	liters/sec
	*/
	double tmp = Prec * DA_mm2; //mm³
	tmp = tmp / 1000000; //mm³ -> liters
	tmp = tmp / 0;//day to secs

}

//km² to mm²
static double km22mm2(double km) {
	return km * 1000000000000;
}

//Get the average Q Observed
static double ave_QO() {
	double sum = 0;
	for each (double QO in vQObserved)
	{
		sum += QO;
	}
	double ave = sum / sizeof(vQObserved);
	return ave;
}

//Get Average Precipitation
static double ave_Prec() {
	double sum = 0;
	for each (double p in vPrecipiation)
	{
		sum += p;
	}
	double ave = sum / sizeof(vPrecipiation);
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
	return qb0 - qc1 - qc0;
}
static double c_hD(double qc0, double qd1) {
	return qc0 - qd1;
}

//Compute for Discharge Multiplirs
static double c_nA1(double hA) {
	return hA > YA1 ? 1 : 0;
}
static double c_nA2(double hA) {
	return hA > YA2 ? 1 : 0;
}
static double c_nB1(double hB) {
	return hB > YB1 ? 1 : 0;
}
static double c_nC1(double hC) {
	return hC > YC1 ? 1 : 0;
}
static double c_nD1(double hD) {
	return hD > YD1 ? 1 : 0;
}

//Compute for QC for each entry
static void COMPUTE() {
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
		
		nA1 = c_nA1(hA);
		nA2 = c_nA2(hA);
		nB1 = c_nB1(hB);
		nC1 = c_nC1(hC);
		nD1 = c_nD1(hD);

		cout << "Multipliers [1/0]: " << endl
			<< "A1:" << nA1 << endl
			<< "A2:" << nA2 << endl
			<< "B1:" << nB1 << endl
			<< "C1:" << nC1 << endl
			<< "D1:" << nD1 << endl << endl;
		
		double tmp_QC = 
			(QA1 * nA1) +
			(QA2 * nA2) +
			(QB1 * nB1) +
			(QC1 * nC1) +
			(QD1 * nD1);

		cout << "QC = " << endl
			<< QA1 << "*" << nA1 << " + " << endl
			<< QA2 << "*" << nA1 << " + " << endl
			<< QB1 << "*" << nB1 << " + " << endl
			<< QC1 << "*" << nC1 << " + " << endl
			<< QD1 << "*" << nD1 << " = " << endl 
			<< tmp_QC << endl << endl;

		vQCalculated.push_back(tmp_QC);
	}

	cout << "Finished Copmutations..." << endl << endl;
}

/*
Range and Optimal Values
R	|-1.0 to 1.0 | -1 (negative slope) or +1 (positive slope)
R2	|0.0 to 1.0	 | 1.0
MAE	|0.0 to inf	 | 0.0
RSME|0.0 to inf	 | 0.0
*/
//Add R² or R2 to OEF Functions
static void COMPUTE_OEF(int oef) {
	//correl = R
	if (oef == 0) {
		cout << endl << "OEF VALUES:" << endl;
		cout << "CORREL: " << coeffcorrel(vQCalculated, vQObserved) << endl;
	}
	//MAE
	else if (oef == 1) {
		cout << endl << "OEF VALUES:" << endl;
		cout << "MAE: " << mae(vQCalculated, vQObserved) << endl;
	}
	//rmse
	else if (oef == 2) {
		cout << endl << "OEF VALUES:" << endl;
		cout << "RMSE: " << rmse(vQCalculated, vQObserved) << endl;
	}
	else if (oef == 999) {
		vector<double> test;
		for (int i = 0; i < 11; i++) {
			test.push_back(i);
		}

		cout << endl << "OEF VALUES:" << endl;
		cout << "CORREL: " << coeffcorrel(test, test) << endl;
		cout << "MAE: " << mae(test, test) << endl;
		cout << "RMSE: " << rmse(test, test) << endl;
	}
	//All
	else {
		cout << endl << "OEF VALUES:" << endl;
		cout << "CORREL: " << coeffcorrel(vQCalculated, vQObserved) << endl;
		cout << "MAE: " << mae(vQCalculated, vQObserved) << endl;
		cout << "RMSE: " << rmse(vQCalculated, vQObserved) << endl;

		/*cout << endl << "OEF VALUES:" << endl;
		cout << "CORREL: " << coeffcorrel(vQCalculated, vQCalculated) << endl;
		cout << "MAE: " << mae(vQCalculated, vQCalculated) << endl;
		cout << "RMSE: " << rmse(vQCalculated, vQCalculated) << endl;

		cout << endl << "OEF VALUES:" << endl;
		cout << "CORREL: " << coeffcorrel(vQObserved, vQObserved) << endl;
		cout << "MAE: " << mae(vQObserved, vQObserved) << endl;
		cout << "RMSE: " << rmse(vQObserved, vQObserved) << endl;*/
	}
}
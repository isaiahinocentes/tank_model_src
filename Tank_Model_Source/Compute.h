#pragma once
#include "Model.h" //Tank Model Variables
#include <iomanip> //For output formatting
#include <iostream>

//Conversions
//l/ps to mm³/day
static double lps2mmd(double lps, double da_mm) {
	return (lps * 86400000000) / da_mm;
}
//km² to mm²
static double km2mm(double km) {
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
	std::cout << "Average for QO: " << ave << endl;
	return ave;
}

//Get Average Precipitation
static double ave_Prec() {
	double sum = 0;
	for each (double p in vPrecipitation){
		sum += p;
	}
	double ave = sum / sizeof(vPrecipitation);
	std::cout << "Average for Precipitation: " << ave << endl;
	return ave;
}

//Water balance Equations
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

//Multipliers for QC
static void compute_multipliers() {
	QA1 >= YA1 ? nA1 = 1 : nA1 = 0;
	QA2 >= YA2 ? nA2 = 1 : nA2 = 0;
	QB1 >= YB1 ? nB1 = 1 : nB1 = 0; 
	QC1 >= YC1 ? nC1 = 1 : nC1 = 0;
	QD1 >= YD1 ? nD1 = 1 : nD1 = 0;
}

//Compute QC
static void compute() {

	int n = vQObserved.size();

	cout <<  "----- QCs ----" << endl;

	for (int i = 0; i < n; i++)
	{
		//Initialize QS using QO
		init_Qs(vQObserved.at(i));

		//Calculate water level on tanks
		hA = c_hA(vPrecipitation.at(i), Evap, QA1, QA2, QA0);  //This will be - if P = 0
		hB = c_hB(QA0, QB1, QB0);
		hC = c_hC(QB0, QC1, QC0);
		hD = c_hD(QC0, QD1);

		/*cout << "Values for \"h\": " << endl
		<< "hA:" << setprecision(10) << hA << endl
		<< "hB:" << setprecision(10) << hB << endl
		<< "hC:" << setprecision(10) << hC << endl
		<< "hD:" << setprecision(10) << hD << endl << endl;*/

		compute_multipliers();

		/*cout << "Multipliers [1/0]: " << endl
		<< "A1:" << nA1 << endl
		<< "A2:" << nA2 << endl
		<< "B1:" << nB1 << endl
		<< "C1:" << nC1 << endl
		<< "D1:" << nD1 << endl << endl;*/

		double tmp_QC =
			(QA1 * nA1) +
			(QA2 * nA2) +
			(QB1 * nB1) +
			(QC1 * nC1) +
			(QD1 * nD1);

		/*cout << "QC = " << endl
		<< QA1 << "*" << nA1 << " + " << endl
		<< QA2 << "*" << nA1 << " + " << endl
		<< QB1 << "*" << nB1 << " + " << endl
		<< QC1 << "*" << nC1 << " + " << endl
		<< QD1 << "*" << nD1 << " = " << endl
		<< tmp_QC << endl << endl;*/

		cout << "[" << i << "]: " << tmp_QC << endl;
		vQCalculated.push_back(tmp_QC);
	}

	cout << "--------------" << endl;
	cout << "Finished Copmutations..." << endl << endl;
}
static double predictRainfall(double prec) {

	double QC = 0;
	if (prec == 0) {
		QC += 0;
	} else {
		QC += YA1;
		prec -= YA2; //-9
		if (prec <= 0) {
			QC += YA2;
			//QC += YA2 - prec;
		} else {
			QC += YB1;
			prec -= YB1;
			if (prec <= 0) {
				QC += YB1 - prec;
			}
			else {
				QC += YC1;
				prec -= YC1;
				if (prec <= 0) {
					QC += YC1 - prec;
				}
				else {
					QC += YD1;
					prec -= YD1;
					if (prec <= 0) {
						QC += YD1 - prec;
					}
				}
			}
		}
	}
	return QC;
	/*
	//QA1
	//if (YA1 > QA1) {
	//	QA1 = YA1;
	//	cout << "QA1: " << QA1 << " ";
	//}
	//else {
		//prec -= YA1;
		//QA1 = prec;
		//cout << "QA1: " << QA1 << " ";


		//QA2
		if (YA2 > prec) {
			QA2 = YA2;
			cout << "QA2: " << QA2 << " ";
			return QA2;
		}
		else {
			QA2 = prec - YA2;
			cout << "QA2: " << QA2 << " ";
			//QB1
			if (YB1 > QB1) {
				QB1 = YB1;
				cout << "QB1: " << QB1 << " ";
				return QA2 + QB1;
			}
			else {
				QB1 = QA2 - YB1;
				cout << "QB1: " << QB1 << " ";
				
				//QC1
				if (YC1 > QC1) {
					QC1 = YC1;
					cout << "QC1: " << QC1 << " ";
					return QA2 + QB1 + QC1;
				}
				else {
					QC1 = QB1 - YC1;
					cout << "QC1: " << QC1 << " ";
					
					//QD1
					if (YD1 > QD1) { 
						QD1 = YD1; 
						cout << "QD1: " << QD1 << " ";
					} else { 
						QD1 = QC1 - YD1; 
						cout << "QD1: " << QD1 << " ";
					}
					return QA2 + QB1 + QC1 + QD1;
				}
			}
		}
	//}
	return QA1;*/
}

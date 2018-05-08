#pragma once
#include <vector> //Vectors
#include "Model.h"

using namespace std;

//Function Prototypes
static double mean(vector<double>);
static double sum(vector<double>);
static double sqsum(vector<double>);
static double stdev(vector<double>);
static vector<double> operator-(vector<double>, double);
static vector<double> operator*(vector<double>, vector<double>);

//R = Correlation Function
static double coeffcorrel(vector<double> QC, vector<double> QO)
{
	double r = sum((QC - mean(QC))*(QO - mean(QO))) / (QC.size()*stdev(QC)* stdev(QO));
	R = r;
	return r;
}

//R2 = Correlation Function
static double coeffcorrel2(vector<double> QC, vector<double> QO)
{
	double r2 = sum((QC - mean(QC))*(QO - mean(QO))) / (QC.size()*stdev(QC)* stdev(QO));
	r2 = pow(r2, 2);
	R2 = r2;
	return r2;
}

//MAE
static double mae(vector<double> QC, vector <double> QO) {
	double suma;
	int N = QC.size();
	for (unsigned i = 0; i < N; i++) {
		suma = abs(QC.at(i) - QO.at(i));
	}
	double mae = suma / N;
	MAE = mae;
	return mae;
}

//RMSE
static double rmse(vector <double> QC, vector <double> QO) {
	double suma;
	int N = QC.size();
	for (unsigned i = 0; i < N; i++) {
		suma = pow(QC.at(i) - QO.at(i), 2);
	}
	double rmse = sqrt(suma / N);
	RMSE = rmse;
	return rmse;
}

//--These are all for Coeffcorrel
static double mean(vector<double> a)
{
	return sum(a) / a.size();
}
static double sum(vector<double> a)
{
	double s = 0;
	for (int i = 0; i < a.size(); i++)
	{
		s += a[i];
	}
	return s;
}
static double sqsum(vector<double> a)
{
	double s = 0;
	for (int i = 0; i < a.size(); i++)
	{
		s += pow(a[i], 2);
	}
	return s;
}
static double stdev(vector<double> nums)
{
	double N = nums.size();
	return pow(sqsum(nums) / N - pow(sum(nums) / N, 2), 0.5);
}
static vector<double> operator-(vector<double> a, double b)
{
	vector<double> retvect;
	for (int i = 0; i < a.size(); i++)
	{
		retvect.push_back(a[i] - b);
	}
	return retvect;
}
static vector<double> operator*(vector<double> a, vector<double> b)
{
	vector<double> retvect;
	for (int i = 0; i < a.size(); i++)
	{
		retvect.push_back(a[i] * b[i]);
	}
	return retvect;
}
//--

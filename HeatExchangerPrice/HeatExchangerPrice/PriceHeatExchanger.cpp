//============================================================================
// Name        : PriceHeatExchanger.cpp
// Author      : Amirreza Mirbeygi Moghadam
// Version     : 1.0
// instructor  : Prof. Shahnazari
// Copyright   : only to the author and instructor
// Description : Estimating price of aheat exchanger in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <math.h>
#include <conio.h>
using namespace std;

int main() {
	////Estimating A
	///getting needed parameters from the user
	int Lq_n=1;
	double U, A, LMTD, C1, C2, T1i, T1o, T2i, T2o, Q, W1, W2;
	int ft = 1;
	int PresRange;
	int Material;
	int Type;
	cout << "Please choose a pair of fluids from the folowing list. " << endl;
	cout << "1:\tAroclor 1248-Jet fuels" << endl <<
		"2:\tCutback asphalt-Water" << endl <<
		"3:\tDemineralized water-Water" << endl <<
		"4:\tEthanol amine-Water or DEA" << endl <<
		"5:\tFuel oil-Water" << endl <<
		"6:\tFuel oil-Oil" << endl <<
		"7:\tGasoline-Water" << endl <<
		"8:\tHeavy oils-Heavy oils" << endl <<
		"9:\tHeavy oils-Water" << endl <<
		"10:\tHydrogen-rich reformer stream-Hydrogen-rich reformer stream" << endl <<
		"11:\tKerosene or gas oil-Water" << endl <<
		"12:\tKerosene or gas oil-Oil" << endl <<
		"13:\tKerosene or jet fuels-Trichlorethylene" << endl <<
		"14:\tJacket water-Water" << endl <<
		"15:\tLube oil (low viscosity)-Water" << endl <<
		"16:\tLube oil (high viscosity)-Water" << endl <<
		"17:\tLube oil-Oil" << endl <<
		"18:\tNaphtha-Water" << endl <<
		"19:\tNaphtha-Oil" << endl <<
		"20:\tWater-Water" << endl;
	cin >> Lq_n;

	cout << "Please enter the folowing parameters:\n1:\tinlet tempertare for the FIRST fluid,\n2:\toutlet tempertare for the FIRST fluid,\n3:\tinlet tempertare for the SECOND fluid,\n" <<
		"4:\tFIRST fluid's flow rate\n5:\tand SECOND fluid's flow rate"<< endl;
	cin >> T1i >> T1o >> T2i >> W1 >> W2;


	cout << "Please enter 1 for counter-current and 2 for cooperative-current." << endl;
	cin >> ft;

	//calculations
	double i = 0;
	double j = 0;
	ifstream inputfile;
	inputfile.open("data.txt");
	for (j; j<(Lq_n - 1) * 3; j++)
	{
		inputfile >> i;
	}
	inputfile >> U >> C1 >> C2;
	inputfile.close();
	T2o = T2i + (W1*C1*(T1i - T1o) / W2*C2);

	if (ft == 1)
		LMTD = ((T1i - T2o) - (T1o - T2i)) / log((T1i - T2o) - (T1o - T2i));
	if (ft == 2)
		LMTD = ((T1i - T2i) - (T1o - T2o)) / log((T1i - T2i) - (T1o - T2o));
	Q = W1*C1*(T1i - T1o);
	A = Q / U*LMTD;
	printf("\n\n===============\nOutlet tempertare for Second fluid= %f \t LMTD= %f \t Q= %f \t A= %f \n\n===============\n",
		T2o, LMTD, Q, A);
	if (T2o > T2i)
		printf("First fluid<----->Hot\nSecond fluid<----->Cold\n");
	else
		printf("First fluid<----->Cold\nSecond fluid<----->Hot\n");
	////Estimating total price
	///getting needed parameters from the user
	cout<<"Please Choose a pressure range for your heat exchanger."<<endl;
	cout<<"100-300 psig"<<endl<<
	"300-600 psig"<<endl<<
	"600-900 psig"<<endl;

	cin>>PresRange;

	cout<<"Wich material do you choose to build your heat exchanger?"<<endl;
	cout<<"1:\tSS316"<<endl<<
	"2:\tSS304"<<endl<<
	"3:\tSS347"<<endl<<
	"4:\tNickel 200"<<endl<<
	"5:\tMonel 400"<<endl<<
	"6:\tInconel 600"<<endl<<
	"7:\tIncoloy 825"<<endl<<
	"8:\tTitanium"<<endl<<
	"9:\tHastelloy"<<endl;
	cin>>Material;

	cout<<"What type of Heat Exchanger are you designing?"<<endl<<
	"1:\tFixed Head"<<endl<<
	"2:\tKettle Reboiler"<<endl<<
	"3:\tU-Tube"<<endl;
	cin>>Type;

	///Calculating the price
	//changing A's unit to USC
	A = A*10.7639;
	//CB
	double CB=1 ;
	CB=exp(8.551 - 0.30863*log(A) + 0.06811*(log(A))*(log(A)));

	//FD
	double FD=1 ;
	if (Type == 1)
		FD = exp(-1.1156 + 0.0906*(log(A)));
	else if (Type == 2)
		FD = 1.35;
	else if (Type == 3)
		FD = exp(-0.9816 + 0.0830*(log(A)));
	else
		cout<<"Please Enter a valid Type and rerun the program.";

	//FP
	double FP=1;
	if ( PresRange== 1)
		FP = 0.7771 + 0.04981*log(A);
	else if (PresRange == 2)
		FP = 1.0305 + 0.07140*log(A);
	else if (PresRange == 3)
		FP = 1.14 + 0.12088*log(A);
	else
		cout<<"Please Enter a valid PresRange and rerun the program.";

	//FM
	double FM=1;
	if ( Material== 1)
		FM =0.8608 + 0.23296*log(A);
	else if (Material == 2)
		FM =0.8193 + 0.15984*log(A);
	else if (Material == 3)
		FM =0.6116 + 0.22186*log(A);
	else if (Material == 4)
		FM =1.5092 + 0.60859*log(A);
	else if (Material == 5)
		FM =1.2989 + 0.43377*log(A);
	else if (Material == 6)
		FM =1.2040 + 0.50764*log(A);
	else if (Material == 7)
		FM =1.1854 + 0.49706*log(A);
	else if (Material == 8)
		FM =1.5420 + 0.42913*log(A);
	else if (Material == 9)
		FM =0.1549 + 1.51774*log(A);
	else
		cout<<"Please Enter a valid Material and rerun the program.";

	///Heat-Exchanger Cost
	//CE
	float CE;
	CE = CB*FP*FD*FM;
	//cout<<"c= "<<CE;
	printf("\n===============\nTotal cost is CE= %f \n===============\n",CE);
	////Estimating the pipe's geometrical characteristic parameters
	///Getting the needed Data from the user
	double Lp=1;
	int ND = 1;
	double RD = 1;
	cout << "Please enter the length of the pipe" << endl;
	cin >> Lp;
	cout << "Please choose the nominal Diameter for the pipe" << endl <<
		"1:\t1/8" <<endl<<
		"2:\t2/8" << endl <<
		"3:\t3/8" << endl <<
		"4:\t4/8" << endl <<
		"5:\t1" << endl <<
		"6:\t1.1/4" << endl <<
		"7:\t1.1/2" << endl <<
		"8:\t2" << endl <<
		"9:\t2.1/2" << endl <<
		"10:\t3"<<endl;
	cin >> ND;
	if (ND == 1)
		RD = 0.405;
	else if (ND == 2)
		RD = 0.540;
	else if (ND == 3)
		RD = 0.675;
	else if (ND == 4)
		RD = 0.840;
	else if (ND == 5)
		RD = 1.315;
	else if (ND == 6)
		RD = 1.66;
	else if (ND == 7)
		RD = 1.9;
	else if (ND == 8)
		RD = 2.375;
	else if (ND == 9)
		RD = 2.875;
	else if (ND == 10)
		RD = 3.5;
	else
		cout << "please enter a valid ND and rerun the program." << endl;
	///calculations
	
	double ns;
	ns =ceil( A / (RD*Lp*3.1415));
	cout << "\n=========\nNumber of pipes in the Heat Exchanger is\nNp=\t " << ns << "\n===Thank you, by!======\n";
	_getch();
	return 0;
}

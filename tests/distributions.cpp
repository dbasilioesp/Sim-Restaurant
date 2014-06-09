#include <iostream>
#include <cmath>

#include "Random.h"

using namespace std;



int distributions_main(){
	
	int limitFirstClass = 0;
	int limitMedia = 0;
	int limitInf = 0;
	int limitSup = 0;
	double media = 0;
	int classSize = 8;
	int classNumber = 8;
	int * frequency = new int[classSize];
	int totalFrequency = 100;
	int totalFrequencyMedia = 0;
	int classIndex = 0;
	double df = 0;	// Graus de Liberdade 
	double e = 0;
	double o = 0;
	int libertyDegrees = 0;
	int uniformEstimator = 0;
	int exponencialEstimator = 1;
	int normalEstimator = 2;

	// Generate frequency array

	Random yrandom(3);

	for (int i = 0; i < classSize; i++){
		frequency[i] = 0;
	}

    for (int i = 0; i < totalFrequency; i++)
	{
		//int number = yrandom.uniformRandom(0, 64);
		//int number = yrandom.exponencial(5);
		int number = yrandom.normal(32, 12);
		classIndex = number % classSize;
		frequency[classIndex] += 1;
	}

	for (int i = 0; i < classSize; i++){
		cout << i << ": " << frequency[i] << endl;
	}
	cout << endl;

	// Calculate media

	for (int i = 0; i < classSize; i++){

		limitInf = i * classSize;
		limitSup = (i + 1) * classSize;
		limitMedia = (limitInf + limitSup) / 2;

		totalFrequencyMedia += limitMedia * frequency[i];
	}

	media = totalFrequencyMedia / totalFrequency;
	
	// Calculate uniform df

	e = totalFrequency / classNumber;
	libertyDegrees = classNumber - exponencialEstimator - 1;

	for (int i = 0; i < classSize; i++){
		o = frequency[i] - e;
		df += (o * o) / e;
	}

	// Result

	cout << "Graus de Liberdade: " << libertyDegrees << endl;
	cout << "Porcentagem Esperada 0.975 97.5%" << endl;
	cout << "Qui-quadrada Esperada: 1.69" << endl;
	cout << "Qui-quadrada Obtida: " << df << endl;
	cout << endl;

	system("PAUSE");
	return 0;
}
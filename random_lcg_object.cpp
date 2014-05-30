#include "stdafx.h"

#include <iostream>

using namespace std;

int seed = 4294967291;
int last_random = seed;
int first_random;
const int module = seed;
const int constantMultiple = 7777;
const int constantAditive = 8888;


double randomLCG()
{
	last_random = (constantMultiple * last_random + constantAditive) % module;
	return last_random/seed;
}

double normal(int media, int dp)
{
	double u1, u2, v1, v2, w, y, x1;
	u1 = randomLCG();
	u2 = randomLCG();
	v1 = 2 * u1 - 1;
	v2 = 2 * u2 - 1;
	w = (v1*v1) + (v2*v2);
	y = sqrt((-2*log(w))/w);
	x1 = v1 * y;
	return media + x1 * dp;
}

double exponencial(int media)
{
	return (-media * log(1 - randomLCG()));
}


double uniformRandom(double init, double final)
{
	return init + (randomLCG() * (final - init));
}


int main(){

	first_random = randomLCG();

	for (int i = 0; i < 1000; i++)
	{
		cout << randomLCG() << endl;

		if(first_random == last_random){
			cout << "Cicle in " << i << endl;
			break;
		}
	}

	system("PAUSE");
	return 0;
}
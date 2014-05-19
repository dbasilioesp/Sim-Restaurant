#include "stdafx.h"

#include <iostream>

using namespace std;

int seed = 6733;
int last_random = seed;
int first_random;
const int module = seed;
const int constantMultiple = 7777;
const int constantAditive = 8888;


int randomLCG(){
	last_random = (constantMultiple * last_random + constantAditive) % module;
	return last_random;
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
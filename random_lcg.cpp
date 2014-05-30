#include <iostream>
#include <cmath>

using namespace std;


int firstRandom;
// int seed = 110;
// int lastRandom = seed;
// const int module = 2^32;
// const int constantMultiple = 1664525;
// const int constantAditive = 1013904223;
int seed = 3;
int lastRandom = seed;
const int module = 64;
const int constantMultiple = 21;
const int constantAditive = 1;

int randomCalc(){
    lastRandom = (constantMultiple * lastRandom + constantAditive) % module;
    return lastRandom;
}

double randomLCG(){
    int calc = randomCalc();
    return ((double) calc/(module-1));
}


int main(){

	for (int i = 0; i < 100; i++)
	{
		//cout << randomCalc() << endl;

		// if(firstRandom == lastRandom){
		// 	cout << "Cicle in " << i << endl;
		// 	break;
		// }
	}

    cout << uniformRandom(7, 10);

	return 0;
}
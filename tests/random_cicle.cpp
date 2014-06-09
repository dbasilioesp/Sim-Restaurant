#include <iostream>

using namespace std;

int last_random = NULL;

double randomLCG(){

	int seed = 4294967291;	
	const int module = seed;
	const int constantMultiple = 7777;
	const int constantAditive = 8888;

	if(last_random == NULL)
		last_random = seed;

	last_random = (constantMultiple * last_random + constantAditive) % module;
	return last_random/seed;
}


int random_cicle_cmain(){

	int first_random;
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
#pragma once
#include <iostream>
#include <cmath>
#include <mutex>

using namespace std;


class Random {

	private:

	int seed;
	int lastRandom;
	int module;
	int constantMultiple;
	int constantAditive;
	int number;
	mutex randomMutex;

	public:

	Random::Random(int _seed){
		seed = _seed;
		lastRandom = seed;
		module = 64;
		constantMultiple = 21;
		constantAditive = 1;
	}

	int randomCalc(){
		randomMutex.lock();
			lastRandom = (constantMultiple * lastRandom + constantAditive) % module;
		randomMutex.unlock();
		return lastRandom;
	}

	double randomLCG(){
		int calc = randomCalc();
		return ((double) calc/(module-1));
	}

	int uniform(int init, int final){
		number = init + (randomLCG() * (final - init));
		return number;
	}

	int exponencial(int media){
		number = (-media * log(1 - randomLCG()));
		return number;
	}

	unsigned int normal(int media, int dp){
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
};

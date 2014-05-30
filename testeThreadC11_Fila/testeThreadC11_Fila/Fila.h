#pragma once
#include <queue>
#include "Carro.h"
#include <mutex>

using namespace std;

class Fila
{
	queue <Carro *> fila;
	mutex queueMutex;

public:
	Fila();
	~Fila();
	void insert(Carro *c);
	Carro* getFirst();
	bool isEmpty();

};


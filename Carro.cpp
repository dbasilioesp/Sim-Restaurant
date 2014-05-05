#include "stdafx.h"
#include "Carro.h"


Carro::Carro( int i)
{
	id = i;
}


Carro::~Carro()
{
}

int Carro::getId(){
	return id;
}
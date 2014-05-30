#include "stdafx.h"
#include "Carro.h"
#include <iostream>
using namespace std;

Carro::Carro(int placa)
{
	this->placa = placa;
}

Carro::Carro()
{
}
Carro::~Carro()
{
	std::cout << "destruct " << this->placa << std::endl;
}

void Carro::setPlaca(int pla){
	placa = pla;
}

int Carro::getPlaca(){
	return placa;
}
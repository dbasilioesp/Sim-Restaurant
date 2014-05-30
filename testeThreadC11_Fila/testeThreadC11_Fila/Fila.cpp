#include "stdafx.h"
#include <exception>
#include <iostream>
#include <mutex>
#include "Fila.h"


Fila::Fila()
{}
Fila::~Fila()
{}

void Fila::insert(Carro *c){
	queueMutex.lock();
	 fila.push(c);
	queueMutex.unlock();
}
Carro* Fila::getFirst(){
	Carro *c = NULL;
	
       queueMutex.lock();
	   if (!fila.empty()){
			c = fila.front();
			fila.pop();
	   }	
       queueMutex.unlock();
	return c;
}

bool Fila::isEmpty(){
	return fila.empty();
}
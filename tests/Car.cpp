#include "Car.h"


Car::Car( int i)
{
	id = i;
}


Car::~Car()
{
}

int Car::getId(){
	return id;
}
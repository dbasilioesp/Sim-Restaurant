#include "Client.h"


Client::Client(int i)
{
	id = i;
}


Client::~Client(void)
{
}


int Client::getId(){
	return id;
}


void Client::setGroup(int i){
	group = i;
}


int Client::getGroup(){
	return group;
}


void Client::setServed(bool s){
	served = s;
}


bool Client::isServed(){
	return served;
}
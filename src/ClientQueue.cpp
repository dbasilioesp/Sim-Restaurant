#include <exception>
#include "ClientQueue.h"
#include <iostream>

ClientQueue::ClientQueue(void)
{
}


ClientQueue::~ClientQueue(void)
{
}

void ClientQueue::insert(Client *client){
	queueMutex.lock();
		queueClient.push(client);
	queueMutex.unlock();
}

Client* ClientQueue::getFirst(){
	Client *client = NULL;
	
    queueMutex.lock();
	if (!queueClient.empty()){
		client = queueClient.front();
		queueClient.pop();
	}	
    queueMutex.unlock();
	
	return client;
}

bool ClientQueue::isEmpty(){
	return queueClient.empty();
}


int ClientQueue::size(){
	return queueClient.size();
}

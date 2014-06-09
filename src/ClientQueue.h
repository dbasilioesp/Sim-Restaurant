#pragma once
#include <queue>
#include <mutex>

#include "Client.h"

using namespace std;


class ClientQueue
{
	queue <Client *> queueClient;
	mutex queueMutex;
public:
	ClientQueue(void);
	~ClientQueue(void);
	
	void insert(Client *g);
	Client* getFirst();
	bool isEmpty();
	int size();
};

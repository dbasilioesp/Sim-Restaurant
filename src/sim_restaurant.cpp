#pragma once
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>
#include <queue>
#include <future>

#include "Random.h"
#include "ClientQueue.h"

using namespace std;
using namespace chrono;

mutex mu;
time_point<system_clock, system_clock::duration> initialTime;
ClientQueue cozinha;
int mesasOcupadas = 0;
int balcaoOcupado = 0;
int cozinheirosOcupados = 0;
int totalClients = 0;
int totalExited = 0;
int counter = 0;

long getClock(){
	return duration_cast<seconds>(system_clock::now() - initialTime).count();
}

void dashboard(int endTime, ClientQueue *cq1, ClientQueue *cq2, ClientQueue *balcao, ClientQueue *mesas){

	char letter;
	long interval;

	while(getClock() < endTime){
		system("cls");

		cout << "Sim Restaurant" << endl;
		cout << "--------------" << endl;
		cout << "Time: " << getClock() << endl << endl;
		
		cout << "Fila Caixa 1: ";
		for (int i = 0; i < cq1->size(); i++)
			cout << "|";
		cout << endl;

		cout << "Fila Caixa 2: ";
		for (int i = 0; i < cq2->size(); i++)
			cout << "|";
		cout << endl;

		cout << "Fila Balcao: ";
		for (int i = 0; i < balcao->size(); i++)
			cout << "|";
		cout << endl;

		cout << "Fila Mesas: ";
		for (int i = 0; i < mesas->size(); i++)
			cout << "|";
		cout << endl;

		cout << "Fila Cozinha: ";
		for (int i = 0; i < cozinha.size(); i++)
			cout << "|";
		cout << endl << endl;
		
		cout << "Balcao: ";
		for (int i = 0; i < balcaoOcupado; i++)
			cout << "|";
		cout << endl;

		cout << "Mesas: ";
		for (int i = 0; i < mesasOcupadas; i++)
			cout << "|";
		cout << endl;

		cout << "Cozinha: ";
		for (int i = 0; i < cozinheirosOcupados; i++)
			cout << "|";
		cout << endl;

		this_thread::sleep_for(seconds(1)); 
	}

}


void prapareFood(int waitTime, int * placesFilled, Client *client){
	this_thread::sleep_for(seconds(waitTime));
	mu.lock();
		*placesFilled -= 1;
		client->setServed(true);
	mu.unlock();
}


void kitchen(int endTime, int maxPlaces, int * placesFilled, ClientQueue *clientQueue){
	int waitTime;
	Random randomWait(250);
	Client* client = NULL;

	while (getClock() < endTime){
        
		if (clientQueue->isEmpty() == false && *placesFilled < maxPlaces){
			
			mu.lock();
				if(*placesFilled < maxPlaces){
					client = clientQueue->getFirst();
				}
			mu.unlock();
			
			if (client != NULL){
				mu.lock();
					*placesFilled += 1;
				mu.unlock();

				waitTime = randomWait.normal(14, 5);
				async(launch::async, &prapareFood, waitTime, placesFilled, client);

				client = NULL;
			}

		}         
		
	}

}


void waitToBeServed(int waitTime, int * placesFilled, Client *client){

	while (!client->isServed())
	{
		this_thread::sleep_for(seconds(1));
	}

	this_thread::sleep_for(seconds(waitTime));
	mu.lock();
		*placesFilled -= 1;
		totalExited++;
	mu.unlock();
}


void receiveClientInPlaces(int endTime, int maxPlaces, int * placesFilled, ClientQueue *clientQueue){

	int waitTime;
	Random randomWait(50);
	Client* client = NULL;

	
	while (getClock() < endTime){
        
		if (clientQueue->isEmpty() == false && *placesFilled < maxPlaces){
			
			mu.lock();
				if(*placesFilled < maxPlaces){
					client = clientQueue->getFirst();
				}
			mu.unlock();
			
			if (client != NULL){
				mu.lock();
					*placesFilled += 1;
				mu.unlock();

				waitTime = randomWait.normal(20, 8);
				async(launch::async, &waitToBeServed, waitTime, placesFilled, client);

				client = NULL;
			}

		}         
		
	}

}


void receiveClientQueue(int endTime, ClientQueue *clientQueue, ClientQueue *balcao, ClientQueue *mesas){

	int waitTime;
	Random randomWait(50);
	Client* client = NULL;
	
	while (getClock() < endTime){   
        
		if (clientQueue->isEmpty() == false){
					
			client = clientQueue->getFirst();
			
			if (client != NULL){
				waitTime = randomWait.normal(8, 2);
				this_thread::sleep_for(seconds(waitTime));

				if(client->getGroup() == 1){
					balcao->insert(client);
				} else {
					mesas->insert(client);
				}

				cozinha.insert(client);
				
				client = NULL;
			}
		}         
		
	}

}


void produceClients(int endTime, ClientQueue *cq1, ClientQueue *cq2){
	
	int waitTime;
	Random randomWait(55);
	Random randomClient(105);

	while(getClock() < endTime){

		waitTime = randomWait.exponencial(3);
		this_thread::sleep_for(seconds(waitTime));

		int clientSize = randomClient.uniform(1, 4);
		
		mu.lock();
			counter++;
			Client * client = new Client(counter);
		mu.unlock();
		
		client->setGroup(clientSize);

		mu.lock();
			if(cq1->size() < cq2->size()){
				cq1->insert(client);
			} else {
				cq2->insert(client);
			}
			totalClients++;
		mu.unlock();

	}

}


int main()
{
	int finishTime = 60;
	ClientQueue cq1, cq2, balcao, mesas;
	initialTime = chrono::system_clock::now();
	
	thread t1(produceClients, 30, &cq1, &cq2);
	thread t2(receiveClientQueue, finishTime, &cq1, &balcao, &mesas);
	thread t3(receiveClientQueue, finishTime, &cq2, &balcao, &mesas);
	thread t4(receiveClientInPlaces, finishTime, 3, &mesasOcupadas, &mesas);
	thread t5(receiveClientInPlaces, finishTime, 4, &balcaoOcupado, &balcao);
	thread t6(kitchen, finishTime, 3, &cozinheirosOcupados, &cozinha);
	thread t99(dashboard, finishTime, &cq1, &cq2, &balcao, &mesas);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t99.join();

	cout << endl << "Time: " << getClock() << " seconds" << endl;
	cout << "Total Clients: " << totalClients << endl;
	cout << "Total Exited: " << totalExited << endl;
	cout << "Finishing... " << endl;

	system("PAUSE");
	return 0;
}


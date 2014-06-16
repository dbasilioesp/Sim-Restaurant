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


struct ThreadParameters {
	int tablesFilled;
	int balconyFilled;
	int chefsWorking;
	int totalClients;
	int totalExited;
	int counter;
	int maxTables;
	int maxBalconies;
	int maxChefs;
	int money;
};


struct ClientsController {
	ClientQueue cq1;
	ClientQueue cq2;
	ClientQueue balconies;
	ClientQueue tables;
	ClientQueue kitchen;
};

mutex mu;
time_point<system_clock, system_clock::duration> initialTime;


long getClock(){
	return duration_cast<seconds>(system_clock::now() - initialTime).count();
}


void store(ThreadParameters * parameters){

	int money = parameters->money;
	char option;
	while (true)
	{
		system("cls");
		cout << "Sim Restaurant" << endl;
		cout << "--------------" << endl;
		
		cout << "Money: " << money << "\t" << "Tables: " << parameters->maxTables << "\t" << "Balconies: " << parameters->maxBalconies;
		cout << "\t" << "Chefs: " << parameters->maxChefs << endl;

		cout << endl << "1 - More Tables (100)" << endl;
		cout << "2 - More Balconies (50)" << endl;
		cout << "3 - More Chefs (150)" << endl;
		cout << "4 - Start Game" << endl;

		cout << endl << "Option: ";
		cin >> option;

		if(option == '1'){
			if(money - 100 < 0){
				cout << "Not enough cash!" << endl;
				system("pause");
			} else {
				money -= 100;
				parameters->maxTables += 1;
			}
		} else if(option == '2'){
			if(money - 50 < 0){
				cout << "Not enough cash!" << endl;
				system("pause");
			} else {
				money -= 50;
				parameters->maxBalconies += 1;
			}
		} else if(option == '3'){
			if(money - 150 < 0){
				cout << "Not enough cash!" << endl;
				system("pause");
			} else {
				money -= 150;
				parameters->maxChefs += 1;
			}
		}

		if(option == '4')
			break;
	}
	
	parameters->money = money;

}


void dashboard(int endTime, ThreadParameters* tp, ClientsController* controller){

	char letter;
	long interval;

	while(getClock() < endTime){
		system("cls");

		cout << "Sim Restaurant" << endl;
		cout << "--------------" << endl;

		cout << "Money: " << tp->money << "\t" << "Tables: " << tp->maxTables << "\t" << "Balconies: " << tp->maxBalconies;
		cout << "\t" << "Chefs: " << tp->maxChefs << endl;

		cout << "Time: " << getClock() << endl << endl;
		
		cout << "Box 1: ";
		for (int i = 0; i < controller->cq1.size(); i++)
			cout << "|";
		cout << endl;

		cout << "Box 2: ";
		for (int i = 0; i < controller->cq2.size(); i++)
			cout << "|";
		cout << endl;

		cout << "Fila Balconies: ";
		for (int i = 0; i < controller->balconies.size(); i++)
			cout << "|";
		cout << endl;

		cout << "Fila Tables: ";
		for (int i = 0; i < controller->tables.size(); i++)
			cout << "|";
		cout << endl;

		cout << "Fila Kitchen: ";
		for (int i = 0; i < controller->kitchen.size(); i++)
			cout << "|";
		cout << endl << endl;
		
		cout << "Balconies: ";
		for (int i = 0; i < tp->balconyFilled; i++)
			cout << "|";
		cout << endl;

		cout << "Tables: ";
		for (int i = 0; i < tp->tablesFilled; i++)
			cout << "|";
		cout << endl;

		cout << "Kitchen: ";
		for (int i = 0; i < tp->chefsWorking; i++)
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


void receiveFoodRequest(int endTime, int * maxPlaces, int * placesFilled, ClientQueue *clientQueue){
	
	int waitTime;
	Random randomWait(250);
	Client* client = NULL;

	while (getClock() < endTime){
        
		if (clientQueue->isEmpty() == false && *placesFilled < *maxPlaces){
			
			mu.lock();
				if(*placesFilled < *maxPlaces){
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


void waitToBeServed(int waitTime, ThreadParameters* tp, int * placesFilled, Client *client){

	while (!client->isServed())
	{
		this_thread::sleep_for(seconds(1));
	}

	this_thread::sleep_for(seconds(waitTime));
	mu.lock();
		*placesFilled -= 1;
		tp->totalExited++;
	mu.unlock();
}


void receiveClientInPlaces(int endTime, ThreadParameters* tp, int * maxPlaces, int * placesFilled, ClientQueue *clientQueue){

	int waitTime;
	Random randomWait(50);
	Client* client = NULL;

	
	while (getClock() < endTime){
        
		if (clientQueue->isEmpty() == false && *placesFilled < *maxPlaces){
			
			mu.lock();
				if(*placesFilled < *maxPlaces){
					client = clientQueue->getFirst();
				}
			mu.unlock();
			
			if (client != NULL){
				mu.lock();
					*placesFilled += 1;
				mu.unlock();

				waitTime = randomWait.normal(20, 8);
				async(launch::async, &waitToBeServed, waitTime, tp, placesFilled, client);

				client = NULL;
			}

		}         
		
	}

}


void receiveClientQueue(int endTime, ClientQueue *cq, ClientQueue *balcony, ClientQueue *tables, ClientQueue *kitchen){

	int waitTime;
	Random randomWait(50);
	Client* client = NULL;
	
	while (getClock() < endTime){   
        
		if (cq->isEmpty() == false){
					
			client = cq->getFirst();
			
			if (client != NULL){
				waitTime = randomWait.normal(8, 2);
				this_thread::sleep_for(seconds(waitTime));

				kitchen->insert(client);

				if(client->getGroup() == 1){
					balcony->insert(client);
				} else {
					tables->insert(client);
				}
				
				client = NULL;
			}
		}         
		
	}

}


void produceClients(int endTime, ThreadParameters* tp, ClientQueue *cq1, ClientQueue *cq2){
	
	int waitTime;
	Random randomWait(55);
	Random randomClient(105);

	while(getClock() < endTime){

		waitTime = randomWait.exponencial(3);
		this_thread::sleep_for(seconds(waitTime));

		int clientSize = randomClient.uniform(1, 4);
		
		mu.lock();
			tp->counter++;
			Client * client = new Client(tp->counter);
		mu.unlock();
		
		client->setGroup(clientSize);

		mu.lock();
			if(cq2->size() < cq1->size()){
				cq2->insert(client);
			} else {
				cq1->insert(client);
			}
			tp->totalClients++;
		mu.unlock();

	}

}


int main()
{
	ThreadParameters parameters;
	parameters.tablesFilled = 0;
	parameters.balconyFilled = 0;
	parameters.chefsWorking = 0;
	parameters.totalClients = 0;
	parameters.totalExited = 0;
	parameters.counter = 0;
	parameters.maxTables = 1;
	parameters.maxBalconies = 1;
	parameters.maxChefs = 1;
	parameters.money = 800;
	
	store(&parameters);

	int endTime = 60;
	
	ClientsController controller;

	initialTime = chrono::system_clock::now();
	
	thread t1(produceClients, 30, &parameters, &controller.cq1, &controller.cq2);

	thread t2(receiveClientQueue, endTime, &controller.cq1, &controller.balconies, &controller.tables, &controller.kitchen);
	thread t3(receiveClientQueue, endTime, &controller.cq2, &controller.balconies, &controller.tables, &controller.kitchen);

	thread t4(receiveClientInPlaces, endTime, &parameters, &parameters.maxTables, &parameters.tablesFilled, &controller.tables);
	thread t5(receiveClientInPlaces, endTime, &parameters, &parameters.maxBalconies, &parameters.balconyFilled, &controller.balconies);
	thread t6(receiveFoodRequest, endTime, &parameters.maxChefs, &parameters.chefsWorking, &controller.kitchen);

	thread t99(dashboard, endTime, &parameters, &controller);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t99.join();

	cout << endl << "Time: " << getClock() << " seconds" << endl;
	cout << "Total Clients: " << parameters.totalClients << endl;
	cout << "Total Exited: " << parameters.totalExited << endl;
	cout << "Finishing... " << endl;

	system("PAUSE");
	return 0;
}

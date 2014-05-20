#include "stdafx.h"

// testeThreadsC11.cpp : Defines the entry point for the console application.

#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>
#include <queue>

using namespace std;
using namespace chrono;

struct Car {
	int id;
};

mutex mu;
time_point<system_clock, system_clock::duration> initialTime;
queue<Car> cars;

const int MAX_GASPOINT_RECEIVERS = 4;
int gaspoint_receivers = MAX_GASPOINT_RECEIVERS;
bool generator_notified = false;

void consumerGasPoint(){
	
	cout << "Initializing gas point consumer" <<  endl;

	while(!generator_notified || !cars.empty()){

		this_thread::sleep_for(seconds(3));
		if(!cars.empty()){
			cars.pop();
		}
	}

}


void producerCars(){

	cout << "Initializing generator of cars" <<  endl;

	for (int i = 1; i <= 1; i++){
		Car car;
		car.id = i;
		cars.push(car);
		this_thread::sleep_for(seconds(2));
	}

	generator_notified = true;
}

int main(int argc, char* argv[])
{
	cout << "Gas Point" << endl;
	cout << "---------" << endl << endl;

	initialTime = ::system_clock::now();
	
	thread thread_producer_cars(producerCars);
	thread thread_gaspoint_consumer(consumerGasPoint);

	thread_producer_cars.join();
	thread_gaspoint_consumer.join();
	
	auto end = ::system_clock::now();
	auto interval = end - initialTime;

	cout << endl << "Time: " << duration_cast<::seconds>(interval).count() << " seconds" << endl;
	cout << "Finishing... " << endl;

	system("PAUSE");
	return 0;
}


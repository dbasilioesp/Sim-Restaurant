#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>
#include <queue>

#include "Random.h"

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
int producedCars = 0;
int consumedCars = 0;
int generators = 1;
int consumers = 2;
long * consumersInterval = new long[consumers];
Random random(5);

long getIntervalTime(){
	auto end = ::system_clock::now();
	auto interval = end - initialTime;
	return duration_cast<::seconds>(interval).count();
}

void printer(){

	char letter;
	long interval;

	while(generators > 0 || consumers > 0){
		system("cls");
		interval =  getIntervalTime();

		cout << "Gas Point" << endl;
		cout << "---------" << endl;
		cout << "Time: " << interval << endl << endl;
		
		cout << "Released Cars: " << producedCars << endl;
		cout << "Consumed Cars: " << consumedCars << endl;
		cout << "Queue Cars: " << cars.size() << endl;

		cout << endl;
		for (int i = 0; i < consumers; i++){
			cout  << "Consumer " << i << ": " << consumersInterval[i] - interval << endl;
		}
		
		this_thread::sleep_for(seconds(1));
	}

}

void consumerGasPoint(int id){
	
	//cout << " [Initializing gas point consumer " << id <<  "]" << endl;

	while(generators > 0){
		while(!cars.empty()){
			mu.lock();
			if(!cars.empty()){
				cars.pop();
				consumedCars++;
			}
			mu.unlock();

			auto time = seconds(random.normal(5, 1));
			consumersInterval[id-1] = getIntervalTime() + duration_cast<::seconds>(time).count();
			this_thread::sleep_for(time);
		}
	}
	
	mu.lock();
		consumers--;
	mu.unlock();

	//cout << " [End gas point consumer " << id << "] " << endl;
}


void producerCars(){

	//cout << "Initializing generator of cars " <<  endl;
	int clock = 0;
	
	while(clock < 8){
		Car car;
		mu.lock();
			cars.push(car);
			producedCars++;
		mu.unlock();
		this_thread::sleep_for(seconds(1));
		clock += 1;
	}

	mu.lock();
		generators--;
	mu.unlock();
}

int main(int argc, char* argv[])
{
	vector<thread> threads;
	initialTime = ::system_clock::now();

	for (int i = 0; i < consumers; i++){
		consumersInterval[i] = 0;
	}
	
	thread threadProducerCars(producerCars);	
	for (int i = 0; i < consumers; i++)
		threads.push_back(thread(consumerGasPoint, i+1));
	thread threadPrinter(printer);

	threadProducerCars.join();
	for (auto& thread : threads)
		thread.join();
	threadPrinter.join();
	
	auto end = ::system_clock::now();
	auto interval = end - initialTime;

	cout << endl << "Time: " << duration_cast<::seconds>(interval).count() << " seconds" << endl;
	cout << "Finishing... " << endl;

	system("PAUSE");
	return 0;
}


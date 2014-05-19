#include "stdafx.h"

//// testeThreadsC11.cpp : Defines the entry point for the console application.
//
//#include <thread>
//#include <iostream>
//#include <vector>
//#include <chrono>
//#include <mutex>
//
//using namespace std;
//using namespace chrono;
//
//
//
//mutex mu;
//time_point<system_clock, system_clock::duration> initialTime;
//
//const int MAX_RECEIVERS_GASPOINT = 4;
//int receivers_gaspoint = MAX_RECEIVERS_GASPOINT;
//int cntr;
//
//void gasPointReceiver(int i){
//	
//	cout << "receiving " << i <<  endl;
//	
//	this_thread::sleep_for(seconds(4));
//	
//	cout << "leaving " << i << endl;
//}
//
//void generator(int id){
//
//	vector<thread> threads;
//
//	cout << "Initializing generator: " << id << endl;
//	cout << "Thread Id:" << this_thread::get_id() << endl;
//
//	mu.lock();
//	cntr++;
//	mu.unlock();
//
//	for (int x = 0; x < 3; x++){
//
//		if(receivers_gaspoint > 0){
//
//			mu.lock();
//			threads.push_back(thread(gasPointReceiver, receivers_gaspoint));
//			receivers_gaspoint--;
//			mu.unlock();
//
//			this_thread::sleep_for(seconds(3));
//		}
//	}
//
//	for (auto& thread : threads){
//		thread.join();
//	}
//}
//
//int main(int argc, char* argv[])
//{
//	cout << "Gas Point" << endl;
//	cout << "---------" << endl << endl;
//
//	cntr = 0;
//	initialTime = ::system_clock::now();
//	
//	thread t1(generator, 1);
//	thread t2(generator, 2);
//	t1.join();
//	t2.join();
//
//	auto end = ::system_clock::now();
//	auto interval = end - initialTime;
//
//	cout << endl << "Time: " << duration_cast<::seconds>(interval).count() << " seconds" << endl;
//	cout << "Finishing... " << endl;
//
//	system("PAUSE");
//	return 0;
//}
//

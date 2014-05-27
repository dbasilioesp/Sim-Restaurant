#include "stdafx.h"

//#include <iostream>
//#include <thread>
//#include <condition_variable>
//#include <mutex>
//
//using namespace std;
//
//
//condition_variable cond_var;
//mutex m;
//
//
//int main(){
//
//	int value = 100;
//	bool notified = false;
//
//	thread reporter([&](){
//
//		unique_lock<mutex> lock(m);
//		while(!notified) {
//			cond_var.wait(lock);
//		}
//
//		cout << "The value is " << value << endl;
//
//	});
//
//	thread assigner([&](){
//		value = 20;
//
//		notified = true;
//		cond_var.notify_one();
//	});
//
//	reporter.join();
//	assigner.join();
//
//	system("PAUSE");
//	return 0;
//}
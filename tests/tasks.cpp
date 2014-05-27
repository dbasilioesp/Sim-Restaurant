#include "stdafx.h"

//#include <iostream>
//#include <future>
//#include <chrono>
//
//using namespace std;
//
//
//int square(int x) {
//	cout << "Thread Id: " << this_thread::get_id() << endl;
//	this_thread::sleep_for(chrono::milliseconds(100));
//	cout << x << endl;
//	return x * x;
//}
//
//
//int main(){
//
//	auto a = async(launch::async, &square, 10);
//	auto b = async(launch::async, &square, 20);
//	int v = a.get();
//	v += b.get();
//
//	cout << "The thread returned " << v << endl;
//
//	system("PAUSE");
//	return 0;
//}
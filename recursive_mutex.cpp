#include "stdafx.h"

//#include <thread>
//#include <mutex>
//#include <iostream>
//
//
//struct Complex {
//	std::recursive_mutex mutex;
//	int i;
//
//	Complex() : i(0) {}
//
//	void mul(int x) {
//		std::lock_guard<std::recursive_mutex> lock(mutex);
//		i *= x;
//	}
//
//	void div(int x){
//		std::lock_guard<std::recursive_mutex> lock(mutex);
//		i /= x;
//	}
//
//	void both(int x, int y) {
//		std::lock_guard<std::recursive_mutex> lock(mutex);
//
//		i = 100;
//
//		mul(x);
//		div(y);
//
//		std::cout << i << std::endl;
//	}
//};
//
//
//int main(int argc, char* argv[])
//{
//	Complex complex;
//	complex.both(32, 23);
//
//	std::cout << "..." << std::endl;
//
//	system("PAUSE");
//	return 0;
//}
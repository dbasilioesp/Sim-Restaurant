#include "stdafx.h"

//#include <iostream>
//#include <vector>
//#include <thread>
//#include <atomic>
//
//using namespace std;
//
//// int accum = 0;
//atomic<int> accum = 0;
//
//
//void atomicSquare(int x) {
//	accum += x * x;
//}
//
////void square(int& accum, int x) {
////	accum += x * x;
////}
//
//int main(){
//
//	vector<thread> threads;
//
//	for (int i = 1; i <= 1000; i++){
//		threads.push_back(thread(&atomicSquare, i));
//	}
//
//	for (auto& th : threads){
//		th.join();
//	}
//
//	cout << "accum = " << accum << endl;
//
//	system("PAUSE");
//	return 0;
//}
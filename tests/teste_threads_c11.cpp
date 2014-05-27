#include "stdafx.h"

// testeThreadsC11.cpp : Defines the entry point for the console application.
//
//#include <thread>
//#include <iostream>
//#include <vector>
//#include <chrono>
//#include <mutex>
//
//std::mutex mu;
//std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration> tempoInicial;
//int cntr;
//
//void atende(int i){
//	std::cout << "atendendo " << i <<  std::endl;
//	std::this_thread::sleep_for(std::chrono::seconds(2));
//	std::cout << "liberando " << i << std::endl;
//}
//
//void gerador(int id){
//
//	std::vector<std::thread> threads;
//
//	std::cout << "disparando gerador " << id << std::endl;
//	std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
//
//	mu.lock();
//	cntr++;
//	mu.unlock();
//
//	for (int x = 0; x < 5; x++){
//		threads.push_back(std::thread(atende, x));
//		std::this_thread::sleep_for(std::chrono::seconds(3));
//	}
//
//	for (auto& thread : threads){
//		thread.join();
//	}
//}
//
//int _main(int argc, char* argv[])
//{
//
//	tempoInicial = std::chrono::system_clock::now();
//	cntr = 0;
//
//	std::thread t1(gerador, 1);
//	std::thread t2(gerador, 2);
//	t1.join();
//	t2.join();
//
//	auto end = std::chrono::system_clock::now();
//	auto dur = end - tempoInicial;
//
//	std::cout << "encerrando... " << std::chrono::duration_cast<std::chrono::seconds>(dur).count() << std::endl;
//
//	return 0;
//}
//

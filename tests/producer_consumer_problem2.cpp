#include <iostream>
#include <future>
#include <chrono>
#include <queue>

using namespace std;

int c = 0;
queue<int> goods;

void producer(){
	for (int i = 0; i < 500; ++i) {
		goods.push(i);
		c++;
	}
}


void consumer(){
	while(!goods.empty()){
		goods.pop();
		c--;
	}
}

int pcp2_main(){

	auto thread_producer = async(launch::async, &producer);
	auto thread_consumer = async(launch::async, &consumer);

	thread_producer.get();
	thread_consumer.get();
	

	cout << "Net: " << c << endl;

	system("PAUSE");
	return 0;
}
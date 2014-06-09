#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>

using namespace std;

condition_variable cond_var;
mutex m;

int pcp_main(){

	int c = 0;
	bool done = false;
	queue<int> goods;

	thread producer([&]() {
		for (int i = 0; i < 500; ++i) {
			goods.push(i);
			c++;
		}

		done = true;
		cond_var.notify_one();
	});

	thread consumer([&](){
		
		unique_lock<mutex> lock(m);
		while(!done){
			cond_var.wait(lock);
		}

		while(!goods.empty()){
			goods.pop();
			c--;
		}
	});

	producer.join();
	consumer.join();

	cout << "Net: " << c << endl;

	system("PAUSE");
	return 0;
}
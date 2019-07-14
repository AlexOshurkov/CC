// cc-7-mt.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

#include <array>
using namespace std;

int num = 0;
mutex mtx;

void func(int p, int b) {
	
	for (int i = 0; i < 1000; i++) {
		lock_guard <mutex> g(mtx);
		num |= (1 << b);
		cout << b << ">> " << num << endl;
		this_thread::sleep_for(chrono::milliseconds(p));
		num &= ~(1 << b);
		cout << b << "<< " << num << endl;
	}

}

int main(int argc, char* argv[])
{

	array <int, 100> a1 = {};
	//a1.fill(0);



	thread t1 = thread(&func, 134, 1);
	thread t2 = thread(&func, 121, 2);
	thread t3 = thread(&func, 151, 3);

	t1.join();
	t2.join();
	return 0;
}


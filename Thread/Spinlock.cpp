#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

using std::atomic;
using std::thread;
using std::vector;

atomic<bool> lock_flag;
vector<thread> threads;

void atomic_unlock() {
	lock_flag.store(false, std::memory_order_seq_cst);
}

bool try_lock() {
	bool expected = false;
	
	return lock_flag.compare_exchange_strong(expected, true, std::memory_order_seq_cst);
}

int main() {
	int size = 0;

	std::cout << "화장실 갯수 입력 : " << std::endl;
	std::cin >> size;

	if (size <= 0) {
		std::cout << "올바른 화장실 갯수를 입력하세요." << std::endl;
		return 1;
	}

	for (int i = 0; i < size; i++)
		threads.emplace_back(atomic_unlock, i);
}
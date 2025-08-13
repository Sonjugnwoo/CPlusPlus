#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using std::vector;
using std::thread;
using std::queue;


std::condition_variable cv; // 스레드 간 신호 전달용 조건변수
std::mutex m;               // 데이터 보호를 위한 mutex
bool done = false;          // 작업 완료 여부 표시 플래그

void worker(int i) {

}

int main() {
	vector<std::thread> bathroom; 
	bathroom.reserve(5);          // 5개까지만 쓴다고 예약

	queue<std::function<void>> job;

	for (int i = 0; i < 5; i++)
		bathroom.emplace_back(worker, i);
}
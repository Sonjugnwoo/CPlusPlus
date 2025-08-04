#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using std::thread;
using std::vector;

//뮤텍스(Mutex)는 여러 스레드가 동시에 접근하는 공유 자원을 한 번에 하나의 스레드만 사용하도록 잠금(lock)하여 동기화를 보장하는 도구입니다
//즉, 상호 배제를 통해 경쟁 상태(race condition)를 방지

void worker(int& result,std::mutex& m) {	
	for (int i = 0; i < 10000; i++) {
		//std::lock_guard<std::mutex> lock(m)  -> lock 생성시에 m.lock 실행   -> scope 를 빠져 나가면 lock 소멸 -> m.unlock 자동 실행 
		m.lock();            // 임계 영역 시작: 뮤텍스를 잠궈 다른 쓰레드 접근 차단
		result += 1;         // 공유 변수 result를 1 증가시키는 작업 (임계 영역)
		m.unlock();          // 임계 영역 끝: 뮤텍스 잠금 해제
	}
	//unlock이 없으면 뮤텍스가 풀리지 않아 모든 쓰레드가 대기 상태에 빠지고, 아무 작업도 못 하는 상황을 데드락이라고 합니다.
}

int main() {
	int counter = 0; 
	vector<thread> workers;
	std::mutex m;		 // 뮤텍스 객체, 공유 변수 보호용

	for (int i = 0; i < 4; i++)
		workers.push_back(thread(worker, std::ref(counter),std::ref(m)));

	for (int i = 0; i < 4; i++)
		workers[i].join();

	std::cout << "Counter 값 : " << counter << std::endl;
}
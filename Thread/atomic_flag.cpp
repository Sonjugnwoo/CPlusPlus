#include <thread>
#include <atomic>
#include <iostream>

std::atomic_flag at;		// atomic_flag는 가장 단순하고 빠른 원자적 락 플래그 타입
int counter = 0;			// 카운터 자원 

void spin_lock() {
	while (at.test_and_set(std::memory_order_seq_cst)) {
		// test_and_set(): 현재 값을 읽고 true로 설정한 뒤 이전 값을 반환
		// - 이전 값이 true면 이미 다른 스레드가 락을 잡고 있는 상태 → 대기
		// - 이전 값이 false면 락이 풀려있었으므로 이 스레드가 락을 잡음
		std::this_thread::sleep_for(std::chrono::microseconds(1));	// CPU 낭비 방지용으로 아주 짧게 sleep (microseconds 단위)
	}
}

void unlock() {
	at.clear(std::memory_order_seq_cst);		//at를 false 로 만들어 락 해제 , 다른 스레드가 spin_lock 시도 가능 
	// clear(): atomic_flag 값을 false로 초기화 → 락 해제
}

void worker(int id) {	// 각 스레드(1, 2)가 5번씩 counter 증가
	for (int i = 0; i < 5; i++) {
		spin_lock();  // 락을 획득할 때까지 반복 시도
		++counter;    // 임계 구역(여러 스레드가 동시에 접근하면 문제되는 부분)
		std::cout << "Thread " << id << " counter: " << counter << "\n";
		unlock();     // 락 해제. 다른 스레드가 진입할 수 있게 함
	}
}



int main() {
	std::thread t1(worker, 1);
	std::thread t2(worker, 2);
	t1.join();
	t2.join();
}
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

/* DeadLock 가이드 라인 (C++) 
	1. 중첩된 Lock 을 사용하는 것을 피해라 
	2. Lock을 소유하고 있을 때 유저 코드를 호출하는 것을 피해라
	3. Lock들을 언제나 정해진 순서로 획득해라 
*/

using std::thread;
using std::vector;
using std::mutex;

void worker(mutex& m1, mutex& m2) {
	for (int i = 0; i < 10; i++) {
		m1.lock();  // m1 뮤텍스 잠금 - 임계 구역 진입 대기 및 진입
		m2.lock();  // m2 뮤텍스 잠금 - 두 번째 임계 구역 진입

		std::cout << "work 1 : " << i << std::endl;   

		m2.unlock();  // m2 뮤텍스 잠금 해제 - 임계 구역 보호 종료
		m1.unlock();  // m1 뮤텍스 잠금 해제 - 임계 구역 보호 종료
	}
}


void worker_2(mutex& m1, mutex& m2) {		// 잠금 시도를 반복하며 데드락 방지
	for (int i = 0; i < 10; i++) {
		while (true) {
			m2.lock();

			if (!m1.try_lock()) { // m1 잠금 시도 - 즉시 결과 반환(성공하면 true, 실패하면 false)
				// m1 잠금 실패 시 
				m2.unlock();  // 이미 잠근 m2 잠금 해제
				continue;     // 다시 반복문 처음으로 돌아가 재시도
			}
			std::cout << "work 2 : " << i << std::endl;

			m1.unlock();  // m1 잠금 해제
			m2.unlock();  // m2 잠금 해제
			break;
		}
	}
}

int main() {

	mutex m1, m2;

	thread t1(worker, std::ref(m1), std::ref(m2));
	thread t2(worker_2, std::ref(m1), std::ref(m2));

	t1.join();
	t2.join();
}


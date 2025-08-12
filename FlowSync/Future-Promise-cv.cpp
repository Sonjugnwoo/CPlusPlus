//조건변수를 활용해서도 가능하나 Promise - Future 이 더욱 깔끔하며 이해 하기 쉬움 

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <string>

std::condition_variable cv; // 스레드 간 신호 전달용 조건변수
std::mutex m;               // 데이터 보호를 위한 mutex
bool done = false;          // 작업 완료 여부 표시 플래그
std::string info;           // worker 스레드에서 생성한 데이터 저장

void worker() {
	//  {} 안에 lock_guard 의 생명주기를 이 블록으로 제한 -> 락 해제 -> notify 호출 -> 병목 감소 + 데드락 예방
	{
	// mutex 잠금: info와 done 변수를 안전하게 변경
		std::lock_guard<std::mutex> lk(m);
		info = "some data"; // 데이터 준비
		done = true;        // 작업 완료 상태로 변경
	} // lock_guard 소멸 → mutex 자동 해제

	// 대기 중인 스레드(메인 스레드)에게 작업 완료 신호 전송
	cv.notify_all();
}

int main() {
	std::thread t(worker);

	std::unique_lock<std::mutex> lk(m);	 // mutex 잠금 + unique_lock (cv.wait에서 필요)

	// done이 true가 될 때까지 대기 (조건변수 사용)
	// 조건: done이 true면 즉시 반환, 아니면 sleep 상태로 대기
	cv.wait(lk, [] {return done; });

	lk.unlock();	// worker 스레드가 데이터를 준비한 상태

	std::cout << "받은 데이터 : " << info << std::endl;

	t.join();
}
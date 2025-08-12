#include <chrono>
#include <iostream>
#include <thread>
#include <exception>
#include <string>
#include <future>

void worker(std::promise<void>* p) {
	std::this_thread::sleep_for(std::chrono::seconds(10));		// 10초 대기
	p->set_value();		//future에 "작업이 끝났다" 신호만 보냄
}

int main() {

	std::promise<void> p;              // void 타입 promise (값 없음, 완료 신호만)
	std::future<void> data = p.get_future(); // promise와 연동된 future 획득

	std::thread t(worker, &p);

	while (true) {
		std::future_status status = data.wait_for(std::chrono::seconds(1));		 // 최대 1초 동안 결과를 기다린 뒤 상태 확인

		if (status == std::future_status::timeout) 	std::cerr << ">";			 // 아직 준비 안 됨 → 진행 표시  cerr - > 실시간으로 바로 화면에 보임 
		else if (status == std::future_status::ready) break;					 // future 준비 완료 → 루프 탈출
	}

	t.join();
}
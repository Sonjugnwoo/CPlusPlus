#include <exception>
#include <string>
#include <thread>
#include <future>
#include <iostream>

//예외를 발생시키고 promise를 통해 main 스레드로 전달
void worker(std::promise<std::string>* p) {
	try {
		throw std::runtime_error("Some Error");	 // 일부러 예외 발생
	}
	catch (...) {
		// 모든 타입의 예외를 잡음
	    // 현재 예외 상태를 exception_ptr로 가져와서 promise에 저장
	    // → 나중에 future.get()에서 이 예외가 다시 던져짐
		p->set_exception(std::current_exception());
	}
}

int main() {
	std::promise<std::string> p;					 // 값 또는 예외를 전달할 promise
	std::future<std::string> data = p.get_future();	 // promise와 연결된 future

	std::thread t(worker, &p);						 // worker 스레드 실행, promise 주소 전달

	data.wait();								     // future에 값이나 예외가 도달할 때까지 대기

	try {
		// future에서 값 받기 (혹은 예외 발생)
		// 값 대신 예외가 설정되어 있으면 이 시점에서 예외가 다시 던져짐
		data.get();
	}
	catch (const std::exception& e) {
		// 위에서 던져진 예외를 받음
		std::cout << "예외 : " << e.what() << std::endl;
	}

	t.join();
}
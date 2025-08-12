#include <chrono>
#include <thread>
#include <future>
#include <iostream>

// start 신호가 올 때까지 대기 후 "출발" 출력
void runner(std::shared_future<void>* start) {
	start->get();	// promise가 set_value() 할 때까지 대기
	std::cout << "출발" << std::endl;
}

int main() {
	std::promise<void> p;							 // void 타입 promise (완료 신호만 전달)
    std::shared_future<void> start = p.get_future(); // promise로부터 shared_future 획득

	// 같은 shared_future를 여러 스레드에 전달
	std::thread t1(runner, &start);
	std::thread t2(runner, &start);
	std::thread t3(runner, &start);
	std::thread t4(runner, &start);

	// 메인 스레드에서 준비 메시지 출력
	std::cerr << "준비";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cerr << "!\n";

	// 여기서 promise 완료 → 모든 runner 스레드의 get()이 반환되어 동시에 "출발" 출력
	p.set_value();

	t1.join();
	t2.join();
	t3.join();
	t4.join();

}
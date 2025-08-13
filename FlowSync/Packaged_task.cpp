//Future - Promise 패턴을 비동기적 함수 ( 람다 ) 의 리턴값에 간단히 적용 

#include <future>
#include <iostream>
#include <thread>


int some_task(int x) { return 10 + x; }

int main() {
	// <int(int)>  -> int를 리턴하고 인자로 int를 받음 
	// packaged_task에는 실행할 함수(혹은 함수 객체)를 등록
	// 이 packaged_task가 실행되면 결과가 연결된 future에 저장됨
	std::packaged_task<int(int)> task(some_task);

	// packaged_task와 연결된 future 획득
	// 이 future를 통해 나중에 작업 결과를 받아올 수 있음
	std::future<int> start = task.get_future();

	// packaged_task는 복사(copy) 불가능 -> std::move로 소유권 이전
	// std::thread를 생성하면서 인자 5 전달 -> 내부적으로 some_task(5) 실행
	std::thread t(std::move(task), 5);	

	// task가 실행 완료될 때까지 get()은 블로킹
	std::cout << "결과 : " << start.get();
	t.join();
}
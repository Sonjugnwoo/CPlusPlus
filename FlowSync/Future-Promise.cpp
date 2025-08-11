// Future-Promise -> 미래에 쓰레드 T가 원하는 데이터를 돌려 주겟다 라는 약속

#include <future>
#include <iostream>
#include <string>
#include <thread>

// 워커 스레드에서 실행될 함수
void worker(std::promise<std::string>* p) {
	// promise에 값 설정 -> 연결된 future가 이 값을 받을 수 있게 함
	p->set_value("some data");
}

int main() {
    //  promise 생성 : 미래에 std::string 타입 데이터를 전달하겠다는 약속 객체
    std::promise<std::string> p;

    //  future 획득 : promise와 연결된 future를 얻어, 나중에 데이터 수신 가능
    std::future<std::string> data = p.get_future();

    //  워커 스레드 시작, promise 포인터를 인자로 넘김
    std::thread t(worker, &p);

    //  future 데이터 준비될 때까지 대기 (worker에서 set_value 호출할 때까지 블록)
    data.wait();

    //  future에서 값 꺼내기 (get 호출 시 값이 준비되지 않았다면 내부적으로 wait)
    std::cout << "받은 데이터 " << data.get() << std::endl;

    //  워커 스레드가 끝날 때까지 메인 스레드에서 대기
    t.join();
}
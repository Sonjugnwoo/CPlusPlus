//atomicity 중간에 다른 쓰레드가 끼어들 여지가 전혀 없는 연산 ( 마치 원자 처럼 쪼갤 수 없음)

#include <atomic>      // std::atomic 사용을 위한 헤더
#include <iostream>
#include <thread>
#include <vector>

// worker 함수: atomic 카운터를 10000번 증가시키는 작업
void worker(std::atomic<int>& counter) {
    for (int i = 0; i < 10000; i++)
        counter++;  // 원자적(atomic)으로 counter 값 1 증가
}

int main() {
    std::atomic<int> counter(0);  // atomic 정수형 변수 counter를 0으로 초기화

    std::vector<std::thread> workers;  // 스레드 객체를 저장할 벡터 선언

    // 4개의 스레드를 생성하여 worker 함수 실행, counter를 참조로 전달
    for (int i = 0; i < 4; i++)
        workers.push_back(std::thread(worker, std::ref(counter)));

    // 모든 스레드가 종료될 때까지 메인 스레드가 기다림(join)
    for (int i = 0; i < 4; i++)
        workers[i].join();

    // 최종 결과 출력 (4개의 스레드가 각각 10000번씩 증가시켰으므로 40000)
    std::cout << "Counter = " << counter << std::endl;
}
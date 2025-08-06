//memory_order_relaxed CPU 에서 메모리 연산 순서에 관련해서 무한한 자유를 주는 것과 같음 덕분에 매우 빠른속도로 CPU에서 실행 

#include <atomic>      // std::atomic 사용을 위한 헤더
#include <iostream>
#include <thread>
#include <vector>

void worker(std::atomic<int>* counter) {
    for (int i = 0; i < 10000; i++)
        counter->fetch_add(1, std::memory_order_relaxed);   // 순서 제약 없는 원자적 증가
}

// t1 함수: atomic 변수 b에 1 저장, a 값을 읽어 출력
void t1(std::atomic<int>* a, std::atomic<int>* b) {
    b->store(1, std::memory_order_relaxed);  // relaxed 순서로 b에 1 저장
    int x = a->load(std::memory_order_relaxed);  // relaxed 순서로 a 값 읽음

    printf("x : %d\n", x);
}

// t2 함수: atomic 변수 a에 1 저장, b 값을 읽어 출력
void t2(std::atomic<int>* a, std::atomic<int>* b) {
    a->store(1, std::memory_order_relaxed);  // relaxed 순서로 a에 1 저장
    int y = b->load(std::memory_order_relaxed);  // relaxed 순서로 b 값 읽음

    printf("y : %d\n", y);
}

int main() {

    std::vector<std::thread> threads;

    std::atomic<int> a(0);  // atomic 변수 a 초기화 0
    std::atomic<int> b(0);  // atomic 변수 b 초기화 0

    // t1, t2 두 스레드 생성하여 메모리 순서 테스트
    threads.push_back(std::thread(t1, &a, &b));
    threads.push_back(std::thread(t2, &a, &b));

    // 두 스레드 종료 대기
    for (int i = 0; i < 2; i++)
        threads[i].join();

    std::vector<std::thread> threads2;

    std::atomic<int> counter(0);

    for (int i = 0; i < 4; i++)
        threads2.push_back(std::thread(worker, &counter));

    for (int i = 0; i < 4; i++)
        threads2[i].join();

    // 최종 counter 값 출력 (4 * 10000 = 40000 기대)
    std::cout << "Counter = " << counter << std::endl;
}
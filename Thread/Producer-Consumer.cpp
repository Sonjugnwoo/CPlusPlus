// 생산자(Producer) - 처리할 일을 생성하거나 받아와서 작업 큐에 넣는 쓰레드
// 소비자(Consumer) - 작업 큐에서 일을 꺼내 실제로 처리하는 쓰레드

#include <iostream>
#include <chrono>                // 시간 관련 라이브러리
#include <mutex>                 // std::mutex, std::lock_guard, std::unique_lock
#include <queue>                 // std::queue (FIFO 자료구조)
#include <condition_variable>    // std::condition_variable (스레드 간 동기화)
#include <string>
#include <vector>
#include <thread>                // std::thread

// 생산자 함수 (웹사이트에서 페이지 계속 다운로드 역할)
void producer(std::queue<std::string>* download_pages, std::mutex* m, int idx,std::condition_variable* cv) {
	for (int i = 0; i < 5; i++) {
		std::this_thread::sleep_for(std::chrono::microseconds(100 * idx));		//sleep_for -> 인자로 전달 받은 시간만 큼 쓰레드를 sleep 
		std::string content = " 웹사이트 : " + std::to_string(i) + " from thread(" + std::to_string(idx) + ")\n";
		
		// 뮤텍스 잠금 (lock_guard가 자동으로 뮤텍스 관리)
		std::lock_guard<std::mutex> lock(*m);
		download_pages->push(content);  // 공유 큐에 데이터 추가
	}
	// 소비자에게 새로운 데이터가 준비됐음을 알림 (대기 중인 스레드 깨우기)
	cv->notify_one();
	
}

// 비효율적인 busy-wait 방식의 소비자 함수
void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m, int* num_processed) {
	// 처리한 아이템 개수가 25개가 될 때까지 반복
	while (*num_processed < 25) {
		m->lock(); // 뮤텍스 잠금 (공유 큐 보호)

		if (downloaded_pages->empty()) { // 만약 큐가 비어있으면
			m->unlock();  // 뮤텍스 해제 (다른 스레드가 큐에 접근 가능하도록)

			// 10밀리초 대기 (잠시 대기 후 다시 체크)
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			continue; // 다시 루프 처음으로 이동하여 큐 확인
		}

		// 큐에 데이터가 있으면
		std::string content = downloaded_pages->front(); // 큐 앞의 데이터를 읽음
		downloaded_pages->pop(); // 큐에서 해당 데이터 삭제

		(*num_processed)++; // 처리한 개수 증가

		m->unlock(); // 뮤텍스 해제 (다른 스레드 접근 가능)

		std::cout << content; // 데이터 출력

		// 약간의 처리 시간 주기 (80마이크로초)
		std::this_thread::sleep_for(std::chrono::microseconds(80));
	}
}

// 소비자 함수 (condition_variable 기반 효율적 대기 방식)
void consumer_2(std::queue<std::string>* downloaded_pages, std::mutex* m, int* num_processed, std::condition_variable* cv) {
	while (*num_processed < 25) {
		std::unique_lock<std::mutex> lk(*m); // 뮤텍스 잠금 (unique_lock: lock/unlock 자유로움)

		// 큐가 비었으면 대기, 데이터가 있거나 처리 개수 25개 도달하면 깨어남
		cv->wait(lk, [&] { return !downloaded_pages->empty() || *num_processed == 25; });

		// 25개 처리 완료 시 종료 (다른 소비자도 깨울 수 있도록 unlock 후 리턴)
		if (*num_processed == 25) {
			lk.unlock();
			return;
		}

		// 큐에서 데이터 꺼내기
		std::string content = downloaded_pages->front();
		downloaded_pages->pop();

		(*num_processed)++; // 처리 개수 증가

		lk.unlock(); // 데이터 처리하면서 뮤텍스 풀어 다른 스레드가 접근 가능하도록 함

		// 처리한 내용 출력 및 약간의 작업 지연
		std::cout << content;
		std::this_thread::sleep_for(std::chrono::microseconds(80));
	}
}
int main() {
	std::queue<std::string> download_pages;
	std::mutex m;
	std::condition_variable cv;

	std::vector<std::thread> producers;
	for (int i = 0; i < 5; i++)
		producers.push_back(std::thread(producer, &download_pages, &m, i + 1,&cv));

	int num_processed = 0; 
	std::vector<std::thread> consumers;
	for (int i = 0; i < 5; i++)
		consumers.push_back(std::thread(consumer_2, &download_pages, &m,&num_processed,&cv));

	for (int i = 0; i < 5; i++)
		producers[i].join();

	// 생산자 종료 후에도 소비자는 대기 중일 수 있으므로, 조건 변수 깨우기
	cv.notify_all();

	for (int i = 0; i < 5; i++)
		consumers[i].join();
}
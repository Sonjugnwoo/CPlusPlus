//memory_order_acquire	해당 명령 뒤에 오는 모든 메모리 명령들이 해당 명령 위로 재배치 되는것을 금지 .
//memory_order_release	해당 명령 이전의 모든 메모리 명령들이 해당 명령 이후로 재배치 되는 것을 금지 , 같은 변수를 acquire으로 읽는 쓰레드가 있다면 모든 명령들이 관찰 될 수 있어야함 
//같은 변수의 release , acquire 를 통해서 동기화를 수행 

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<bool> ready;
std::atomic<int> data[3];

void produ() {
	// 순서에 상관없이 relaxed 모드로 data 배열에 값 저장
	data[0].store(1, std::memory_order_relaxed);
	data[1].store(2, std::memory_order_relaxed);
	data[2].store(3, std::memory_order_relaxed);

	// data 쓰기가 모두 끝난 뒤 ready 변수에 true 저장
    // memory_order_release: 이 store 이전의 모든 메모리 쓰기 연산이 현재 store 이후로 재배치되는 것을 금지함 (순서 보장)
	ready.store(true, std::memory_order_release);
}

void consu() {
	// memory_order_acquire: 이 load 이후의 모든 메모리 읽기/쓰기 연산은이 load 이전으로 재배치될 수 없음 (순서 보장)
	while(!ready.load(std::memory_order_acquire)){}

	// ready가 true가 되었으므로, produ()에서 저장한 data 값들이 "보장된" 상태
	// relaxed 모드로 읽더라도, acquire-release 관계 덕분에 값들이 정상적으로 관찰됨
	std::cout << "Data[0] : " << data[0].load(std::memory_order_relaxed) << std::endl;
	std::cout << "Data[1] : " << data[1].load(std::memory_order_relaxed) << std::endl;
	std::cout << "Data[2] : " << data[2].load(std::memory_order_relaxed) << std::endl;
}

void producer(std::atomic<bool>* is_ready, int* data) {
	*data = 10;

	// is_ready에 메모리 순서 release로 true 저장 (동기화 신호)
	is_ready->store(true, std::memory_order_release);		
}

void consumer(std::atomic<bool>* is_ready, int* data) {
	while (!is_ready->load(std::memory_order_acquire)) {  // true가 되면 producer가 data를 썼다는 의미이므로, data 값 읽기 가능
	}

	std::cout << "Data : " << *data << std::endl;
}

int main() {
	std::vector<std::thread> threads;

	std::atomic<bool> is_ready(false);
	int data = 0;

	threads.push_back(std::thread(producer, &is_ready, &data));
	threads.push_back(std::thread(consumer, &is_ready, &data));

	for (int i = 0; i < 2; i++)
		threads[i].join();

	std::cout << "--------------------------" << std::endl;

	std::vector<std::thread> threads2;

	threads2.push_back(std::thread(produ));
	threads2.push_back(std::thread(consu));

	for (int i = 0; i < 2; i++)
		threads2[i].join();

}

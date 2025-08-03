#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>

using std::thread;
using std::vector;

// 덧셈을 수행할 데이터의 시작점과 끝점을 받아서 해당 범위 내의 원소들을 모두 더한 후 result 에 저장 
// 쓰레드는 리턴 값이 X  어떤 결과를 반환하고 싶으면 포인터로 전달 
void worker(vector<int>::iterator start, vector<int>::iterator end, int* result) {
	int sum = 0;
	for (auto itr = start; itr < end; ++itr)
		sum += *itr;

	*result = sum;

	thread::id this_id = std::this_thread::get_id();	   // 현재 실행 중인 쓰레드의 고유 id 획득
	printf("쓰레드 %x 에서 %d 부터 %d 까지 계산 결과 : %d \n", this_id, *start, *(end-1),sum);
}

int main() {
	vector<int> data(10000);
	
	for (int i = 0; i < 10000; i++)	data[i] = i;

	vector<int> partial_sums(4);	 // 각 쓰레드가 계산한 부분 합 저장용

	vector<thread> workers;	// 쓰레드 객체들을 담을 벡터

	// 각 쓰레드에 data 범위를 2500개씩 할당하고,
	// partial_sums[i] 주소를 결과 저장용 포인터로 전달
	for (int i = 0; i < 4; i++)
		workers.push_back(thread(worker, data.begin() + i * 2500, data.begin() + (i + 1) * 2500, &partial_sums[i]));

	for (int i = 0; i < 4; i++) workers[i].join();		   // 모든 쓰레드가 종료할 때까지 대기

	int total = 0; 
	for (int i = 0; i < 4; i++)	total += partial_sums[i];

	std::cout << "전체 합 : " << total << std::endl;

}
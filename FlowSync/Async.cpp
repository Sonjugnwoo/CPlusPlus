//Async -> promise , packaged_task 를 비동기적으로 실행 하기 위해서는 쓰레드를 명시적으로 생성 후 실행
//		   async 에 함수 전달 시 알아서 쓰레드를 만들어 비동기적으로 실행 후 futrue에 전달 

#include <iostream>
#include <thread>
#include <future>
#include <vector>

int sum(const std::vector<int>& v, int start, int end) {
	int total = 0; 

	for (int i = start; i < end; i++)
		total += v[i];

	return total;
}

int paralle_sum(const std::vector<int>& v) {
	// 벡터 앞 절반 합을 std::async로 비동기 실행
	// launch::async : 함수가 반드시 새 스레드에서 실행되도록 강제
	// launch::deferred : future 의 get 함수 호출시 실행 ( 새로운 쓰레드 X)
	std::future<int> lower_half_future = std::async(std::launch::async, sum, std::cref(v), 0, v.size() / 2);		
	// async (비동기(새 스레드)실행 정책 , 실행할 함수 , v 참조 전달 (복사 방지 ) , 시작 인덱스 , 끝 인덱스) 
	// 기본 async 정책은 lazy 실행일 수도 있어서 보장하려면 std::launch::async 필요

	// 벡터 뒷 절반은 현재 스레드(메인 스레드)에서 계산
	int upper_half = sum(v, v.size() / 2, v.size());

	// lower_half_future.get()은 비동기 계산이 끝날 때까지 대기
	return lower_half_future.get() + upper_half;
}


int main() {
	std::vector<int> v;
	v.reserve(100);

	for (int i = 0; i < 100; i++)
		v.push_back(i + 1);

	std::cout << paralle_sum(v); 
}
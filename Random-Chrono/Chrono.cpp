#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

int main() {
	std::random_device rd;               // 난수 시드 생성
	std::mt19937 gen(rd());              // 난수 생성기 초기화

	std::uniform_int_distribution<> dist(0, 1000); // 0~1000 사이의 균등분포 난수 생성기

	for (int total = 1; total <= 100000; total *= 10) { // 난수 개수를 1, 10, 100, ..., 100000 순으로 반복
		std::vector<int> random_numbers;                // 실제 난수 저장용 벡터
		random_numbers.reserve(total);                  // 벡터 용량을 미리 확보하여,  늘어나는 오버헤드를 줄임

		std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
		// 난수 생성 시작 시점 저장

		for (int i = 0; i < total; i++)
			random_numbers.push_back(dist(gen));        // 난수를 벡터에 추가

		std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
		// 난수 생성 끝 시점 저장

		auto diff = end - start;                        // 시작~끝 시점의 시간 차

		std::cout << std::setw(7) << total<< "개 난수 생성 시 틱 횟수 : " << diff.count() << std::endl;        
		// 경과된 시간의 '틱' 단위 출력 (기본 단위: std::chrono 사용 환경에 따라 다름)

		std::cout << std::setw(7) << total << "개 난수 생성 시 걸리는 시간  : " << std::chrono::duration_cast<std::chrono::microseconds>(diff).count() << std::endl;
		// 마이크로초(µs) 단위로 변환 후 출력 (1초 = 1,000,000 마이크로초)
	}
}
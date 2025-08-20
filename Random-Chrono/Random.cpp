#include <iostream>
#include <random>
#include <map>
#include <iomanip>

int main() {
	std::random_device rd; // 난수 생성기(seeding에 사용)

	std::mt19937 gen(rd()); //  시드를 받아 초기화

	std::normal_distribution<double> dist(0, 1); // 평균 0, 표준편차 1인 정규분포 객체 생성

	std::map<int, int> hist{}; // key: 정수 구간, value: 출현 횟수 저장 map(히스토그램)
	for (int n = 0; n < 500; ++n)
		++hist[std::round(dist(gen))]; // 정규분포 난수 생성 후 반올림해서 해당 구간 count 증가

	for (auto p : hist)
		std::cout << std::setw(2) << p.first   // 정수 값 구간 (x축)
		<< ' ' << std::string(p.second / 100, '*') // 빈도수에 따라 * 출력(100개당 별 1개)
		<< " " << p.second << std::endl; // 실제 빈도수(카운트) 출력
}
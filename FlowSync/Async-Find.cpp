#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <algorithm>

// 특정 구간(begin ~ end)에서 data를 찾아보고, 찾으면 true 반환
// 찾은 경우에는 "찾음 : data" 출력
template <typename Iter, typename T>
bool  do_find(Iter begin , Iter end ,const T data) {
	auto result = std::find(begin, end, data);	// std::find: [begin, end) 구간에서 data를 선형 탐색

	if (result != end) {	// end가 아니면 값 존재
		std::cout << "찾음 : " << data << std::endl;
		return true;
	}

	return false;	
}

// 주어진 벡터를 절반으로 나누어, 앞뒤 구간을 비동기로 검색하는 함수
template <typename T>
void do_find_parallel(const std::vector<T> &v,const T data) {	
	// 벡터의 중간 위치 반복자 (앞 구간과 뒷 구간 나눌 경계)
	auto mid = v.begin() + v.size() / 2;

	// 첫 번째 구간 [begin, mid) 검색을 async로 비동기 실행
	auto f1 = std::async([&]() { return do_find(v.begin(), mid, data); });

	// 두 번째 구간 [mid, end) 검색을 async로 비동기 실행
	auto f2 = std::async([&]() { return do_find(mid, v.end(), data); });

	// 각 async의 반환값(bool) 수신 - get은 해당 작업 끝날 때까지 대기
	bool found1 = f1.get();
	bool found2 = f2.get();

	// 두 구간 모두에서 못 찾으면 최종 "결과 없음" 출력
	if (!found1 && !found2)
		std::cout << "결과 없음\n";
	
}

int main(){
	std::vector<int> nums;
	for (int i = 0; i < 20; i++)
		nums.push_back(i);

	do_find_parallel(nums, 15); // 찾는 값 있음
	do_find_parallel(nums, 50); // 찾는 값 없음
}

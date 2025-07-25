#include <algorithm>
#include <iostream>
#include <vector>

//Sort(start,end) 함수는 정렬할 원소의 시작 위치와 마지막 위치 바로 뒤를 반복자 로 받음
//반드시 임의접근 반복자 (vector, deque 등)만 가능
// 오름 차순이 기본 

template <typename Iter>
void print_sort(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << *begin << " ";
		begin++;
	}
	std::cout << std::endl;
}

template <typename T>
struct Compare {
	bool operator()(const T& a, const T& b) const {
		return a > b;
	}
};

int main() {
	std::vector<int> vec;

	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(6);
	vec.push_back(2);

	std::cout << "정렬 전 : ";
	print_sort(vec.begin(), vec.end());

	// 기본 오름차순 정렬
	std::sort(vec.begin(), vec.end());

	std::cout << "정렬 후 :";
	print_sort(vec.begin(), vec.end());

	// 내림차순 정렬 (Compare 비교자 사용)
	std::sort(vec.begin(), vec.end(), Compare<int>());

	std::cout << "내림차순 정렬 :";
	print_sort(vec.begin(), vec.end());

	return 0;

}
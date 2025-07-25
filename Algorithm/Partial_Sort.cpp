#include <algorithm>
#include <iostream>
#include <vector>

// Partial_Sort (start , middle , end) 함수는 일부만 정렬하는 함수 
//  전체 원소 중 [start,middle] 까지 원소들이 전체 원소들 중에서 제일 작은 애들 순으로 정렬 
// 시간 복잡도 전체 원소 N , 정렬 크기 M 일시 O(N log M) 

template <typename Iter>
void print_partial_sort(Iter begin, Iter end) {
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
	print_partial_sort(vec.begin(), vec.end());

	std::partial_sort(vec.begin(), vec.begin() + 3, vec.end());

	std::cout << "정렬 후 :";
	print_partial_sort(vec.begin(), vec.end());

	// 내림차순 정렬 (Compare 비교자 사용)
	std::partial_sort(vec.begin(), vec.begin() + 3,vec.end(), Compare<int>());

	std::cout << "내림차순 정렬 :";
	print_partial_sort(vec.begin(), vec.end());

}
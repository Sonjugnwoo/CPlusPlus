#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

// std::find(First, Last, Value) : 반복자 구간 [First, Last)에서 첫 번째로 value와 같은 원소를 찾고,
// 해당 원소의 반복자를 반환한다. 찾지 못하면 Last를 반환.
// 중복된 값이 있어도 가장 먼저 만나는(First ~ Last 방향으로) 원소를 반환한다.
// 역방향(뒤에서부터 찾기)은 reverse iterator (예: rbegin/rend)와 함께 사용한다.

template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "]";
		begin++;
	}
	std::cout << std::endl;
}

int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(7);
	vec.push_back(2);
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);
	vec.push_back(2);

	auto result = std::find(vec.begin(), vec.end(), 2);

	std::cout << "2는 " << std::distance(vec.begin(), result) + 1 << "번 째 원소 " << std::endl;

	// 중복된 수 출력 
	auto current = vec.begin();
	while ((current = std::find(current, vec.end(), 5)) !=vec.end()) {
		std::cout << "5 는 " << std::distance(vec.begin(), current) + 1 << " 번 째 원소" << std::endl;
		current++;
	}

	//조건 추가 

	auto cur = vec.begin();
	while (true) {
		cur = std::find_if(cur, vec.end(), [](int i) {return i % 3 == 2; });
		if (cur == vec.end()) break;
		std::cout << "3 으로 나눈 나머지가 2 인 원소" << *cur << "이다" << std::endl;
		cur++;
	}
}
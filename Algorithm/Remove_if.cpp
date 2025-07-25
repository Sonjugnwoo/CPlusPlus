#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
//Remove_if  Remove함수의 조건 추가 = Remove_if
//원소의 이동 수행  직접적인 삭제는 X 삭제가 필요할시 erase 호출 해서 삭제
//순방향 반복자 사용 ( vector ,list , set , map) 전부 사용 가능 

template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "]";
		begin++;
	}
	std::cout << std::endl;
}

struct odd {
	bool operator() (const int& i) { return i % 2 == 1; }
};
struct is_odd {
	int* num_delete;   //포인터 쓰는 이유 : remove_if가 복사본으로 함수 객체를 사용 하기 때문에 외부변수로 관리 

	is_odd(int* num_delete) : num_delete(num_delete) {}

	bool operator() (const int& i) {
		if (*num_delete >= 2) return false;
		if (i % 2 == 1) {
			(*num_delete)++;
			return true;
		}
		return false;
	}
};

int main() {
	std::vector<int> vec;

	vec.push_back(5);
	vec.push_back(7);
	vec.push_back(2);
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);

	std::vector<int> vec2 = vec;

	std::cout << "처음 Vec : ";
	print(vec.begin(), vec.end());

	std::cout << "Vec 값 홀수 제거 ";
	vec.erase(std::remove_if(vec.begin(), vec.end(), odd()), vec.end());
	print(vec.begin(), vec.end());

	int num_delete = 0;
	std::cout << "처음 Vec2 : ";
	print(vec2.begin(), vec2.end());
	
	std::cout << "Vec2 홀수 2개만 제거 ";
	vec2.erase(std::remove_if(vec2.begin(), vec2.end(), is_odd(&num_delete)), vec2.end());
	print(vec2.begin(), vec2.end());
}
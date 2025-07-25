#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

//Remove 원소의 이동 수행  직접적인 삭제는 X 삭제가 필요할시 erase 호출 해서 삭제
//순방향 반복자 사용 ( vector ,list , set , map) 전부 사용 가능 

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
	vec.push_back(4);
	vec.push_back(5);

	std::cout << "처음 Vec : ";
	print(vec.begin(), vec.end());

	std::cout << "Vec 값 5 제거 ";
	vec.erase(std::remove(vec.begin(), vec.end(), 5), vec.end());
	print(vec.begin(), vec.end());

}
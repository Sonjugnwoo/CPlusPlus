#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

//transform (start , end , result.start , pred)   for문이랑 유사 
//값을 저장하는 컨테이너의 크기는 원래의 컨테이너보다 최소한 같거나 커야함 

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

	std::vector<int> vec2(6, 0);
	
	std::cout << "처음 Vec : ";
	print(vec.begin(), vec.end());
	std::cout << "처음 Vec2 : ";
	print(vec2.begin(), vec2.end());

	std::cout << "Vec 전체 +1 = Vec2\n";
	std::transform(vec.begin(), vec.end(), vec2.begin(),
		[](int i) {return i + 1; });

	std::cout << "Vec : ";
	print(vec.begin(), vec.end());
	std::cout << "Vec2 : ";
	print(vec2.begin(), vec2.end());
}
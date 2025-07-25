#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

//Stable_Sort (start , end) 원소가 삽입되어 있는 순서를 보존하는 정렬 방식
//Sort 는 정렬 시 원소들 간의 상대적 위치를 랜덤으로 바꾸지만 Stable_Sort는 순서를 처음 넣은 그대로 유지 
// 시간 복잡도 :  O(n (log n)^2)
template <typename Iter>
void print_stable_sort(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << *begin << " ";
		begin++;
	}
	std::cout << std::endl;
}

struct User {	//age 가 같으면 크기가 같다고 가정 
	std::string name;
	int age;

	User(std::string name, int age) : name(name), age(age) {}

	bool operator<(const User& u) const { return age < u.age; }
};

std::ostream& operator <<(std::ostream& o,const User& u) {
	o << u.name << "," << u.age;
	return o;
}

int main() {
	std::vector<User> vec;

	for (int i = 0; i < 100; i++){
		std::string name ="";
		name.push_back('a' + i / 26);
		name.push_back('a' + i % 26);
		vec.push_back(User(name, static_cast<int>(rand() % 10)));
	}
	std::vector<User> vec2 = vec;
	std::cout << "정렬 전 :";
	print_stable_sort(vec2.begin(), vec2.end());

	std::sort(vec2.begin(), vec2.end());

	std::cout << "정렬 후 :";
	print_stable_sort(vec2.begin(), vec2.end());

	std::cout << "Stable_Sort : ";
	std::stable_sort(vec2.begin(), vec2.end());
	print_stable_sort(vec2.begin(), vec2.end());

}
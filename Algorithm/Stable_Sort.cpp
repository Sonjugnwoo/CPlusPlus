#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

//Stable_Sort (start , end) ���Ұ� ���ԵǾ� �ִ� ������ �����ϴ� ���� ���
//Sort �� ���� �� ���ҵ� ���� ����� ��ġ�� �������� �ٲ����� Stable_Sort�� ������ ó�� ���� �״�� ���� 
// �ð� ���⵵ :  O(n (log n)^2)
template <typename Iter>
void print_stable_sort(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << *begin << " ";
		begin++;
	}
	std::cout << std::endl;
}

struct User {	//age �� ������ ũ�Ⱑ ���ٰ� ���� 
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
	std::cout << "���� �� :";
	print_stable_sort(vec2.begin(), vec2.end());

	std::sort(vec2.begin(), vec2.end());

	std::cout << "���� �� :";
	print_stable_sort(vec2.begin(), vec2.end());

	std::cout << "Stable_Sort : ";
	std::stable_sort(vec2.begin(), vec2.end());
	print_stable_sort(vec2.begin(), vec2.end());

}
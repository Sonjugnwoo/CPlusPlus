#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

//Remove ������ �̵� ����  �������� ������ X ������ �ʿ��ҽ� erase ȣ�� �ؼ� ����
//������ �ݺ��� ��� ( vector ,list , set , map) ���� ��� ���� 

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

	std::cout << "ó�� Vec : ";
	print(vec.begin(), vec.end());

	std::cout << "Vec �� 5 ���� ";
	vec.erase(std::remove(vec.begin(), vec.end(), 5), vec.end());
	print(vec.begin(), vec.end());

}
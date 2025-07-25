#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
//Remove_if  Remove�Լ��� ���� �߰� = Remove_if
//������ �̵� ����  �������� ������ X ������ �ʿ��ҽ� erase ȣ�� �ؼ� ����
//������ �ݺ��� ��� ( vector ,list , set , map) ���� ��� ���� 

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
	int* num_delete;   //������ ���� ���� : remove_if�� ���纻���� �Լ� ��ü�� ��� �ϱ� ������ �ܺκ����� ���� 

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

	std::cout << "ó�� Vec : ";
	print(vec.begin(), vec.end());

	std::cout << "Vec �� Ȧ�� ���� ";
	vec.erase(std::remove_if(vec.begin(), vec.end(), odd()), vec.end());
	print(vec.begin(), vec.end());

	int num_delete = 0;
	std::cout << "ó�� Vec2 : ";
	print(vec2.begin(), vec2.end());
	
	std::cout << "Vec2 Ȧ�� 2���� ���� ";
	vec2.erase(std::remove_if(vec2.begin(), vec2.end(), is_odd(&num_delete)), vec2.end());
	print(vec2.begin(), vec2.end());
}
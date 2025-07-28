#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

// std::find(First, Last, Value) : �ݺ��� ���� [First, Last)���� ù ��°�� value�� ���� ���Ҹ� ã��,
// �ش� ������ �ݺ��ڸ� ��ȯ�Ѵ�. ã�� ���ϸ� Last�� ��ȯ.
// �ߺ��� ���� �־ ���� ���� ������(First ~ Last ��������) ���Ҹ� ��ȯ�Ѵ�.
// ������(�ڿ������� ã��)�� reverse iterator (��: rbegin/rend)�� �Բ� ����Ѵ�.

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

	std::cout << "2�� " << std::distance(vec.begin(), result) + 1 << "�� ° ���� " << std::endl;

	// �ߺ��� �� ��� 
	auto current = vec.begin();
	while ((current = std::find(current, vec.end(), 5)) !=vec.end()) {
		std::cout << "5 �� " << std::distance(vec.begin(), current) + 1 << " �� ° ����" << std::endl;
		current++;
	}

	//���� �߰� 

	auto cur = vec.begin();
	while (true) {
		cur = std::find_if(cur, vec.end(), [](int i) {return i % 3 == 2; });
		if (cur == vec.end()) break;
		std::cout << "3 ���� ���� �������� 2 �� ����" << *cur << "�̴�" << std::endl;
		cur++;
	}
}
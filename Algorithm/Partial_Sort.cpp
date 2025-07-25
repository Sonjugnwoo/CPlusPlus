#include <algorithm>
#include <iostream>
#include <vector>

// Partial_Sort (start , middle , end) �Լ��� �Ϻθ� �����ϴ� �Լ� 
//  ��ü ���� �� [start,middle] ���� ���ҵ��� ��ü ���ҵ� �߿��� ���� ���� �ֵ� ������ ���� 
// �ð� ���⵵ ��ü ���� N , ���� ũ�� M �Ͻ� O(N log M) 

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

	std::cout << "���� �� : ";
	print_partial_sort(vec.begin(), vec.end());

	std::partial_sort(vec.begin(), vec.begin() + 3, vec.end());

	std::cout << "���� �� :";
	print_partial_sort(vec.begin(), vec.end());

	// �������� ���� (Compare ���� ���)
	std::partial_sort(vec.begin(), vec.begin() + 3,vec.end(), Compare<int>());

	std::cout << "�������� ���� :";
	print_partial_sort(vec.begin(), vec.end());

}
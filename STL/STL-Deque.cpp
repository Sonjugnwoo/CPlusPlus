#include <iostream>
#include <deque>

/*
���� ���� ���� (index) : O(1)

��/�� ���� �߰� (push_front, push_back) : O(1)

�߰� ����/���� : O(n) (���� ûũ �̵� �Ǵ� ���ġ �ʿ�)

�߰� Ž�� : O(n)
*/

template <typename T>
void print_deque(const std::deque<T>& dq) {
	for (const auto& elem : dq)
		std::cout << elem << " ";
}


int main() {

	std::deque<int> dq;
	
	dq.push_back(2);
	dq.push_back(5);
	dq.push_back(7);
	dq.push_back(1);
	dq.push_back(10);

	std::cout << "[";
	print_deque(dq);
	std::cout << "]" << std::endl;

	dq.pop_front();
	std::cout << "�Ǿ� ���� ���� \n[";
	print_deque(dq);
	std::cout << "]" << std::endl;

}
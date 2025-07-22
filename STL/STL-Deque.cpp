#include <iostream>
#include <deque>

/*
임의 원소 접근 (index) : O(1)

앞/뒤 원소 추가 (push_front, push_back) : O(1)

중간 삽입/삭제 : O(n) (내부 청크 이동 또는 재배치 필요)

중간 탐색 : O(n)
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
	std::cout << "맨앞 원소 제거 \n[";
	print_deque(dq);
	std::cout << "]" << std::endl;

}
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <algorithm>

// Ư�� ����(begin ~ end)���� data�� ã�ƺ���, ã���� true ��ȯ
// ã�� ��쿡�� "ã�� : data" ���
template <typename Iter, typename T>
bool  do_find(Iter begin , Iter end ,const T data) {
	auto result = std::find(begin, end, data);	// std::find: [begin, end) �������� data�� ���� Ž��

	if (result != end) {	// end�� �ƴϸ� �� ����
		std::cout << "ã�� : " << data << std::endl;
		return true;
	}

	return false;	
}

// �־��� ���͸� �������� ������, �յ� ������ �񵿱�� �˻��ϴ� �Լ�
template <typename T>
void do_find_parallel(const std::vector<T> &v,const T data) {	
	// ������ �߰� ��ġ �ݺ��� (�� ������ �� ���� ���� ���)
	auto mid = v.begin() + v.size() / 2;

	// ù ��° ���� [begin, mid) �˻��� async�� �񵿱� ����
	auto f1 = std::async([&]() { return do_find(v.begin(), mid, data); });

	// �� ��° ���� [mid, end) �˻��� async�� �񵿱� ����
	auto f2 = std::async([&]() { return do_find(mid, v.end(), data); });

	// �� async�� ��ȯ��(bool) ���� - get�� �ش� �۾� ���� ������ ���
	bool found1 = f1.get();
	bool found2 = f2.get();

	// �� ���� ��ο��� �� ã���� ���� "��� ����" ���
	if (!found1 && !found2)
		std::cout << "��� ����\n";
	
}

int main(){
	std::vector<int> nums;
	for (int i = 0; i < 20; i++)
		nums.push_back(i);

	do_find_parallel(nums, 15); // ã�� �� ����
	do_find_parallel(nums, 50); // ã�� �� ����
}

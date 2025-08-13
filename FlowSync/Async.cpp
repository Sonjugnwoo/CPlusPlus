//Async -> promise , packaged_task �� �񵿱������� ���� �ϱ� ���ؼ��� �����带 ��������� ���� �� ����
//		   async �� �Լ� ���� �� �˾Ƽ� �����带 ����� �񵿱������� ���� �� futrue�� ���� 

#include <iostream>
#include <thread>
#include <future>
#include <vector>

int sum(const std::vector<int>& v, int start, int end) {
	int total = 0; 

	for (int i = start; i < end; i++)
		total += v[i];

	return total;
}

int paralle_sum(const std::vector<int>& v) {
	// ���� �� ���� ���� std::async�� �񵿱� ����
	// launch::async : �Լ��� �ݵ�� �� �����忡�� ����ǵ��� ����
	// launch::deferred : future �� get �Լ� ȣ��� ���� ( ���ο� ������ X)
	std::future<int> lower_half_future = std::async(std::launch::async, sum, std::cref(v), 0, v.size() / 2);		
	// async (�񵿱�(�� ������)���� ��å , ������ �Լ� , v ���� ���� (���� ���� ) , ���� �ε��� , �� �ε���) 
	// �⺻ async ��å�� lazy ������ ���� �־ �����Ϸ��� std::launch::async �ʿ�

	// ���� �� ������ ���� ������(���� ������)���� ���
	int upper_half = sum(v, v.size() / 2, v.size());

	// lower_half_future.get()�� �񵿱� ����� ���� ������ ���
	return lower_half_future.get() + upper_half;
}


int main() {
	std::vector<int> v;
	v.reserve(100);

	for (int i = 0; i < 100; i++)
		v.push_back(i + 1);

	std::cout << paralle_sum(v); 
}
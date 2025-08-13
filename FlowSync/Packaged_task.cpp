//Future - Promise ������ �񵿱��� �Լ� ( ���� ) �� ���ϰ��� ������ ���� 

#include <future>
#include <iostream>
#include <thread>


int some_task(int x) { return 10 + x; }

int main() {
	// <int(int)>  -> int�� �����ϰ� ���ڷ� int�� ���� 
	// packaged_task���� ������ �Լ�(Ȥ�� �Լ� ��ü)�� ���
	// �� packaged_task�� ����Ǹ� ����� ����� future�� �����
	std::packaged_task<int(int)> task(some_task);

	// packaged_task�� ����� future ȹ��
	// �� future�� ���� ���߿� �۾� ����� �޾ƿ� �� ����
	std::future<int> start = task.get_future();

	// packaged_task�� ����(copy) �Ұ��� -> std::move�� ������ ����
	// std::thread�� �����ϸ鼭 ���� 5 ���� -> ���������� some_task(5) ����
	std::thread t(std::move(task), 5);	

	// task�� ���� �Ϸ�� ������ get()�� ���ŷ
	std::cout << "��� : " << start.get();
	t.join();
}
#include <chrono>
#include <iostream>
#include <thread>
#include <exception>
#include <string>
#include <future>

void worker(std::promise<void>* p) {
	std::this_thread::sleep_for(std::chrono::seconds(10));		// 10�� ���
	p->set_value();		//future�� "�۾��� ������" ��ȣ�� ����
}

int main() {

	std::promise<void> p;              // void Ÿ�� promise (�� ����, �Ϸ� ��ȣ��)
	std::future<void> data = p.get_future(); // promise�� ������ future ȹ��

	std::thread t(worker, &p);

	while (true) {
		std::future_status status = data.wait_for(std::chrono::seconds(1));		 // �ִ� 1�� ���� ����� ��ٸ� �� ���� Ȯ��

		if (status == std::future_status::timeout) 	std::cerr << ">";			 // ���� �غ� �� �� �� ���� ǥ��  cerr - > �ǽð����� �ٷ� ȭ�鿡 ���� 
		else if (status == std::future_status::ready) break;					 // future �غ� �Ϸ� �� ���� Ż��
	}

	t.join();
}
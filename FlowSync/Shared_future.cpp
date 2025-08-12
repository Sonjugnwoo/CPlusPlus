#include <chrono>
#include <thread>
#include <future>
#include <iostream>

// start ��ȣ�� �� ������ ��� �� "���" ���
void runner(std::shared_future<void>* start) {
	start->get();	// promise�� set_value() �� ������ ���
	std::cout << "���" << std::endl;
}

int main() {
	std::promise<void> p;							 // void Ÿ�� promise (�Ϸ� ��ȣ�� ����)
    std::shared_future<void> start = p.get_future(); // promise�κ��� shared_future ȹ��

	// ���� shared_future�� ���� �����忡 ����
	std::thread t1(runner, &start);
	std::thread t2(runner, &start);
	std::thread t3(runner, &start);
	std::thread t4(runner, &start);

	// ���� �����忡�� �غ� �޽��� ���
	std::cerr << "�غ�";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cerr << "!\n";

	// ���⼭ promise �Ϸ� �� ��� runner �������� get()�� ��ȯ�Ǿ� ���ÿ� "���" ���
	p.set_value();

	t1.join();
	t2.join();
	t3.join();
	t4.join();

}
//���Ǻ����� Ȱ���ؼ��� �����ϳ� Promise - Future �� ���� ����ϸ� ���� �ϱ� ���� 

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <string>

std::condition_variable cv; // ������ �� ��ȣ ���޿� ���Ǻ���
std::mutex m;               // ������ ��ȣ�� ���� mutex
bool done = false;          // �۾� �Ϸ� ���� ǥ�� �÷���
std::string info;           // worker �����忡�� ������ ������ ����

void worker() {
	//  {} �ȿ� lock_guard �� �����ֱ⸦ �� ������� ���� -> �� ���� -> notify ȣ�� -> ���� ���� + ����� ����
	{
	// mutex ���: info�� done ������ �����ϰ� ����
		std::lock_guard<std::mutex> lk(m);
		info = "some data"; // ������ �غ�
		done = true;        // �۾� �Ϸ� ���·� ����
	} // lock_guard �Ҹ� �� mutex �ڵ� ����

	// ��� ���� ������(���� ������)���� �۾� �Ϸ� ��ȣ ����
	cv.notify_all();
}

int main() {
	std::thread t(worker);

	std::unique_lock<std::mutex> lk(m);	 // mutex ��� + unique_lock (cv.wait���� �ʿ�)

	// done�� true�� �� ������ ��� (���Ǻ��� ���)
	// ����: done�� true�� ��� ��ȯ, �ƴϸ� sleep ���·� ���
	cv.wait(lk, [] {return done; });

	lk.unlock();	// worker �����尡 �����͸� �غ��� ����

	std::cout << "���� ������ : " << info << std::endl;

	t.join();
}
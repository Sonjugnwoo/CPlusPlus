#include <thread>
#include <atomic>
#include <iostream>

std::atomic_flag at;		// atomic_flag�� ���� �ܼ��ϰ� ���� ������ �� �÷��� Ÿ��
int counter = 0;			// ī���� �ڿ� 

void spin_lock() {
	while (at.test_and_set(std::memory_order_seq_cst)) {
		// test_and_set(): ���� ���� �а� true�� ������ �� ���� ���� ��ȯ
		// - ���� ���� true�� �̹� �ٸ� �����尡 ���� ��� �ִ� ���� �� ���
		// - ���� ���� false�� ���� Ǯ���־����Ƿ� �� �����尡 ���� ����
		std::this_thread::sleep_for(std::chrono::microseconds(1));	// CPU ���� ���������� ���� ª�� sleep (microseconds ����)
	}
}

void unlock() {
	at.clear(std::memory_order_seq_cst);		//at�� false �� ����� �� ���� , �ٸ� �����尡 spin_lock �õ� ���� 
	// clear(): atomic_flag ���� false�� �ʱ�ȭ �� �� ����
}

void worker(int id) {	// �� ������(1, 2)�� 5���� counter ����
	for (int i = 0; i < 5; i++) {
		spin_lock();  // ���� ȹ���� ������ �ݺ� �õ�
		++counter;    // �Ӱ� ����(���� �����尡 ���ÿ� �����ϸ� �����Ǵ� �κ�)
		std::cout << "Thread " << id << " counter: " << counter << "\n";
		unlock();     // �� ����. �ٸ� �����尡 ������ �� �ְ� ��
	}
}



int main() {
	std::thread t1(worker, 1);
	std::thread t2(worker, 2);
	t1.join();
	t2.join();
}
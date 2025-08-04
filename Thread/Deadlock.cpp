#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

/* DeadLock ���̵� ���� (C++) 
	1. ��ø�� Lock �� ����ϴ� ���� ���ض� 
	2. Lock�� �����ϰ� ���� �� ���� �ڵ带 ȣ���ϴ� ���� ���ض�
	3. Lock���� ������ ������ ������ ȹ���ض� 
*/

using std::thread;
using std::vector;
using std::mutex;

void worker(mutex& m1, mutex& m2) {
	for (int i = 0; i < 10; i++) {
		m1.lock();  // m1 ���ؽ� ��� - �Ӱ� ���� ���� ��� �� ����
		m2.lock();  // m2 ���ؽ� ��� - �� ��° �Ӱ� ���� ����

		std::cout << "work 1 : " << i << std::endl;   

		m2.unlock();  // m2 ���ؽ� ��� ���� - �Ӱ� ���� ��ȣ ����
		m1.unlock();  // m1 ���ؽ� ��� ���� - �Ӱ� ���� ��ȣ ����
	}
}


void worker_2(mutex& m1, mutex& m2) {		// ��� �õ��� �ݺ��ϸ� ����� ����
	for (int i = 0; i < 10; i++) {
		while (true) {
			m2.lock();

			if (!m1.try_lock()) { // m1 ��� �õ� - ��� ��� ��ȯ(�����ϸ� true, �����ϸ� false)
				// m1 ��� ���� �� 
				m2.unlock();  // �̹� ��� m2 ��� ����
				continue;     // �ٽ� �ݺ��� ó������ ���ư� ��õ�
			}
			std::cout << "work 2 : " << i << std::endl;

			m1.unlock();  // m1 ��� ����
			m2.unlock();  // m2 ��� ����
			break;
		}
	}
}

int main() {

	mutex m1, m2;

	thread t1(worker, std::ref(m1), std::ref(m2));
	thread t2(worker_2, std::ref(m1), std::ref(m2));

	t1.join();
	t2.join();
}


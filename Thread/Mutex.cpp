#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using std::thread;
using std::vector;

//���ؽ�(Mutex)�� ���� �����尡 ���ÿ� �����ϴ� ���� �ڿ��� �� ���� �ϳ��� �����常 ����ϵ��� ���(lock)�Ͽ� ����ȭ�� �����ϴ� �����Դϴ�
//��, ��ȣ ������ ���� ���� ����(race condition)�� ����

void worker(int& result,std::mutex& m) {	
	for (int i = 0; i < 10000; i++) {
		//std::lock_guard<std::mutex> lock(m)  -> lock �����ÿ� m.lock ����   -> scope �� ���� ������ lock �Ҹ� -> m.unlock �ڵ� ���� 
		m.lock();            // �Ӱ� ���� ����: ���ؽ��� ��� �ٸ� ������ ���� ����
		result += 1;         // ���� ���� result�� 1 ������Ű�� �۾� (�Ӱ� ����)
		m.unlock();          // �Ӱ� ���� ��: ���ؽ� ��� ����
	}
	//unlock�� ������ ���ؽ��� Ǯ���� �ʾ� ��� �����尡 ��� ���¿� ������, �ƹ� �۾��� �� �ϴ� ��Ȳ�� ������̶�� �մϴ�.
}

int main() {
	int counter = 0; 
	vector<thread> workers;
	std::mutex m;		 // ���ؽ� ��ü, ���� ���� ��ȣ��

	for (int i = 0; i < 4; i++)
		workers.push_back(thread(worker, std::ref(counter),std::ref(m)));

	for (int i = 0; i < 4; i++)
		workers[i].join();

	std::cout << "Counter �� : " << counter << std::endl;
}
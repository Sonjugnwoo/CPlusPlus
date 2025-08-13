#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using std::vector;
using std::thread;
using std::queue;


std::condition_variable cv; // ������ �� ��ȣ ���޿� ���Ǻ���
std::mutex m;               // ������ ��ȣ�� ���� mutex
bool done = false;          // �۾� �Ϸ� ���� ǥ�� �÷���

void worker(int i) {

}

int main() {
	vector<std::thread> bathroom; 
	bathroom.reserve(5);          // 5�������� ���ٰ� ����

	queue<std::function<void>> job;

	for (int i = 0; i < 5; i++)
		bathroom.emplace_back(worker, i);
}
//memory_order_acquire	�ش� ��� �ڿ� ���� ��� �޸� ��ɵ��� �ش� ��� ���� ���ġ �Ǵ°��� ���� .
//memory_order_release	�ش� ��� ������ ��� �޸� ��ɵ��� �ش� ��� ���ķ� ���ġ �Ǵ� ���� ���� , ���� ������ acquire���� �д� �����尡 �ִٸ� ��� ��ɵ��� ���� �� �� �־���� 
//���� ������ release , acquire �� ���ؼ� ����ȭ�� ���� 

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<bool> ready;
std::atomic<int> data[3];

void produ() {
	// ������ ������� relaxed ���� data �迭�� �� ����
	data[0].store(1, std::memory_order_relaxed);
	data[1].store(2, std::memory_order_relaxed);
	data[2].store(3, std::memory_order_relaxed);

	// data ���Ⱑ ��� ���� �� ready ������ true ����
    // memory_order_release: �� store ������ ��� �޸� ���� ������ ���� store ���ķ� ���ġ�Ǵ� ���� ������ (���� ����)
	ready.store(true, std::memory_order_release);
}

void consu() {
	// memory_order_acquire: �� load ������ ��� �޸� �б�/���� �������� load �������� ���ġ�� �� ���� (���� ����)
	while(!ready.load(std::memory_order_acquire)){}

	// ready�� true�� �Ǿ����Ƿ�, produ()���� ������ data ������ "�����" ����
	// relaxed ���� �д���, acquire-release ���� ���п� ������ ���������� ������
	std::cout << "Data[0] : " << data[0].load(std::memory_order_relaxed) << std::endl;
	std::cout << "Data[1] : " << data[1].load(std::memory_order_relaxed) << std::endl;
	std::cout << "Data[2] : " << data[2].load(std::memory_order_relaxed) << std::endl;
}

void producer(std::atomic<bool>* is_ready, int* data) {
	*data = 10;

	// is_ready�� �޸� ���� release�� true ���� (����ȭ ��ȣ)
	is_ready->store(true, std::memory_order_release);		
}

void consumer(std::atomic<bool>* is_ready, int* data) {
	while (!is_ready->load(std::memory_order_acquire)) {  // true�� �Ǹ� producer�� data�� ��ٴ� �ǹ��̹Ƿ�, data �� �б� ����
	}

	std::cout << "Data : " << *data << std::endl;
}

int main() {
	std::vector<std::thread> threads;

	std::atomic<bool> is_ready(false);
	int data = 0;

	threads.push_back(std::thread(producer, &is_ready, &data));
	threads.push_back(std::thread(consumer, &is_ready, &data));

	for (int i = 0; i < 2; i++)
		threads[i].join();

	std::cout << "--------------------------" << std::endl;

	std::vector<std::thread> threads2;

	threads2.push_back(std::thread(produ));
	threads2.push_back(std::thread(consu));

	for (int i = 0; i < 2; i++)
		threads2[i].join();

}

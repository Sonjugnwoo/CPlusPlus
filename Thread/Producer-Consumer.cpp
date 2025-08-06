// ������(Producer) - ó���� ���� �����ϰų� �޾ƿͼ� �۾� ť�� �ִ� ������
// �Һ���(Consumer) - �۾� ť���� ���� ���� ������ ó���ϴ� ������

#include <iostream>
#include <chrono>                // �ð� ���� ���̺귯��
#include <mutex>                 // std::mutex, std::lock_guard, std::unique_lock
#include <queue>                 // std::queue (FIFO �ڷᱸ��)
#include <condition_variable>    // std::condition_variable (������ �� ����ȭ)
#include <string>
#include <vector>
#include <thread>                // std::thread

// ������ �Լ� (������Ʈ���� ������ ��� �ٿ�ε� ����)
void producer(std::queue<std::string>* download_pages, std::mutex* m, int idx,std::condition_variable* cv) {
	for (int i = 0; i < 5; i++) {
		std::this_thread::sleep_for(std::chrono::microseconds(100 * idx));		//sleep_for -> ���ڷ� ���� ���� �ð��� ŭ �����带 sleep 
		std::string content = " ������Ʈ : " + std::to_string(i) + " from thread(" + std::to_string(idx) + ")\n";
		
		// ���ؽ� ��� (lock_guard�� �ڵ����� ���ؽ� ����)
		std::lock_guard<std::mutex> lock(*m);
		download_pages->push(content);  // ���� ť�� ������ �߰�
	}
	// �Һ��ڿ��� ���ο� �����Ͱ� �غ������ �˸� (��� ���� ������ �����)
	cv->notify_one();
	
}

// ��ȿ������ busy-wait ����� �Һ��� �Լ�
void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m, int* num_processed) {
	// ó���� ������ ������ 25���� �� ������ �ݺ�
	while (*num_processed < 25) {
		m->lock(); // ���ؽ� ��� (���� ť ��ȣ)

		if (downloaded_pages->empty()) { // ���� ť�� ���������
			m->unlock();  // ���ؽ� ���� (�ٸ� �����尡 ť�� ���� �����ϵ���)

			// 10�и��� ��� (��� ��� �� �ٽ� üũ)
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			continue; // �ٽ� ���� ó������ �̵��Ͽ� ť Ȯ��
		}

		// ť�� �����Ͱ� ������
		std::string content = downloaded_pages->front(); // ť ���� �����͸� ����
		downloaded_pages->pop(); // ť���� �ش� ������ ����

		(*num_processed)++; // ó���� ���� ����

		m->unlock(); // ���ؽ� ���� (�ٸ� ������ ���� ����)

		std::cout << content; // ������ ���

		// �ణ�� ó�� �ð� �ֱ� (80����ũ����)
		std::this_thread::sleep_for(std::chrono::microseconds(80));
	}
}

// �Һ��� �Լ� (condition_variable ��� ȿ���� ��� ���)
void consumer_2(std::queue<std::string>* downloaded_pages, std::mutex* m, int* num_processed, std::condition_variable* cv) {
	while (*num_processed < 25) {
		std::unique_lock<std::mutex> lk(*m); // ���ؽ� ��� (unique_lock: lock/unlock �����ο�)

		// ť�� ������� ���, �����Ͱ� �ְų� ó�� ���� 25�� �����ϸ� ���
		cv->wait(lk, [&] { return !downloaded_pages->empty() || *num_processed == 25; });

		// 25�� ó�� �Ϸ� �� ���� (�ٸ� �Һ��ڵ� ���� �� �ֵ��� unlock �� ����)
		if (*num_processed == 25) {
			lk.unlock();
			return;
		}

		// ť���� ������ ������
		std::string content = downloaded_pages->front();
		downloaded_pages->pop();

		(*num_processed)++; // ó�� ���� ����

		lk.unlock(); // ������ ó���ϸ鼭 ���ؽ� Ǯ�� �ٸ� �����尡 ���� �����ϵ��� ��

		// ó���� ���� ��� �� �ణ�� �۾� ����
		std::cout << content;
		std::this_thread::sleep_for(std::chrono::microseconds(80));
	}
}
int main() {
	std::queue<std::string> download_pages;
	std::mutex m;
	std::condition_variable cv;

	std::vector<std::thread> producers;
	for (int i = 0; i < 5; i++)
		producers.push_back(std::thread(producer, &download_pages, &m, i + 1,&cv));

	int num_processed = 0; 
	std::vector<std::thread> consumers;
	for (int i = 0; i < 5; i++)
		consumers.push_back(std::thread(consumer_2, &download_pages, &m,&num_processed,&cv));

	for (int i = 0; i < 5; i++)
		producers[i].join();

	// ������ ���� �Ŀ��� �Һ��ڴ� ��� ���� �� �����Ƿ�, ���� ���� �����
	cv.notify_all();

	for (int i = 0; i < 5; i++)
		consumers[i].join();
}
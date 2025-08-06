//atomicity �߰��� �ٸ� �����尡 ����� ������ ���� ���� ���� ( ��ġ ���� ó�� �ɰ� �� ����)

#include <atomic>      // std::atomic ����� ���� ���
#include <iostream>
#include <thread>
#include <vector>

// worker �Լ�: atomic ī���͸� 10000�� ������Ű�� �۾�
void worker(std::atomic<int>& counter) {
    for (int i = 0; i < 10000; i++)
        counter++;  // ������(atomic)���� counter �� 1 ����
}

int main() {
    std::atomic<int> counter(0);  // atomic ������ ���� counter�� 0���� �ʱ�ȭ

    std::vector<std::thread> workers;  // ������ ��ü�� ������ ���� ����

    // 4���� �����带 �����Ͽ� worker �Լ� ����, counter�� ������ ����
    for (int i = 0; i < 4; i++)
        workers.push_back(std::thread(worker, std::ref(counter)));

    // ��� �����尡 ����� ������ ���� �����尡 ��ٸ�(join)
    for (int i = 0; i < 4; i++)
        workers[i].join();

    // ���� ��� ��� (4���� �����尡 ���� 10000���� �����������Ƿ� 40000)
    std::cout << "Counter = " << counter << std::endl;
}
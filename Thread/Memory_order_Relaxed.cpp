//memory_order_relaxed CPU ���� �޸� ���� ������ �����ؼ� ������ ������ �ִ� �Ͱ� ���� ���п� �ſ� �����ӵ��� CPU���� ���� 

#include <atomic>      // std::atomic ����� ���� ���
#include <iostream>
#include <thread>
#include <vector>

void worker(std::atomic<int>* counter) {
    for (int i = 0; i < 10000; i++)
        counter->fetch_add(1, std::memory_order_relaxed);   // ���� ���� ���� ������ ����
}

// t1 �Լ�: atomic ���� b�� 1 ����, a ���� �о� ���
void t1(std::atomic<int>* a, std::atomic<int>* b) {
    b->store(1, std::memory_order_relaxed);  // relaxed ������ b�� 1 ����
    int x = a->load(std::memory_order_relaxed);  // relaxed ������ a �� ����

    printf("x : %d\n", x);
}

// t2 �Լ�: atomic ���� a�� 1 ����, b ���� �о� ���
void t2(std::atomic<int>* a, std::atomic<int>* b) {
    a->store(1, std::memory_order_relaxed);  // relaxed ������ a�� 1 ����
    int y = b->load(std::memory_order_relaxed);  // relaxed ������ b �� ����

    printf("y : %d\n", y);
}

int main() {

    std::vector<std::thread> threads;

    std::atomic<int> a(0);  // atomic ���� a �ʱ�ȭ 0
    std::atomic<int> b(0);  // atomic ���� b �ʱ�ȭ 0

    // t1, t2 �� ������ �����Ͽ� �޸� ���� �׽�Ʈ
    threads.push_back(std::thread(t1, &a, &b));
    threads.push_back(std::thread(t2, &a, &b));

    // �� ������ ���� ���
    for (int i = 0; i < 2; i++)
        threads[i].join();

    std::vector<std::thread> threads2;

    std::atomic<int> counter(0);

    for (int i = 0; i < 4; i++)
        threads2.push_back(std::thread(worker, &counter));

    for (int i = 0; i < 4; i++)
        threads2[i].join();

    // ���� counter �� ��� (4 * 10000 = 40000 ���)
    std::cout << "Counter = " << counter << std::endl;
}
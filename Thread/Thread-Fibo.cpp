#include <iostream>
#include <thread>
#include <vector>

using std::thread;
using std::vector;

// �Ǻ���ġ ������ ����ϴ� �Լ�
int Fibo(int n, int depth = 0) {		// depth: ����ȭ ���� ������ ���� �Ķ���� (��� ȣ�� ���� üũ)
	if (n <= 1) return n;			    // ���̽� ���̽�: n�� 0 �Ǵ� 1�̸� �� ���� �״�� ��ȯ
	
	if (depth > 2)	 // ����ȭ�� ���� 2������ ����ϰ�, �� ���Ŀ��� ���� ������ ��� ȣ��� ó��
		return Fibo(n - 1, depth + 1) + Fibo(n - 2, depth + 1);

	int x, y;
	// �����带 �ϳ� �����Ͽ� fib(n-1)�� ���� ���
	// ���� �Լ��� ȣ��, ĸó ����Ʈ�� x�� ������ ����
	thread t1([&]() {x = Fibo(n - 1, depth + 1); });

	y = Fibo(n - 2, depth + 1);	//���� �����忡���� fib(n-2)�� ���

	t1.join();	   // ���� �����尡 ���� ������ ���(����ȭ)

	return x + y;
}


int main() {
	int size = 20;
	std::cout << "fib(" << size << ") = " << Fibo(size) << std::endl;
}
#include <iostream>

// constexpr �Լ�: ������ Ÿ�ӿ� �򰡵� �� �ִ� ���丮�� �Լ�
constexpr int Factorial(int n) {
	int total = 1;
	for (int i = 1; i <= n; i++)
		total *= i;

	return total;
}

template <int N>
struct A {
	int operator ()() { return N; }
};

int main() {
	// Factorial(5)�� ������ Ÿ�ӿ� 5! = 120���� ����
	A<Factorial(5)> a;

	std::cout << a() << std::endl;
}
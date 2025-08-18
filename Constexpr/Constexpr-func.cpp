#include <iostream>

// constexpr 함수: 컴파일 타임에 평가될 수 있는 팩토리얼 함수
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
	// Factorial(5)는 컴파일 타임에 5! = 120으로 계산됨
	A<Factorial(5)> a;

	std::cout << a() << std::endl;
}
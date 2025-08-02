#include <functional>
#include <iostream>
#include <string>

class A {
	int c;

public:
	A(int c) : c(c) {}
	int some_func() {
		std::cout << "�� ��� �Լ�" << std::endl;
		return c;
	}
	int some_const_func() const {
		std::cout << "��� �Լ�" << std::endl;
		return c;
	}

	static void st() {}
};


int main() {
	A a(5);	// A ��ü ����, c=5�� �ʱ�ȭ

	std::function<int(A&)> f1 = &A::some_func;
	// ��-��� ��� �Լ� some_func�� std::function�� ����
    // ȣ�� �� A ��ü�� ������ ù ��° ���ڷ� �޾� ȣ���
    // (��: f1(a) �� a.some_func() ȣ��)

	std::function<int(const A&)> f2 = &A::some_const_func;
	// ��� ��� �Լ� some_const_func�� std::function�� ����
    // const A& Ÿ�� ������ �޾� ȣ�� ����

	f1(a);
	f2(a);
}
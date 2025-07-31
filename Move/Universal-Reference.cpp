#include <iostream>

// ������ ���۷����� �޴� ���¸� ������ ���۷������ �� 

template <typename T>
void wrapper(T&& u) {	//�� ���ø� Ÿ���� ������ ���۷����� �������� ���� �� ���� 
	g(std::forward<T>(u)); //forward -> ������ ���������� �����ؼ� �������ִ� ĳ���� �Լ� 
}

class A {};

void g(A& a) { std::cout << "������ ���۷���" << std::endl; }				//A& a : ��-const ������ ����(lvalue reference)
void g(const A& a) { std::cout << "������ ��� ���۷���" << std::endl; }	//const A& a : ��� ������ ����(const lvalue reference)
void g(A&& a) { std::cout << "������ ���۷���" << std::endl; }				//A&& a : ������ ����(rvalue reference)

int main() {
	A a;
	const A ca;

	std::cout << "���� -----------" << std::endl;

	g(a);    // A a;               -> "������ ���۷���"
	g(ca);   // const A ca;        -> "������ ��� ���۷���"
	g(A());  // �ӽ� ��ü           -> "������ ���۷���"

	std::cout << " wrapper ��  -----------" << std::endl;


	wrapper(a);		
	wrapper(ca);		
	wrapper(A());		
}
#include <iostream>
#include <vector>

template <typename T>
void wrapper(T u) {
	g(u);
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

	// ���ø� Ÿ���� �߷��� �� T�� ���۷����� �ƴ� �Ϲ����� Ÿ���̶�� const ����  T -->> class A�� �߷� 

	wrapper(a);			// T -> AŸ������ �߷� (���۷��� X)
	wrapper(ca);		// T - >A�� �߷� (const ����)
	wrapper(A());		// A() -> rvalue ������ T - > A�߷� 
}
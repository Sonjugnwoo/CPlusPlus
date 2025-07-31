#include <iostream>
#include <vector>

template <typename T>
void wrapper(T u) {
	g(u);
}

class A {};
		
void g(A& a) { std::cout << "좌측값 레퍼런스" << std::endl; }				//A& a : 비-const 좌측값 참조(lvalue reference)
void g(const A& a) { std::cout << "좌측값 상수 레퍼런스" << std::endl; }	//const A& a : 상수 좌측값 참조(const lvalue reference)
void g(A&& a) { std::cout << "우측값 레퍼런스" << std::endl; }				//A&& a : 우측값 참조(rvalue reference)

int main() {
	A a;
	const A ca;

	std::cout << "원본 -----------" << std::endl;

	g(a);    // A a;               -> "좌측값 레퍼런스"
	g(ca);   // const A ca;        -> "좌측값 상수 레퍼런스"
	g(A());  // 임시 객체           -> "우측값 레퍼런스"

	std::cout << " wrapper 후  -----------" << std::endl;

	// 템플릿 타입을 추론할 때 T가 레퍼런스가 아닌 일반적인 타입이라면 const 무시  T -->> class A로 추론 

	wrapper(a);			// T -> A타입으로 추론 (레퍼런스 X)
	wrapper(ca);		// T - >A로 추론 (const 무시)
	wrapper(A());		// A() -> rvalue 하지만 T - > A추론 
}
#include <iostream>

// 우측값 레퍼런스를 받는 형태를 보편적 레퍼런스라고 함 

template <typename T>
void wrapper(T&& u) {	//단 템플릿 타입의 보편적 레퍼런스는 좌측값도 받을 수 있음 
	g(std::forward<T>(u)); //forward -> 인자의 원래성질을 보존해서 전달해주는 캐스팅 함수 
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


	wrapper(a);		
	wrapper(ca);		
	wrapper(A());		
}
#include <functional>
#include <iostream>
#include <string>

class A {
	int c;

public:
	A(int c) : c(c) {}
	int some_func() {
		std::cout << "비 상수 함수" << std::endl;
		return c;
	}
	int some_const_func() const {
		std::cout << "상수 함수" << std::endl;
		return c;
	}

	static void st() {}
};


int main() {
	A a(5);	// A 객체 생성, c=5로 초기화

	std::function<int(A&)> f1 = &A::some_func;
	// 비-상수 멤버 함수 some_func를 std::function에 저장
    // 호출 시 A 객체의 참조를 첫 번째 인자로 받아 호출됨
    // (예: f1(a) → a.some_func() 호출)

	std::function<int(const A&)> f2 = &A::some_const_func;
	// 상수 멤버 함수 some_const_func를 std::function에 저장
    // const A& 타입 참조를 받아 호출 가능

	f1(a);
	f2(a);
}
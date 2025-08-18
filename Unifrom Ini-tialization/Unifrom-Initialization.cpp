#include <iostream>

class A {
public:
	A(int x) { std::cout << "A생성자 호출" << std::endl; }
};

A func() {
	return { 3 };	// A(3)과 같아서 임시 객체 생성 후 반환 
}

int main() {
	A a{3}; // 균일 초기화. int형 변수만 들어올 수 있음

	func(); 
}
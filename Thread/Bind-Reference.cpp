#include <functional>
#include <iostream>

//Ref -> 기존 객체를 참조로 감싸는 역할 bind같이 함수 객체를 만들때 기본적으로 인자가 복사 전달인데  참조가 전달 되도록 함 

struct S {
	int data;
	S(int data) : data(data) { std::cout << "일반 생성자 " << std::endl; }
	S(const S& s) {
		std::cout << "복사 생성자 " << std::endl;
		data = s.data;
	}

	S(S&& s) { 
		std::cout << "이동 생성자" << std::endl;
		data = s.data;
	}
};

void something(S& s1, const S& s2) { s1.data = s2.data + 3; }

int main() {
	S s1(1), s2(2);		 // s1.data=1, s2.data=2

	std::cout << "before : " << s1.data << std::endl;

	// std::bind를 사용해 함수 something 에 첫번째 인자를 참조로 고정하고,
	// 두번째 인자는 나중에 호출 시 받아들이는 함수 객체 temp 생성
	auto temp = std::bind(something, std::ref(s1), std::placeholders::_1);

	temp(s2);	//temp(s2) 호출하면 something(s1, s2) 호출됨.

	std::cout << "after : " << s1.data << std::endl;
}
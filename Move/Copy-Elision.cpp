﻿#include <iostream>

class A {
	int data_;

public:
	A(int data) : data_(data) {
		std::cout << "일반 생성자 호출" << std::endl;
	}

	A(const A& a) : data_(a.data_) {
		std::cout << "복사 생성자 호출" << std::endl;
	}
};

int main() {
	A a(1);		//일반 생성자 호출
	A b(a);		//복사 생성자 호출

	A c(A(2));  // 일반 생성자 호출 (복사생략: c를 직접 생성, 복사 생성자 없음)
}
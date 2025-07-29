#include <iostream>
#include <stdexcept>

// 리소스 관리를 담당하는 클래스
// 생성자에서 예외가 발생 시에 소멸자가 호출 되지 않는다 
class Resource {
	int id_;

public:
	Resource(int id) : id_(id) {}

	~Resource() {
		std::cout << "리소스 해제" << id_ << std::endl;
	}

};

int func3() {
    Resource r(3);                          // id 3인 Resource 객체 생성
    throw std::runtime_error("Exception from 3!\n");  // 예외 발생

    // → 예외 발생으로 인해 이 함수 종료되고 스택이 unwind 됨
    // 호출 스택이 풀리면서 func3() 내 지역 변수 r(3)의 소멸자 호출됨
    return 0;                              // 도달하지 않음
}

int func2() {
    Resource r(2);      // id 2인 Resource 객체 생성
    func3();            // func3 호출

    // func3()에서 예외가 발생해 이 라인까지는 도달하지 못함
    // 호출 스택이 unwind 되면서 func2() 내 지역 객체 r(2)의 소멸자 호출됨

    std::cout << "실행 안됨 " << std::endl;  // 예외 발생 시 실행 안 됨
    return 0;
}

int func() {
    Resource r(1);      // id 1인 Resource 객체 생성
    func2();            // func2 호출

    // func2()에서 예외가 전파되어 이 라인도 실행되지 않음
    // 호출 스택 unwind 후 func() 내의 r(1) 소멸자 호출됨

    std::cout << "실행 안됨 " << std::endl;  // 예외 발생 시 실행 안 됨
    return 0;
}

int main() {
	try {
		func();
	}
	catch (std::exception& e) {	
		std::cout << "Exception : " << e.what();
	}
}
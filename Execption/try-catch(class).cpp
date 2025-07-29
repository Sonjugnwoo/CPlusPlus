#include <exception>
#include <iostream>

// 예외의 기본 클래스 역할을 하는 Parent
class Parent : public std::exception {
public:
	// 예외 메시지 반환, noexcept 명시하여 예외 안 던짐을 보장
	virtual const char* what() const noexcept override {
		return "Parent!\n";
	}
};

// Parent를 상속한 Child 클래스 (더 구체적인 예외)
class Child : public Parent {
public:
	// Parent의 what() 함수 오버라이드
	const char* what() const noexcept override {
		return "Child!\n";
	}
};

int func(int c) {
	if (c == 1)throw Parent();
	else if (c == 2) throw Child();

	return 0;
}

int main() {
	int c;
	std::cin >> c;

	try {
		func(c);
	}
	// Child 타입 예외를 먼저 캐치해야 함 (더 구체적인 타입)
	catch (Child& c) {
		std::cout << "Child Catch!" << std::endl;
		std::cout << c.what();  // "Child!\n" 출력
	}
	// 그 다음으로 Parent 타입 예외 캐치
	catch (Parent& p) {
		std::cout << "Parent Catch!" << std::endl;
		std::cout << p.what();  // "Parent!\n" 출력
	}
}
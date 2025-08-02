#include <functional>
#include <iostream>
#include <string>

//function 은 C++의 모든ㅇ Callable을 마음대로 보관할 수 있는 유용한 객체 

int some_func1(const std::string& a) {
	std::cout << "func1 호출 " << a << std::endl;
	return 0;
}

struct func2 {
	void operator() (char a) { std::cout << "func2 호출 " << a << std::endl; }
};

int main() {
	//function 객체는 템플릿인자로 전달 받을 함수의 타입을 가짐 , 함수의 타입 : (리턴값과 함수의 인자값)

	std::function<int(const std::string&)> f1 = some_func1;	// 리턴 : int , 인자 : std::string

	std::function<void(char)> f2 = func2();	// 리턴 : void , 인자 : char 

	std::function<void()> f3 = []() {std::cout << "func3 호출 " << std::endl; };	//리턴 : X , 인자 : X 

	f1("hello");
	f2('c');
	f3();
}
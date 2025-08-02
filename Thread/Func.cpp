#include <functional>
#include <iostream>
#include <string>

//function �� C++�� ��礷 Callable�� ������� ������ �� �ִ� ������ ��ü 

int some_func1(const std::string& a) {
	std::cout << "func1 ȣ�� " << a << std::endl;
	return 0;
}

struct func2 {
	void operator() (char a) { std::cout << "func2 ȣ�� " << a << std::endl; }
};

int main() {
	//function ��ü�� ���ø����ڷ� ���� ���� �Լ��� Ÿ���� ���� , �Լ��� Ÿ�� : (���ϰ��� �Լ��� ���ڰ�)

	std::function<int(const std::string&)> f1 = some_func1;	// ���� : int , ���� : std::string

	std::function<void(char)> f2 = func2();	// ���� : void , ���� : char 

	std::function<void()> f3 = []() {std::cout << "func3 ȣ�� " << std::endl; };	//���� : X , ���� : X 

	f1("hello");
	f2('c');
	f3();
}
#include <iostream>

//C++에서 호출 가능한 객체(Callables)

struct Callable{	
	void operator() (int a, int b) { std::cout << "a + b = " << a + b << std::endl; }
};

int main() {
	Callable callable;		//Callable 의 객체 callable  

	callable(5, 6);			//함수 처럼 () 을 이용해 호출가능  , callable() (5,6) 를 한것과 같음 

	auto f = [](int a, int b) { std::cout << "a + b = " << a + b << std::endl; };
	f(5, 6);				// 람다 함수 역시 Callable 이라고 할 수 있음 
 }
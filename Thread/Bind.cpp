#include <functional>
#include <iostream>

//Bind -> 원래 함수에 특정 인자를 붙여줌 
//Placeholders -> Bind 에서 나중에 전달될 인자의 위치를 표시하는 자리 표시

void add(int x, int y) {
	std::cout << x << "+" << y << "=" << x + y << std::endl;
}


void subtract(int x, int y) {
	std::cout << x << "-" << y << "=" << x - y << std::endl;
}

int main() {
	// add 함수에서 첫번째 인자를 2로 고정하고, 두번째 인자는 호출 시 받는 형태로 새로운 함수 객체 생성
	auto add_with_2 = std::bind(add, 2, std::placeholders::_1);		 // x=2 고정, y = 첫 번째 인자
	add_with_2(3);   // y = 3 으로 들어감 

	add_with_2(3, 4); // 호출 시 두 개 인자를 주지만, bind가 기대하는 첫 번째 인자만 사용

	//subtract 함수에서 두번째 인자를 2로 고정하고, 첫번째 인자는 호출 시 받는 형태 생성 
	auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);		 // y=2 고정
	auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);	 // subtract 함수의 인자 위치를 바꾸어 호출할 수 있는 함수 객체 생성

	subtract_from_2(3); // x = 3 으로 들어감 
	negate(4, 2);	 // negate(4,2) 호출 → subtract(2,4) 호출
}
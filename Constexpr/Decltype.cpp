// decltype ( 타입을 알고자 하는 식 ) 

#include <iostream>

struct A {
	double d;
};

int main() {
	int a = 3;                         // a: int, 값 = 3
	decltype(a) b = 2;                 // b: int (a와 같은 타입), 값 = 2

	int& r_a = a;                      // r_a: int& (a를 참조), 값 = 3
	decltype(r_a) r_b = b;             // r_b: int& (r_a와 같은 타입), 값 = 2 (b를 참조)

	int&& x = 3;                       // x: int&& (rvalue 참조), 값 = 3
	decltype(x) y = 2;                 // y: int&& (x와 같은 타입), 값 = 2 (rvalue)

	A* aa = new A{ 1.23 };             // aa: A* (A 구조체를 가리키는 포인터), aa->d = 1.23
	decltype(aa->d) dd = 0.1;          // dd: double (d의 타입), 값 = 0.1

	//결과 출력 
	std::cout << "a = " << a << std::endl;           // 3
	std::cout << "b = " << b << std::endl;           // 2
	std::cout << "r_a = " << r_a << std::endl;       // 3
	std::cout << "r_b = " << r_b << std::endl;       // 2
	std::cout << "x = " << x << std::endl;           // 3
	std::cout << "y = " << y << std::endl;           // 2
	std::cout << "aa->d = " << aa->d << std::endl;   // 1.23
	std::cout << "dd = " << dd << std::endl;         // 0.1

	delete aa;
	return 0;
}
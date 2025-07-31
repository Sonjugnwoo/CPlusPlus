#include <iostream>
#include <memory>
#include <vector>

class A {
	int* data;

public:
	A() {
		data = new int[100];
		std::cout << "자원 획득" << std::endl;
	}

	~A() {
		std::cout << "소멸자 호출" << std::endl;
		delete[] data;
	}
};

// 클래스 B는 std::enable_shared_from_this를 상속받아, 객체 내부에서 자신에 대한 shared_ptr를 안전하게 얻음
class B : public std::enable_shared_from_this<B> {
	int* data;

public:
	B() {
		data = new int[100];
		std::cout << "자원 획득" << std::endl;
	}

	~B() {
		std::cout << "소멸자 호출" << std::endl;
		delete[] data;
	}

	std::shared_ptr<B> get_shared_ptr() { return shared_from_this(); }	//std::enable_shared_from_this<B>의 shared_from_this() 호출
};

int main() {
	std::vector<std::shared_ptr<A>> vec1;				// A 객체를 공유하는 스마트 포인터를 저장하는 벡터 생성
	vec1.push_back(std::shared_ptr<A>(new A()));		// vec1에 새 A 객체를 가리키는 shared_ptr 추가 ,  new A()로 동적 생성된 객체를 shared_ptr가 소유 관리
	

	std::cout << "소멸" << std::endl;		  // vec1의 첫 번째 요소를 지우면서 shared_ptr 소멸 , 참조 카운트 0이 되어 내부 A 객체 소멸
	vec1.erase(vec1.begin());


	std::shared_ptr<A> p1(new A());			 // p1은 새 A 객체 소유, 참조 카운트 1
	std::shared_ptr<A> p2(p1);				 // p2는 p1을 복사해 같은 객체 공유, 참조 카운트 2

	// p1과 p2 모두 같은 객체를 가리키므로 참조 카운트는 2
	std::cout << p1.use_count() << std::endl;  // 출력: 2
	std::cout << p2.use_count() << std::endl;  // 출력: 2

	std::shared_ptr<A> p3 = std::make_shared<A>();	  // p3는 make_shared를 사용해 새 A 객체 생성 및 소유

	std::shared_ptr<B> pa1 = std::make_shared<B>();
	std::shared_ptr<B> pa2 = pa1->get_shared_ptr();		//두 shared_ptr가 같은 객체를 안전하게 공유함

	std::cout << pa1.use_count() << std::endl;  // 출력: 2
	std::cout << pa2.use_count() << std::endl;  // 출력: 2
}
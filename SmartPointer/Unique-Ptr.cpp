#include <iostream>
#include <memory>

//unique_ptr: 복사 X, 오직 한 곳에서만 소유권을 가지며, 소유권 이전(move)은 가능 .안전한 자동 해제(메모리 누수, double free 방지에 탁월).
//			  명시적으로 복사 생성자가 삭제되어 있음 
//double free : 소유권이 불명확한 '원시 포인터' 코딩에서 흔히 발생.스마트 포인터가 소유권을 명확히 관리하여 double free 버그를 예방.

class A {
	int* data;

public:
	A() {
		std::cout << "자원 획득" << std::endl;
		data = new int[100];
	}

	void some() { std::cout << "일반 포인터와 동일하게 사용 가능" << std::endl; }

	void do_sth(int a) {
		std::cout << "아 묻 따 " << std::endl;
		data[0] = a;
	}

	~A() {
		std::cout << "자원 해제" << std::endl;
		delete[] data;
	}
};

void do_something() {
	std::unique_ptr<A> pa(new A());			// pa는 new A()로 생성한 객체를 소유(관리)하는 스마트 포인터
	std::cout <<"pa : ";
	pa->some();								//pa를 포인터 처럼 사용

	//pa -> pb 로 소유권이전 
	std::unique_ptr<A> pb = std::move(pa);	// pb = pa 사용 시 복사 시도 시 컴파일 오류 발생   , pa는 더 이상 객체를 소유하지 않으며 내부 포인터가 nullptr 상태가 됩니다
	std::cout << "pb : ";
	pb->some();
}

void do_something(A* ptr) { ptr->do_sth(3); }	  // 소유권은 넘기지 않고, 단순히 객체 접근 권한만 부여


int main() {
	std::unique_ptr<A> pc(new A());
	do_something(pc.get());			//get 함수를 호출 하면 실제 객체의 주소값을 리턴 , 소유권을 넘겨주지 않고 단순히 주소값(원시 포인터)만 반환해, 함수내 객체 접근만 허용한다

	do_something();					 // do_something 종료 시 pa 소멸자 호출 → 자동으로 delete 호출

}
#include <iostream>
#include <vector>

// 만들어본 스마트 포인터(MyUniquePtr) 템플릿 클래스
// 동적 배열(T*)의 소유권을 관리하며, 복사 금지, 이동 허용 방식을 구현
template <typename T>
class MyUniquePtr {
	T* ptr;	//소유 포인터

public:
	MyUniquePtr() :ptr(nullptr) {}	//기본 생성자 초기상태 nullptr
	MyUniquePtr(T* p) : ptr(p) {}	//포인터 인자를 받아 소유 시작 

	MyUniquePtr(const MyUniquePtr& other) = delete;	// 복사 생성자 금지: 복사 불가 (유일 소유권 보장)

	MyUniquePtr(MyUniquePtr&& other) noexcept : ptr(other.ptr) {	//이동 생성자  소유권 이전 ,  원래 소유자는 nullptr 처리 
		other.ptr = nullptr;
	}

	MyUniquePtr& operator = (const MyUniquePtr& other) = delete;	// 복사 대입 연산자 금지: 복사 대입 불가
	MyUniquePtr& operator = ( MyUniquePtr&& other) noexcept {		//이동 대입 연산자: 기존 자원 해제 후 소유권 이전
		if (this != &other) {     // 자기 자신이 아닌 경우에만 처리
			delete[] ptr;          // 기존에 소유한 배열 메모리 해제
			ptr = other.ptr;       // 소유권 이동
			other.ptr = nullptr;   // 이전 소유자 null 처리
		}
		return *this;            
	};

	T& operator *() const { return *ptr;  }	//역참조 연산자: 내부 포인터가 가리키는 배열 첫 요소에 대한 참조 반환
	T* operator ->() const { return ptr; }	//멤버 접근 연산자: 내부 포인터 자체를 반환 (배열의 첫 주소)

	~MyUniquePtr() {	//소멸자: 소유한 메모리 해제, null 체크 후 delete[]
		if (ptr != nullptr)
			delete[] ptr;
	}

	void get_data(T data) {	//내부 데이터 값 설정 함수: 배열 첫 번째 원소에 값 저장
		ptr[0] = data;
 	}

	T* get() const { return ptr; }	//내부 원시 포인터 반환 함수: 외부에서 주소 직접 접근 가능
};

template <typename T>
void data(MyUniquePtr<T>* ptr) {  ptr->get_data(static_cast<T>(3)); }	// // 안전한 타입 캐스팅 후 함수 호출

int main() {
	// 1) 기본 생성자 및 nullptr 상태 테스트
	MyUniquePtr<int> p1;
	std::cout << "p1 초기 상태 포인터: " << p1.get() << std::endl;

	// 2) 포인터 소유 시작 테스트
	MyUniquePtr<int> p2(new int[5]{ 10, 20, 30, 40, 50 });
	std::cout << "p2 초기 값(0번째 요소): " << p2.get()[0] << std::endl;

	// 3) get_data() 멤버 함수 호출 테스트
	data(&p2);
	std::cout << "p2 get_data 후 값(0번째 요소): " << p2.get()[0] << std::endl; // 3 으로 덮어쓰기 됨

	// 4) 이동 생성자 테스트
	MyUniquePtr<int> p3(std::move(p2));
	std::cout << "p3 값(0번째 요소): " << p3.get()[0] << std::endl;
	std::cout << "p2 내부 포인터 값 (이동 후): " << p2.get() << std::endl; // nullptr

	// 5) 이동 대입 연산자 테스트
	MyUniquePtr<int> p4;
	p4 = std::move(p3);
	std::cout << "p4 값(0번째 요소): " << p4.get()[0] << std::endl;
	std::cout << "p3 내부 포인터 값 (이동 후): " << p3.get() << std::endl; // nullptr

	return 0;
}
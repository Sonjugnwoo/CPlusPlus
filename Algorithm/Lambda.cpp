#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

//Lambda   ---> [Capture List](받는 인자) -> 리턴 타입{함수 본체}    (리턴 생략 가능 ) 
//[Capture List] ---> [] : 아무것도 안함 , [&a,b] : a는 레퍼런스 캡쳐 b는 복사본 
//					  [&] : 외부의 모든 변수 레퍼런스 캡쳐 , [=] : 외부의 모든 변수들을 복사본 으로 캡쳐 

template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "]";
		begin++;
	}
	std::cout << std::endl;
}

class SomeClass {
	std::vector<int> vec2;
	int num_delete;

public:
	SomeClass() {
		vec2.push_back(3);
		vec2.push_back(1);
		vec2.push_back(6);
		vec2.push_back(2);
		vec2.push_back(9);
		vec2.push_back(5);

		num_delete = 0;

		std::cout << "SomeClass 생성자 실행 전 vec2: ";
		print(vec2.begin(), vec2.end());
		
		// 람다 캡처 [this]는 this 포인터를 캡처합니다.
		// -> 람다 내부에서 멤버 변수 num_delete에 접근 가능
		vec2.erase(std::remove_if(vec2.begin(), vec2.end(),
			[this](int i) {				//  멤버 변수 num_delete에 접근하기 위해 현재 객체 포인터를 캡처하는 것.
			if (this->num_delete >= 2)
				return false;
			else if (i % 2 == 1) {
				num_delete++;
				return true;
			}
			return false;
		}), vec2.end());

		std::cout << "SomeClass 생성자 실행 후 vec2: ";
		print(vec2.begin(), vec2.end());
	}


};

int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(7);
	vec.push_back(2);
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);

	std::cout << "처음 Vec : ";
	print(vec.begin(), vec.end());

	std::cout << "Vec 홀수 2개만 제거 ";
	int num_erased = 0;	

	vec.erase(std::remove_if(vec.begin(), vec.end(),
		[&num_erased](int i) {			//num_erased 의 레퍼런스를 캡쳐 (함수 내부에서 값 변경 가능 )  & 붙이지 않을시 복사본을 얻는데 형태가 const라 값을 바꿀 수 없음 
		if (num_erased >= 2)
			return false;
		else if (i % 2 == 1) {
			num_erased++;
			return true;
		}
		return false;
		})	,vec.end());

	print(vec.begin(), vec.end());

	std::cout << "\n--- SomeClass 객체 생성 및 vec2 처리 ---\n";
	SomeClass someObject;   // 생성자에서 vec2 처리 및 출력

}
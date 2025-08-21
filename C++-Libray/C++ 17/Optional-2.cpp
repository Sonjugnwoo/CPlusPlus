#include <iostream>
#include <functional>   // std::reference_wrapper, std::ref 포함
#include <optional>     // std::optional 포함
#include <utility>      // (선택적) 유틸리티 헤더

class A {
public:
    int data;           // 멤버 변수 data 선언
};

int main() {
    A a;                // 클래스 A의 인스턴스 생성
    a.data = 1453;      // 멤버 변수 data 초기화

    // std::optional에 std::reference_wrapper로 a 객체 참조를 감싸서 저장
    // 실제 객체를 복사하지 않고 참조를 담음
    std::optional<std::reference_wrapper<A>> maybe_a = std::ref(a);

    // maybe_a에 저장된 참조를 통해 a의 data 값을 변경
    maybe_a->get().data = 3;

    // 변경된 a.data 값을 출력 (3 출력)
    std::cout << "a.data : " << a.data << std::endl;
}
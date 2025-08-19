#include <iostream>


// T::x 타입의 매개변수를 받는 함수 템플릿
template <typename T>
void test(typename T::x a) {
    // T 내부에 x라는 타입이 있을 때만 이 함수가 유효
    // 만약 T::x가 없으면 이 함수는 후보에서 제외됨 (SFINAE 덕분)
    std::cout << "T::x \n";
}

// T::y 타입의 매개변수를 받는 함수 템플릿
template <typename T>
void test(typename T::y b) {
    // T 내부에 y라는 타입이 있을 때만 이 함수가 유효
    // T::y가 없으면 컴파일 오류 대신 이 함수 후보에서 제외됨 (SFINAE)
    std::cout << "T::y \n";
}

// 구조체 A는 중첩 타입 x를 int로 정의
struct A {
    using x = int;
};

// 구조체 B는 중첩 타입 y를 int로 정의
struct B {
    using y = int;
};

int main() {
    test<A>(30); // A::x가 있으므로 첫 번째 함수 템플릿 선택, 출력: T::x
    test<B>(20); // B::y가 있으므로 두 번째 함수 템플릿 선택, 출력: T::y

    // 만약 T에 x, y 모두 없으면 컴파일 오류 발생
    // 예) struct C {}; test<C>(...); 호출 시 오류

}


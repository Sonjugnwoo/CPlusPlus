#include <iostream>
#include <utility>

// T 타입 객체의 멤버 함수 f() 호출 결과 타입을 추론하여 반환하는 템플릿 함수
template <typename T>
decltype(std::declval<T>().f()) call_f_and_return(T& t) {
    return t.f();  // 전달받은 객체 t의 f() 호출 결과 반환
}

struct A {
    int f() { return 0; }   // f()는 int 반환
};

struct B {
    B(int x) {}             // 생성자 (인자 1개 받음)
    int f() { return 0; }   // f()는 int 반환
};

int main() {
    A a;    // A 객체 생성
    B b(1); // B 객체 생성 (생성자 인자 1)

    // call_f_and_return 호출 결과 출력
    std::cout << "call_f_and_return(a) = " << call_f_and_return(a) << std::endl;
    // a.f() 호출 → 0 반환 → 출력

    std::cout << "call_f_and_return(b) = " << call_f_and_return(b) << std::endl;
    // b.f() 호출 → 0 반환 → 출력

    return 0;
}
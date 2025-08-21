#include <iostream>
#include <memory>
#include <variant>

// 구조체 A 정의: a() 함수는 "A" 출력
struct A {
    void a() { std::cout << "A" << std::endl; }
};

// 구조체 B 정의: b() 함수는 "B" 출력
struct B {
    void b() { std::cout << "B" << std::endl; }
};

// is_a가 true면 A 객체, 아니면 B 객체를 포함하는 variant 반환
// monostate는 variant가 아직 값이 없음을 나타낼 수 있는 빈 상태
std::variant<std::monostate, A, B> GetDataFromDB(bool is_a) {
    if (is_a)
        return A();  // A 객체 반환
    return B();      // B 객체 반환
}

int main() {
    // true로 호출하여 variant에 A 객체 저장
    auto v = GetDataFromDB(true);

    // variant 내부에 저장된 타입의 인덱스 출력 (0: monostate, 1: A, 2: B)
    std::cout << v.index() << std::endl;

    // variant에서 A 타입으로 get 하여 a() 멤버 함수 호출
    std::get<A>(v).a();
}
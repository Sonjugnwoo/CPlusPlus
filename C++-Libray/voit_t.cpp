#include <iostream>
#include <type_traits>

// void_t 정의 (C++17부터 std::void_t도 있음)
template<typename...>
using void_t = void;

// 기본 템플릿: T에 멤버 타입 type이 없으면 false
template<typename T, typename = void_t<>>
struct has_type_member : std::false_type {};

// 특수화: T에 멤버 타입 type이 있으면 true
template<typename T>
struct has_type_member<T, void_t<typename T::type>> : std::true_type {};

// 테스트용 구조체
struct A { 
    using type = int; 
};
struct B {};

int main() {
    std::cout << std::boolalpha;
    std::cout << "A has type member? " << has_type_member<A>::value << std::endl;  // true
    std::cout << "B has type member? " << has_type_member<B>::value << std::endl;  // false
}
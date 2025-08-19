#include <iostream>
#include <type_traits>

// T가 정수형(integral) 타입일 때만 활성화되는 함수 템플릿
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
void test(const T& t) {
    // 정수형 타입만 이 함수가 호출될 수 있음
    std::cout << "t : " << t << std::endl;
}

int main() {
    test(1);     // int 타입, 호출 가능, 출력: t : 1
    test(false); // bool 타입도 정수형으로 간주되어 호출 가능, 출력: t : 0
    test('c');   // char 타입도 정수형으로 간주되어 호출 가능, 출력: t : c(아스키 문자 출력)
}
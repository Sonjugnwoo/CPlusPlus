#include <iostream>
#include <type_traits>


template <typename T>
void only_integer(const T& t) {
    static_assert(std::is_integral<T>::value,"Not int");        //static_assert(조건, "메시지") 는 컴파일 때 조건을 검사
    // T가 정수형이 아니면 컴파일 타임 오류 발생합니다.
    std::cout << "T is an integer \n";
}

int main() {
    int n = 5;          // int 타입 변수
    only_integer(n);    // T = int 이므로 조건 통과, 출력: T is an integer

    double d = 5.3;
    only_integer(d);    // 컴파일 에러: T=double, 정수형 아님
}
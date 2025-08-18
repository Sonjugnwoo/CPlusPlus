// constexpr은 컴파일 타임에 값이 확정되는 상수임을 명시하는 키워드다.
#include <iostream>


template <int N>
struct A {
    int operator() () { return N; }
};


int main()
{
    constexpr int size = 3;  // 컴파일 타임 상수
    int arr[size];

    constexpr int N = 10;    // 컴파일 타임 상수
    A < N> a;
    std::cout << a() << std::endl;

    constexpr int number = 3;    // 컴파일 타임 상수
    enum B { x = number,y,z};
    std::cout << B::x << std::endl;
}
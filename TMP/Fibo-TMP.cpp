#include<iostream>


// 재귀적으로 N번째 피보나치 수를 계산하는 템플릿 구조체
template <int N>
struct Fibo {
    // Fibo<N>의 value는 Fibo<N-1>::value 와 Fibo<N-2>::value의 합
    static const int value = Fibo<N - 1>::value + Fibo<N - 2>::value;
};

// 종료조건(기저조건) : Fibo<0>::value는 0
template <>
struct Fibo<0> {
    static const int value = 0;
};

// 종료조건(기저조건) : Fibo<1>::value는 1
template<>
struct Fibo<1> {
    static const int value = 1;
};

int main() {
    std::cout << "10 번째 피보나치 수: " << Fibo<10>::value << std::endl; // 결과: 55
}
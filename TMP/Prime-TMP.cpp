#include <iostream>

// PrimeHelper<X, I> : X를 2~I까지(재귀적으로) 나눠보며 소수인지 판단
template<int X, int I>
struct PrimeHelper {
    // 만약 X가 I로 나누어떨어지면 소수가 아님(false)
    // 그렇지 않으면 I-1로 줄여가며 재귀적으로 검사
    static const bool value = (X % I == 0) ? false : PrimeHelper<X, I - 1>::value;
};

// PrimeHelper<X, 1> : 종료조건(더 이상 검사할 필요 없음, X는 소수)
template<int X>
struct PrimeHelper<X, 1> {
    static const bool value = true;  // 2부터 X-1까지 모두 안 나누어떨어지면 소수(true)
};

// Prime<X> : X가 소수인지 최종 결과를 result로 노출
template <int X>
struct Prime {
    // 2~X-1까지 나누어보는 PrimeHelper를 이용해서 결과 결정
    static const bool result = PrimeHelper<X, X - 1>::value;
};


int main() {
    std::cout << std::boolalpha;    // bool값을 true/false로 출력
    std::cout << "2 Is Prime ?: " << Prime<2>::result << std::endl;    // true
    std::cout << "9 Is Prime ?: " << Prime<9>::result << std::endl;    // false
    std::cout << "17 Is Prime ?: " << Prime<17>::result << std::endl;   // true
}
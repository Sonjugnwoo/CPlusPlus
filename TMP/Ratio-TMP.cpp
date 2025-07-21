#include <iostream>

// 유클리드 호제법을 이용한 최대공약수(GCD) 계산을 컴파일 타임에 수행하는 구조체
template <int X, int Y>
struct GCD {
	// GCD<Y, X % Y>를 재귀적으로 호출 (Y가 0이 될 때까지)
	static const int value = GCD<Y, X% Y>::value;
};

// 특수화: 두 번째 인자(Y)가 0이면 최대공약수는 X
template<int X>
struct GCD<X, 0> {
	static const int value = X;
};
// 항상 약분된 형태로 분수를 표현하는 Ratio 구조체 (N/D)
template <int N, int D = 1>
struct Ratio {
private:
	// 분모와 분자의 최대공약수 계산
	static const int _gcd = GCD<N, D>::value;

public:
	// 약분된 Ratio 타입 (재귀적 타입 사용시 유용)
	typedef Ratio<N / _gcd, D / _gcd> type;

	// 약분된 분자(numerator)
	static const int num = N / _gcd;
	// 약분된 분모(denominator)
	static const int den = D / _gcd;
};

// 두 Ratio(R1, R2)의 합을 계산하는 구조체
template<class R1, class R2>
struct _Ratio_add {
	// (a/b) + (c/d) = (ad + bc) / bd 를 Ratio로 표현 (약분은 Ratio 타입이 자동 처리)
	using type = Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den>;
};

// 덧셈 결과를 곧바로 타입으로 제공 (상속)
template<class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

// 두 Ratio(R1, R2)의 차이를 계산하는 구조체 (뺄셈)
template<class R1, class R2>
struct _Ratio_subtract {
	// (a/b) - (c/d) = (ad - bc) / bd 를 Ratio로 표현
	using type = Ratio<R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
};

template<class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

// 두 Ratio의 곱을 계산하는 구조체
template<class R1, class R2>
struct _Ratio_multiply {
	// (a/b) * (c/d) = (a*c)/(b*d)
	using type = Ratio<R1::num* R2::num, R1::den* R2::den>;
};

template<class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

// 두 Ratio의 나눗셈을 계산하는 구조체
template<class R1, class R2>
struct _Ratio_divide {
	// (a/b) / (c/d) = (a*d)/(b*c)
	using type = Ratio<R1::num* R2::den, R1::den* R2::num>;
};

template<class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};
int main() {
	using r1 = Ratio<2, 3>;
	using r2 = Ratio<3, 2>;

	using r3 = Ratio_add<r1, r2>;
	std::cout << "2/3 + 3/2 = " << r3::num << "/" << r3::den << std::endl;

	using r4 = Ratio_subtract<r1, r2>;
	std::cout << "2/3 - 3/2 = " << r4::num << "/" << r4::den << std::endl;

	using r5 = Ratio_multiply<r1, r2>;
	std::cout << "2/3 * 3/2 = " << r5::num << "/" << r5::den << std::endl;

	using r6 = Ratio_divide<r1, r2>;
	std::cout << "2/3 / 3/2 = " << r6::num << "/" << r6::den << std::endl;
}
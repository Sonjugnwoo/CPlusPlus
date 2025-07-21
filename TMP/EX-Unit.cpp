#include <iostream>
#include <typeinfo>

// 정수 X, Y의 최대공약수(GCD) 계산 - 유클리드 호제법
template <int X, int Y>
struct GCD {
    static const int value = GCD<Y, X% Y>::value;
};

// GCD 종료 조건 (Y==0)
template <int X>
struct GCD<X, 0> {
    static const int value = X;
};

// 기약분수 표현 Ratio<N, D>, 자동으로 약분
template <int N, int D = 1>
struct Ratio {
private:
    const static int _gcd = GCD<N, D>::value;  // 약분용 GCD

public:
    typedef Ratio<N / _gcd, D / _gcd> type;    // 약분한 Ratio 타입
    static const int num = N / _gcd;           // 약분된 분자
    static const int den = D / _gcd;           // 약분된 분모
};

// 분수 덧셈
template <class R1, class R2>
struct _Ratio_add {
    using type = Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den>;
};
// 덧셈 결과 타입
template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

// 분수 뺄셈
template <class R1, class R2>
struct _Ratio_subtract {
    using type = Ratio<R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
};
template <class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

// 분수 곱셈
template <class R1, class R2>
struct _Ratio_multiply {
    using type = Ratio<R1::num* R2::num, R1::den* R2::den>;
};
template <class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

// 분수 나눗셈
template <class R1, class R2>
struct _Ratio_divide {
    using type = Ratio<R1::num* R2::den, R1::den* R2::num>;
};
template <class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};


// 차원(Dim): 질량(M), 길이(L), 시간(T) 각각의 차수를 Ratio로 표현
template <typename U, typename V, typename W>
struct Dim {
    using M = U; // 질량
    using L = V; // 길이
    using T = W; // 시간

    using type = Dim<M, L, T>;
};

// 두 Dim의 각 차원(M/L/T)마다 Ratio_add를 수행하여 차원 결합
template <typename U, typename V>
struct add_dim_ {
    typedef Dim<typename Ratio_add<typename U::M, typename V::M>::type,
        typename Ratio_add<typename U::L, typename V::L>::type,
        typename Ratio_add<typename U::T, typename V::T>::type>
        type;
};
// 두 Dim의 각 차원마다 Ratio_subtract로 차원 뺄셈(예: 속도/가속도 만들 때)
template <typename U, typename V>
struct subtract_dim_ {
    typedef Dim<typename Ratio_subtract<typename U::M, typename V::M>::type,
        typename Ratio_subtract<typename U::L, typename V::L>::type,
        typename Ratio_subtract<typename U::T, typename V::T>::type>
        type;
};

// 실제 값을 저장하고, 차원 타입(D) 지정
template <typename T, typename D>
struct quantity {
    T q;
    using dim_type = D;

    // 같은 차원끼리만 덧셈/뺄셈 허용
    quantity operator+(quantity<T, D> quant) {
        return quantity<T, D>(q + quant.q);
    }
    quantity operator-(quantity<T, D> quant) {
        return quantity<T, D>(q - quant.q);
    }
    // 곱셈 : 차원은 add_dim_으로, 값은 곱하기
    template <typename D2>
    quantity<T, typename add_dim_<D, D2>::type> operator*(quantity<T, D2> quant) {
        return quantity<T, typename add_dim_<D, D2>::type>(q * quant.q);
    }
    // 나눗셈 : 차원은 subtract_dim_으로, 값은 나누기
    template <typename D2>
    quantity<T, typename subtract_dim_<D, D2>::type> operator/(
        quantity<T, D2> quant) {
        return quantity<T, typename subtract_dim_<D, D2>::type>(q / quant.q);
    }
    // 스칼라와 곱셈/나눗셈 (차원은 그대로)
    quantity<T, D> operator*(T scalar) { return quantity<T, D>(q * scalar); }
    quantity<T, D> operator/(T scalar) { return quantity<T, D>(q / scalar); }
    // 생성자
    quantity(T q) : q(q) {}
};

// 출력 연산자 오버로딩: 차원 정보를 함께 출력
template <typename T, typename D>
std::ostream& operator<<(std::ostream& out, const quantity<T, D>& q) {
    out << q.q << "kg^" << D::M::num / D::M::den << "m^" << D::L::num / D::L::den
        << "s^" << D::T::num / D::T::den;
    return out;
}

int main() {
    using one = Ratio<1, 1>;
    using zero = Ratio<0, 1>;

    // 질량: 2kg, 길이: 3m, 시간: 1s (차원은 각각 Dim<...>)
    quantity<double, Dim<one, zero, zero>> kg(2); // 2kg
    quantity<double, Dim<zero, one, zero>> meter(3); // 3m
    quantity<double, Dim<zero, zero, one>> second(1); // 1s

    // F = m * a = kg * m / s^2
    auto F = kg * meter / (second * second);
    std::cout << "2 kg 물체를 3m/s^2 의 가속도로 밀기 위한 힘의 크기는? " << F
        << std::endl;
    // 출력 예시 : "2 kg 물체를 3m/s^2 의 가속도로 밀기 위한 힘의 크기는? 6kg^1m^1s^-2"
}
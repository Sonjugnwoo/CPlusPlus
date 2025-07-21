#include <iostream>
#include <typeinfo>

// ���� X, Y�� �ִ�����(GCD) ��� - ��Ŭ���� ȣ����
template <int X, int Y>
struct GCD {
    static const int value = GCD<Y, X% Y>::value;
};

// GCD ���� ���� (Y==0)
template <int X>
struct GCD<X, 0> {
    static const int value = X;
};

// ���м� ǥ�� Ratio<N, D>, �ڵ����� ���
template <int N, int D = 1>
struct Ratio {
private:
    const static int _gcd = GCD<N, D>::value;  // ��п� GCD

public:
    typedef Ratio<N / _gcd, D / _gcd> type;    // ����� Ratio Ÿ��
    static const int num = N / _gcd;           // ��е� ����
    static const int den = D / _gcd;           // ��е� �и�
};

// �м� ����
template <class R1, class R2>
struct _Ratio_add {
    using type = Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den>;
};
// ���� ��� Ÿ��
template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

// �м� ����
template <class R1, class R2>
struct _Ratio_subtract {
    using type = Ratio<R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
};
template <class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

// �м� ����
template <class R1, class R2>
struct _Ratio_multiply {
    using type = Ratio<R1::num* R2::num, R1::den* R2::den>;
};
template <class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

// �м� ������
template <class R1, class R2>
struct _Ratio_divide {
    using type = Ratio<R1::num* R2::den, R1::den* R2::num>;
};
template <class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};


// ����(Dim): ����(M), ����(L), �ð�(T) ������ ������ Ratio�� ǥ��
template <typename U, typename V, typename W>
struct Dim {
    using M = U; // ����
    using L = V; // ����
    using T = W; // �ð�

    using type = Dim<M, L, T>;
};

// �� Dim�� �� ����(M/L/T)���� Ratio_add�� �����Ͽ� ���� ����
template <typename U, typename V>
struct add_dim_ {
    typedef Dim<typename Ratio_add<typename U::M, typename V::M>::type,
        typename Ratio_add<typename U::L, typename V::L>::type,
        typename Ratio_add<typename U::T, typename V::T>::type>
        type;
};
// �� Dim�� �� �������� Ratio_subtract�� ���� ����(��: �ӵ�/���ӵ� ���� ��)
template <typename U, typename V>
struct subtract_dim_ {
    typedef Dim<typename Ratio_subtract<typename U::M, typename V::M>::type,
        typename Ratio_subtract<typename U::L, typename V::L>::type,
        typename Ratio_subtract<typename U::T, typename V::T>::type>
        type;
};

// ���� ���� �����ϰ�, ���� Ÿ��(D) ����
template <typename T, typename D>
struct quantity {
    T q;
    using dim_type = D;

    // ���� ���������� ����/���� ���
    quantity operator+(quantity<T, D> quant) {
        return quantity<T, D>(q + quant.q);
    }
    quantity operator-(quantity<T, D> quant) {
        return quantity<T, D>(q - quant.q);
    }
    // ���� : ������ add_dim_����, ���� ���ϱ�
    template <typename D2>
    quantity<T, typename add_dim_<D, D2>::type> operator*(quantity<T, D2> quant) {
        return quantity<T, typename add_dim_<D, D2>::type>(q * quant.q);
    }
    // ������ : ������ subtract_dim_����, ���� ������
    template <typename D2>
    quantity<T, typename subtract_dim_<D, D2>::type> operator/(
        quantity<T, D2> quant) {
        return quantity<T, typename subtract_dim_<D, D2>::type>(q / quant.q);
    }
    // ��Į��� ����/������ (������ �״��)
    quantity<T, D> operator*(T scalar) { return quantity<T, D>(q * scalar); }
    quantity<T, D> operator/(T scalar) { return quantity<T, D>(q / scalar); }
    // ������
    quantity(T q) : q(q) {}
};

// ��� ������ �����ε�: ���� ������ �Բ� ���
template <typename T, typename D>
std::ostream& operator<<(std::ostream& out, const quantity<T, D>& q) {
    out << q.q << "kg^" << D::M::num / D::M::den << "m^" << D::L::num / D::L::den
        << "s^" << D::T::num / D::T::den;
    return out;
}

int main() {
    using one = Ratio<1, 1>;
    using zero = Ratio<0, 1>;

    // ����: 2kg, ����: 3m, �ð�: 1s (������ ���� Dim<...>)
    quantity<double, Dim<one, zero, zero>> kg(2); // 2kg
    quantity<double, Dim<zero, one, zero>> meter(3); // 3m
    quantity<double, Dim<zero, zero, one>> second(1); // 1s

    // F = m * a = kg * m / s^2
    auto F = kg * meter / (second * second);
    std::cout << "2 kg ��ü�� 3m/s^2 �� ���ӵ��� �б� ���� ���� ũ���? " << F
        << std::endl;
    // ��� ���� : "2 kg ��ü�� 3m/s^2 �� ���ӵ��� �б� ���� ���� ũ���? 6kg^1m^1s^-2"
}
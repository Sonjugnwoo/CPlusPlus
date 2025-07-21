#include<iostream>


// ��������� N��° �Ǻ���ġ ���� ����ϴ� ���ø� ����ü
template <int N>
struct Fibo {
    // Fibo<N>�� value�� Fibo<N-1>::value �� Fibo<N-2>::value�� ��
    static const int value = Fibo<N - 1>::value + Fibo<N - 2>::value;
};

// ��������(��������) : Fibo<0>::value�� 0
template <>
struct Fibo<0> {
    static const int value = 0;
};

// ��������(��������) : Fibo<1>::value�� 1
template<>
struct Fibo<1> {
    static const int value = 1;
};

int main() {
    std::cout << "10 ��° �Ǻ���ġ ��: " << Fibo<10>::value << std::endl; // ���: 55
}
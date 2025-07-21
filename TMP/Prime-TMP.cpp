#include <iostream>

// PrimeHelper<X, I> : X�� 2~I����(���������) �������� �Ҽ����� �Ǵ�
template<int X, int I>
struct PrimeHelper {
    // ���� X�� I�� ����������� �Ҽ��� �ƴ�(false)
    // �׷��� ������ I-1�� �ٿ����� ��������� �˻�
    static const bool value = (X % I == 0) ? false : PrimeHelper<X, I - 1>::value;
};

// PrimeHelper<X, 1> : ��������(�� �̻� �˻��� �ʿ� ����, X�� �Ҽ�)
template<int X>
struct PrimeHelper<X, 1> {
    static const bool value = true;  // 2���� X-1���� ��� �� ����������� �Ҽ�(true)
};

// Prime<X> : X�� �Ҽ����� ���� ����� result�� ����
template <int X>
struct Prime {
    // 2~X-1���� ������� PrimeHelper�� �̿��ؼ� ��� ����
    static const bool result = PrimeHelper<X, X - 1>::value;
};


int main() {
    std::cout << std::boolalpha;    // bool���� true/false�� ���
    std::cout << "2 Is Prime ?: " << Prime<2>::result << std::endl;    // true
    std::cout << "9 Is Prime ?: " << Prime<9>::result << std::endl;    // false
    std::cout << "17 Is Prime ?: " << Prime<17>::result << std::endl;   // true
}
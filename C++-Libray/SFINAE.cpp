#include <iostream>


// T::x Ÿ���� �Ű������� �޴� �Լ� ���ø�
template <typename T>
void test(typename T::x a) {
    // T ���ο� x��� Ÿ���� ���� ���� �� �Լ��� ��ȿ
    // ���� T::x�� ������ �� �Լ��� �ĺ����� ���ܵ� (SFINAE ����)
    std::cout << "T::x \n";
}

// T::y Ÿ���� �Ű������� �޴� �Լ� ���ø�
template <typename T>
void test(typename T::y b) {
    // T ���ο� y��� Ÿ���� ���� ���� �� �Լ��� ��ȿ
    // T::y�� ������ ������ ���� ��� �� �Լ� �ĺ����� ���ܵ� (SFINAE)
    std::cout << "T::y \n";
}

// ����ü A�� ��ø Ÿ�� x�� int�� ����
struct A {
    using x = int;
};

// ����ü B�� ��ø Ÿ�� y�� int�� ����
struct B {
    using y = int;
};

int main() {
    test<A>(30); // A::x�� �����Ƿ� ù ��° �Լ� ���ø� ����, ���: T::x
    test<B>(20); // B::y�� �����Ƿ� �� ��° �Լ� ���ø� ����, ���: T::y

    // ���� T�� x, y ��� ������ ������ ���� �߻�
    // ��) struct C {}; test<C>(...); ȣ�� �� ����

}


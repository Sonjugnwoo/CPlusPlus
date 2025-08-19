#include <iostream>
#include <utility>

// T Ÿ�� ��ü�� ��� �Լ� f() ȣ�� ��� Ÿ���� �߷��Ͽ� ��ȯ�ϴ� ���ø� �Լ�
template <typename T>
decltype(std::declval<T>().f()) call_f_and_return(T& t) {
    return t.f();  // ���޹��� ��ü t�� f() ȣ�� ��� ��ȯ
}

struct A {
    int f() { return 0; }   // f()�� int ��ȯ
};

struct B {
    B(int x) {}             // ������ (���� 1�� ����)
    int f() { return 0; }   // f()�� int ��ȯ
};

int main() {
    A a;    // A ��ü ����
    B b(1); // B ��ü ���� (������ ���� 1)

    // call_f_and_return ȣ�� ��� ���
    std::cout << "call_f_and_return(a) = " << call_f_and_return(a) << std::endl;
    // a.f() ȣ�� �� 0 ��ȯ �� ���

    std::cout << "call_f_and_return(b) = " << call_f_and_return(b) << std::endl;
    // b.f() ȣ�� �� 0 ��ȯ �� ���

    return 0;
}
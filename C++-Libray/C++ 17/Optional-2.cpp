#include <iostream>
#include <functional>   // std::reference_wrapper, std::ref ����
#include <optional>     // std::optional ����
#include <utility>      // (������) ��ƿ��Ƽ ���

class A {
public:
    int data;           // ��� ���� data ����
};

int main() {
    A a;                // Ŭ���� A�� �ν��Ͻ� ����
    a.data = 1453;      // ��� ���� data �ʱ�ȭ

    // std::optional�� std::reference_wrapper�� a ��ü ������ ���μ� ����
    // ���� ��ü�� �������� �ʰ� ������ ����
    std::optional<std::reference_wrapper<A>> maybe_a = std::ref(a);

    // maybe_a�� ����� ������ ���� a�� data ���� ����
    maybe_a->get().data = 3;

    // ����� a.data ���� ��� (3 ���)
    std::cout << "a.data : " << a.data << std::endl;
}
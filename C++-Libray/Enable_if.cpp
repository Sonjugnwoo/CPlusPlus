#include <iostream>
#include <type_traits>

// T�� ������(integral) Ÿ���� ���� Ȱ��ȭ�Ǵ� �Լ� ���ø�
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
void test(const T& t) {
    // ������ Ÿ�Ը� �� �Լ��� ȣ��� �� ����
    std::cout << "t : " << t << std::endl;
}

int main() {
    test(1);     // int Ÿ��, ȣ�� ����, ���: t : 1
    test(false); // bool Ÿ�Ե� ���������� ���ֵǾ� ȣ�� ����, ���: t : 0
    test('c');   // char Ÿ�Ե� ���������� ���ֵǾ� ȣ�� ����, ���: t : c(�ƽ�Ű ���� ���)
}
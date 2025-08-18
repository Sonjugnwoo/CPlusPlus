#include <iostream>
#include<type_traits>

template <typename T>
void show_value(T t) {
    // if constexpr: ������ Ÿ�ӿ� ���� �Ǵ�
    if constexpr (std::is_pointer<T>::value)  // T�� ������ Ÿ���̶��
        std::cout << "O" << *t << std::endl;  // �����͸� �������ؼ� �� ���
    else  // ������ Ÿ���� �ƴ϶��
        std::cout << "X" << t << std::endl;   // �׳� �� ���
}

int main() {
	int x = 3;
	show_value(x);

	int* p = &x;
	show_value(p);

}
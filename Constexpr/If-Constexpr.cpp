#include <iostream>
#include<type_traits>

template <typename T>
void show_value(T t) {
    // if constexpr: 컴파일 타임에 조건 판단
    if constexpr (std::is_pointer<T>::value)  // T가 포인터 타입이라면
        std::cout << "O" << *t << std::endl;  // 포인터를 역참조해서 값 출력
    else  // 포인터 타입이 아니라면
        std::cout << "X" << t << std::endl;   // 그냥 값 출력
}

int main() {
	int x = 3;
	show_value(x);

	int* p = &x;
	show_value(p);

}
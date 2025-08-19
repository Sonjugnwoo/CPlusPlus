#include <iostream>
#include <type_traits>

// void_t ���� (C++17���� std::void_t�� ����)
template<typename...>
using void_t = void;

// �⺻ ���ø�: T�� ��� Ÿ�� type�� ������ false
template<typename T, typename = void_t<>>
struct has_type_member : std::false_type {};

// Ư��ȭ: T�� ��� Ÿ�� type�� ������ true
template<typename T>
struct has_type_member<T, void_t<typename T::type>> : std::true_type {};

// �׽�Ʈ�� ����ü
struct A { 
    using type = int; 
};
struct B {};

int main() {
    std::cout << std::boolalpha;
    std::cout << "A has type member? " << has_type_member<A>::value << std::endl;  // true
    std::cout << "B has type member? " << has_type_member<B>::value << std::endl;  // false
}
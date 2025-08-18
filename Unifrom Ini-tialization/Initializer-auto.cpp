#include <iostream>
#include <initializer_list>

template<typename T>
void print(std::initializer_list<T> list) {
    for (auto elem : list) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    print({ 1, 2, 3, 4 });  // auto�� std::initializer_list<int> �߷�
    print({ "apple", "banana", "cherry" });  // auto�� std::initializer_list<const char*> �߷�

    return 0;
}
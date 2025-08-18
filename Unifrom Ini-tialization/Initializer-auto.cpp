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
    print({ 1, 2, 3, 4 });  // auto가 std::initializer_list<int> 추론
    print({ "apple", "banana", "cherry" });  // auto가 std::initializer_list<const char*> 추론

    return 0;
}
#include <iostream>
#include <map>
#include <vector>
#include <string>

// 클래스 A는 std::initializer_list<int>를 매개변수로 받는 생성자를 가지고 있음
class A {
public:
    // initializer_list로 받은 각 정수를 한 줄씩 출력하는 생성자
    A(std::initializer_list<int> l) {
        for (auto itr = l.begin(); itr != l.end(); ++itr)
            std::cout << *itr << std::endl;
    }
};

// 벡터의 내용을 출력하는 템플릿 함수
template <typename T>
void print_vector(const std::vector<T>& vec) {
    std::cout << "[";
    // 범위 기반 for문으로 벡터의 각 원소 출력
    for (const auto& e : vec)
        std::cout << e << " ";
    std::cout << "]" << std::endl;
}

// 맵의 내용을 출력하는 템플릿 함수
template <typename K, typename V>
void print_map(const std::map<K, V>& m) {
    // 맵의 모든 (키, 값) 쌍순회하며 출력
    for (const auto& kv : m)
        std::cout << kv.first << " : " << kv.second << " ";
    std::cout << std::endl;
}

int main() {
    // A 객체 a를 initializer_list로 초기화
    // 이때 A의 initializer_list 생성자가 호출되어 리스트의 값들을 출력
    A a = { 1, 2, 3, 5, 6 };

    // 정수형 벡터 v를 중괄호 초기화로 선언 및 초기화
    std::vector<int> v = { 1, 2, 3, 5, 7 };
    // 벡터 v의 내용을 출력
    print_vector(v);

    std::cout << "----------------" << std::endl;

    // 문자열 키, int 값 가지는 맵 m을 중괄호로 초기화
    std::map<std::string, int> m = { {"abc", 3}, {"hi", 2}, {"hello", 5} };
    // 맵 m의 모든 (키, 값) 쌍 출력
    print_map(m);
}
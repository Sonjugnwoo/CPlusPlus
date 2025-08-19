#include <iostream>
#include <vector>
#include <set>
#include <type_traits>

// print 함수 템플릿
// SFINAE를 이용해 Cont가 begin()과 end() 멤버 함수를 가져야만 활성화됨
template <typename Cont,
    typename = decltype(std::declval<Cont>().begin()),       // Cont 타입에 begin()이 있어야 함
    typename = decltype(std::declval<Cont>().end())>         // Cont 타입에 end()가 있어야 함
    void print(const Cont& container) {
    std::cout << "[";
    // Cont의 begin()과 end()를 이용해 반복문 실행
    for (auto it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";  // 컨테이너의 각 원소 출력
    std::cout << "]" << std::endl;
}

int main() {
    std::vector<int> v = { 1, 2, 3, 4, 5 };   // 정수형 벡터 생성
    print(v);                                // 출력: [1 2 3 4 5 ]

    std::vector<char> c = { '1', '4', 'a', 'b', 'c' };  // 문자형 벡터 생성
    print(c);                                // 출력: [1 4 a b c ]

    std::set<int> s = { 3, 1, 4, 2 ,9};    // 정수형 셋 생성
    print(s);                               // 출력: [1 2 3 4 9 ]
}
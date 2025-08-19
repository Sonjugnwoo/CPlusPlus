#include <iostream>
#include <vector>
#include <set>
#include <type_traits>

// print �Լ� ���ø�
// SFINAE�� �̿��� Cont�� begin()�� end() ��� �Լ��� �����߸� Ȱ��ȭ��
template <typename Cont,
    typename = decltype(std::declval<Cont>().begin()),       // Cont Ÿ�Կ� begin()�� �־�� ��
    typename = decltype(std::declval<Cont>().end())>         // Cont Ÿ�Կ� end()�� �־�� ��
    void print(const Cont& container) {
    std::cout << "[";
    // Cont�� begin()�� end()�� �̿��� �ݺ��� ����
    for (auto it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";  // �����̳��� �� ���� ���
    std::cout << "]" << std::endl;
}

int main() {
    std::vector<int> v = { 1, 2, 3, 4, 5 };   // ������ ���� ����
    print(v);                                // ���: [1 2 3 4 5 ]

    std::vector<char> c = { '1', '4', 'a', 'b', 'c' };  // ������ ���� ����
    print(c);                                // ���: [1 4 a b c ]

    std::set<int> s = { 3, 1, 4, 2 ,9};    // ������ �� ����
    print(s);                               // ���: [1 2 3 4 9 ]
}
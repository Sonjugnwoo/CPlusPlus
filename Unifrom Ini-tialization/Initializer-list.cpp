#include <iostream>
#include <map>
#include <vector>
#include <string>

// Ŭ���� A�� std::initializer_list<int>�� �Ű������� �޴� �����ڸ� ������ ����
class A {
public:
    // initializer_list�� ���� �� ������ �� �پ� ����ϴ� ������
    A(std::initializer_list<int> l) {
        for (auto itr = l.begin(); itr != l.end(); ++itr)
            std::cout << *itr << std::endl;
    }
};

// ������ ������ ����ϴ� ���ø� �Լ�
template <typename T>
void print_vector(const std::vector<T>& vec) {
    std::cout << "[";
    // ���� ��� for������ ������ �� ���� ���
    for (const auto& e : vec)
        std::cout << e << " ";
    std::cout << "]" << std::endl;
}

// ���� ������ ����ϴ� ���ø� �Լ�
template <typename K, typename V>
void print_map(const std::map<K, V>& m) {
    // ���� ��� (Ű, ��) �ּ�ȸ�ϸ� ���
    for (const auto& kv : m)
        std::cout << kv.first << " : " << kv.second << " ";
    std::cout << std::endl;
}

int main() {
    // A ��ü a�� initializer_list�� �ʱ�ȭ
    // �̶� A�� initializer_list �����ڰ� ȣ��Ǿ� ����Ʈ�� ������ ���
    A a = { 1, 2, 3, 5, 6 };

    // ������ ���� v�� �߰�ȣ �ʱ�ȭ�� ���� �� �ʱ�ȭ
    std::vector<int> v = { 1, 2, 3, 5, 7 };
    // ���� v�� ������ ���
    print_vector(v);

    std::cout << "----------------" << std::endl;

    // ���ڿ� Ű, int �� ������ �� m�� �߰�ȣ�� �ʱ�ȭ
    std::map<std::string, int> m = { {"abc", 3}, {"hi", 2}, {"hello", 5} };
    // �� m�� ��� (Ű, ��) �� ���
    print_map(m);
}
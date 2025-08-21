#include <iostream>
#include <memory>
#include <variant>

// ����ü A ����: a() �Լ��� "A" ���
struct A {
    void a() { std::cout << "A" << std::endl; }
};

// ����ü B ����: b() �Լ��� "B" ���
struct B {
    void b() { std::cout << "B" << std::endl; }
};

// is_a�� true�� A ��ü, �ƴϸ� B ��ü�� �����ϴ� variant ��ȯ
// monostate�� variant�� ���� ���� ������ ��Ÿ�� �� �ִ� �� ����
std::variant<std::monostate, A, B> GetDataFromDB(bool is_a) {
    if (is_a)
        return A();  // A ��ü ��ȯ
    return B();      // B ��ü ��ȯ
}

int main() {
    // true�� ȣ���Ͽ� variant�� A ��ü ����
    auto v = GetDataFromDB(true);

    // variant ���ο� ����� Ÿ���� �ε��� ��� (0: monostate, 1: A, 2: B)
    std::cout << v.index() << std::endl;

    // variant���� A Ÿ������ get �Ͽ� a() ��� �Լ� ȣ��
    std::get<A>(v).a();
}
#include <iostream>
#include <string>
#include <tuple>
#include <map>

// �л� ������ ��ȯ�ϴ� �Լ�, id�� ���� ����, �̸�, ����(bool)�� Ʃ�÷� ��ȯ
std::tuple<int, std::string, bool> GetStudent(int id) {
    if (id == 0)
        return std::make_tuple(25, "ö��", true);   // id�� 0�̸� ���� 25, �̸� "ö��", ����(true)
    else
        return std::make_tuple(26, "����", false);  // �� �� id�� ���� 26, �̸� "����", ����(false)
}

int main() {
    auto student = GetStudent(0);  // �л� ���� �޾ƿ���

    // ������ ���ε��� ���� Ʃ�� ������ ������ ����
    auto [age, name, is_male] = student;

    // ������ �������� ���
    std::cout << "���� :" << age << std::endl;
    std::cout << "�̸� :" << name << std::endl;
    std::cout << "����? :" << std::boolalpha << is_male << std::endl; // boolalpha�� true/false ���

    std::cout << "--------------------------\n";

    // std::map �ʱ�ȭ �� ���� (Ű: int, ��: string)
    std::map<int, std::string> m = { {3, "hi"}, {5, "hello"} };

    // map�� �� ���(key, value)�� ������ ���ε����� �����ؼ� ���
    for (auto& [key, val] : m)
        std::cout << "key : " << key << " value : " << val << std::endl;
}
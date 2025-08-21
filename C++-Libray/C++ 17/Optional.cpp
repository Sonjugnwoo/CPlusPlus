#include <iostream>
#include <map>
#include <string>
#include <optional>  // std::optional ����� ���� ��� ����

// �־��� map���� key�� �ش��ϴ� ���� ã�Ƽ� ��ȯ�ϴ� �Լ�
// ���� ������ std::optional�� ��Ƽ� ��ȯ, ������ std::nullopt ��ȯ
std::optional<std::string> GetValueFromMap(const std::map<int, std::string>& m, int key) {
    // key�� �̿��� map���� �׸� Ž��
    auto itr = m.find(key);

    // key�� �����ϸ� �ش� �� ��ȯ
    if (itr != m.end()) {
        return itr->second;
    }

    // key�� ������ ���� ���� ���� optional ��ȯ
    return std::nullopt;
}

int main() {
    // �׽�Ʈ�� map �ʱ�ȭ
    std::map<int, std::string> data = { {1,"hi"}, {2,"hello"}, {3,"hiroo"} };

    // key=2�� �ش��ϴ� ���� ã��
    auto v = GetValueFromMap(data, 2);
    if (v) {
        // ���� �����ϸ� *v�� ���� ���� ���
        std::cout << "map 2 -> " << *v << std::endl;
    }
    else {
        // ���� ������ "�� ����" �޽��� ���
        std::cout << "map 2 -> �� ����" << std::endl;
    }

    // key=4�� �ش��ϴ� ���� ã�� (����)
    v = GetValueFromMap(data, 4);
    if (v) {
        std::cout << "map 4 -> " << *v << std::endl;
    }
    else {
        std::cout << "map 4 -> �� ����" << std::endl;
    }

}
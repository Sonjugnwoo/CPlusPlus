#include <iostream>
#include <list>

/*
���� ���� ���� (�ε���) : O(n) (���� Ž�� �ʿ�)

��/�� ���� �߰� (push_front, push_back) : O(1)

�߰� ����/���� (�ݺ��� ��ġ �˰� ���� ��) : O(1)

�߰� Ž�� : O(n)
*/

// ����Ʈ�� ��� ��Ҹ� ����ϴ� �Լ�
template <typename T>
void print_list(const std::list<T>& lst) {
    // ���� ��� for������ ����Ʈ ��Ҹ� �ϳ��� ���
    for (const auto& elem : lst)
        std::cout << elem << " ";
}

// ����Ʈ�� �� num�� �����ϴ� �Լ�
template <typename T>
void insert_list(std::list<T>& lst, const T& num) {
    // ����Ʈ ��ȸ �ݺ���
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (*it == num) {           // ���� ���Ұ� num�� ������
            lst.insert(it, num);    // ���� ��ġ �տ� num ����
            return;                 // ���� �Ϸ� �� �Լ� ����
        }
    }
    lst.push_back(num);             // ����Ʈ�� num�� ������ �� �ڿ� �߰�
}

// ����Ʈ���� �� num�� ã�Ƽ� �����ϴ� �Լ�
template<typename T>
void erase_list(std::list<T>& lst, const T& num) {
    // ����Ʈ�� ó������ ������ ��ȸ
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (*it == num) {           // ���� ���Ұ� num�� ������
            lst.erase(it);          // �ش� ��ġ ���� ����
            return;                 // ���� �� �Լ� ����
        }
    }
}

int main() {
    std::list<int> lst;

    lst.push_back(1);
    lst.push_back(4);
    lst.push_back(2);
    lst.push_back(7);
    lst.push_back(4);

    std::cout << "�ʱ� ����Ʈ: [ ";
    print_list(lst);
    std::cout << "]" << std::endl;

    // insert_list �׽�Ʈ
    std::cout << "insert_list(lst, 4) ȣ�� => 4 �տ� 4 ����" << std::endl;
    insert_list(lst, 4);
    std::cout << "[ ";
    print_list(lst);
    std::cout << "]" << std::endl;

    std::cout << "insert_list(lst, 10) ȣ�� => ����Ʈ ���� 10 �߰�" << std::endl;
    insert_list(lst, 10);
    std::cout << "[ ";
    print_list(lst);
    std::cout << "]" << std::endl;

    // erase_list �׽�Ʈ
    std::cout << "erase_list(lst, 4) ȣ�� => ù 4 ����" << std::endl;
    erase_list(lst, 4);
    std::cout << "[ ";
    print_list(lst);
    std::cout << "]" << std::endl;

    std::cout << "erase_list(lst, 100) ȣ�� => ���� ��, ��ȭ ����" << std::endl;
    erase_list(lst, 100);
    std::cout << "[ ";
    print_list(lst);
    std::cout << "]" << std::endl;

    return 0;
}
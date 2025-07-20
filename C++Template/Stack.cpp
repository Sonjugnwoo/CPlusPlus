#include "stack.h"

namespace Excel {
    // ������: ���� ���(start)�� �� ������ �����, current�� start�� �ʱ�ȭ
    Stack::Stack() : start(NULL, "") {
        current = &start;
    }

    // push: ���ο� ��带 ����� current ���� ����
    void Stack::push(std::string str) {
        Node* node = new Node(current, str); // �� ����� prev�� ���� current
        current = node;                      // current�� �� ���� �̵�
    }

    // pop: ������ top ���� ��ȯ�ϰ�, top ��带 ����
    std::string Stack::pop() {
        if (current == &start) return "";    // ������ ������� �� ���ڿ� ��ȯ
        std::string str = current->str;      // top �� ����
        Node* prev = current;                // ���� ��� ������ �ӽ� ����
        current = current->prev;             // current�� �Ʒ� ���� �̵�
        delete prev;                         // top ��� ����
        return str;                          // top �� ��ȯ
    }

    // peek: ������ top ���� �������� �ʰ� ��ȯ
    std::string Stack::peek() {
        if (current == &start) return "";    // ������ ������� �� ���ڿ� ��ȯ
        return current->str;                 // top �� ��ȯ
    }

    // is_empty: ������ ������� Ȯ��
    bool Stack::is_empty() {
        return current == &start;
    }

    // �Ҹ���: ���ÿ� �����ִ� ��� ��� ����
    Stack::~Stack() {
        while (current != &start) {
            Node* prev = current;
            current = current->prev;
            delete prev;
        }
    }
    /*----------NumStack----------*/
    NumStack::NumStack() : start(NULL, 0) {
        current = &start;
    }
    void NumStack::push(double data) {
        Node* node = new Node(current, data);
        current = node;
    }
    double NumStack::pop() {
        if (current == &start) return 0;
        double temp = current->data;
        Node* prev = current;
        current = current->prev;
        delete prev;
        return temp;
    }
    double NumStack::peek() {
        if (current == &start) return 0;
        return current->data;
    }
    bool NumStack::is_empty() {
        return current == &start;
    }
    NumStack::~NumStack() {
        while (current != &start) {
            Node* prev = current;
            current = current->prev;
            delete prev;
        }
    }
}
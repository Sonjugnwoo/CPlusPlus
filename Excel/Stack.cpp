#include "stack.h"

namespace Excel {
    // 생성자: 시작 노드(start)를 빈 값으로 만들고, current를 start로 초기화
    Stack::Stack() : start(NULL, "") {
        current = &start;
    }

    // push: 새로운 노드를 만들어 current 위에 쌓음
    void Stack::push(std::string str) {
        Node* node = new Node(current, str); // 새 노드의 prev는 현재 current
        current = node;                      // current를 새 노드로 이동
    }

    // pop: 스택의 top 값을 반환하고, top 노드를 삭제
    std::string Stack::pop() {
        if (current == &start) return "";    // 스택이 비었으면 빈 문자열 반환
        std::string str = current->str;      // top 값 저장
        Node* prev = current;                // 현재 노드 포인터 임시 저장
        current = current->prev;             // current를 아래 노드로 이동
        delete prev;                         // top 노드 삭제
        return str;                          // top 값 반환
    }

    // peek: 스택의 top 값을 삭제하지 않고 반환
    std::string Stack::peek() {
        if (current == &start) return "";    // 스택이 비었으면 빈 문자열 반환
        return current->str;                 // top 값 반환
    }

    // is_empty: 스택이 비었는지 확인
    bool Stack::is_empty() {
        return current == &start;
    }

    // 소멸자: 스택에 남아있는 노드 모두 삭제
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
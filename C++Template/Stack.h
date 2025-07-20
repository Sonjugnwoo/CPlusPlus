#ifndef EXCEL_STACK_H
#define EXCEL_STACK_H

#include <string>

namespace Excel {
	class Stack {

		// 내부 Node 구조체: 스택의 각 원소를 연결 리스트로 표현 (문자열)
		struct Node {
			Node* prev;           // 이전 노드를 가리키는 포인터 (스택 아래쪽)
			std::string str;      // 저장할 데이터(문자열)
			Node(Node* prev, std::string str) : prev(prev), str(str) {}
		};

		Node* current;            // 현재 스택의 top(맨 위) 노드를 가리키는 포인터
		Node start;               // 스택의 바닥(더미 노드), 항상 존재

	public:
		Stack();						 // 생성자
		void push(std::string str);      // push: 데이터 추가
		std::string pop();               // pop: top 데이터 반환 및 삭제
		std::string peek();              // peek: top 데이터 반환(삭제 X)
		bool is_empty();                 // 스택이 비었는지 확인
		~Stack();                        // 소멸자: 메모리 해제
	};
	class NumStack {

		// 내부 Node 구조체: 스택의 각 원소를 연결 리스트로 표현 (더블형)
		struct Node
		{
			Node* prev;				// 이전 노드 가르키는 포인터
			double data;			// 저장할 데이터
			Node(Node* prev, double data) : prev(prev), data(data) {}
		};
		Node* current;
		Node start;

	public:
		NumStack();					// 생성자
		void push(double data);		// 데이터 추가
		double pop();				// top 데이터 반환 및 삭제
		double peek();				// top 데이터 반환 (삭제 x)
		bool is_empty();			// 스택이 비었는지 확인
		~NumStack();				// 소멸자
	};
}
#endif
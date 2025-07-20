#ifndef EXCEL_STACK_H
#define EXCEL_STACK_H

#include <string>

namespace Excel {
	class Stack {

		// ���� Node ����ü: ������ �� ���Ҹ� ���� ����Ʈ�� ǥ�� (���ڿ�)
		struct Node {
			Node* prev;           // ���� ��带 ����Ű�� ������ (���� �Ʒ���)
			std::string str;      // ������ ������(���ڿ�)
			Node(Node* prev, std::string str) : prev(prev), str(str) {}
		};

		Node* current;            // ���� ������ top(�� ��) ��带 ����Ű�� ������
		Node start;               // ������ �ٴ�(���� ���), �׻� ����

	public:
		Stack();						 // ������
		void push(std::string str);      // push: ������ �߰�
		std::string pop();               // pop: top ������ ��ȯ �� ����
		std::string peek();              // peek: top ������ ��ȯ(���� X)
		bool is_empty();                 // ������ ������� Ȯ��
		~Stack();                        // �Ҹ���: �޸� ����
	};
	class NumStack {

		// ���� Node ����ü: ������ �� ���Ҹ� ���� ����Ʈ�� ǥ�� (������)
		struct Node
		{
			Node* prev;				// ���� ��� ����Ű�� ������
			double data;			// ������ ������
			Node(Node* prev, double data) : prev(prev), data(data) {}
		};
		Node* current;
		Node start;

	public:
		NumStack();					// ������
		void push(double data);		// ������ �߰�
		double pop();				// top ������ ��ȯ �� ����
		double peek();				// top ������ ��ȯ (���� x)
		bool is_empty();			// ������ ������� Ȯ��
		~NumStack();				// �Ҹ���
	};
}
#endif
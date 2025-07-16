#ifndef EXCEL_VECTOR_H
#define EXCEL_VECTOR_H

#include <string>

namespace Excel {

    class Vector {
        std::string* data;   // ���� ���ڿ� �迭�� ���� �ּ�
        int capacity;        // ���� �Ҵ�� �迭�� ũ��(�ִ� ���� ���� ����)
        int length;          // ���� ����� ���� ����
     
    public:
        // ������: n���� ������ ���� ���� �迭 ���� (�⺻�� 1)
        Vector(int n = 1);

        // �� �ڿ� ���ο� ���� �߰� (�ʿ�� �迭 ũ�� 2��� Ȯ��)
        void push_back(std::string str);

        // ������ ��ġ�� ���� ���� (�б�/���� ����)
        std::string operator[](int i);

        // x��° ��ġ�� ���� ���� (���� ���ҵ��� �� ĭ�� ������ �̵�)
        void remove(int x);

        // ���� ���Ϳ� ����� ���� ���� ��ȯ
        int size();

        // �Ҹ���: ���� �迭 �޸� ����
        ~Vector();
    };
}

#endif
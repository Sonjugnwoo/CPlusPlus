#include "vector.h"

namespace Excel {
    // ������: capacity ũ���� ���ڿ� �迭�� ���� �Ҵ�, �ʱ� ���̴� 0
    Vector::Vector(int n) : data(new std::string[n]), capacity(n), length(0) {}

    // push_back: �迭 ���� ���ڿ� �߰�, ���� ���� �� 2��� Ȯ��
    void Vector::push_back(std::string str) {
        if (capacity <= length) {
            // �� �迭 �Ҵ� (�뷮 2��)
            std::string* temp = new std::string[capacity * 2];
            // ���� ������ ����
            for (int i = 0; i < length; i++)
                temp[i] = data[i];
            // ���� �迭 ����
            delete[] data;
            // �� �迭�� ��ü
            data = temp;
            capacity *= 2;
        }
        // �� ������ �߰�
        data[length] = str;
        length++;
    }

    // operator[]: i��° ���� ��ȯ (�б�/���� ����)
    std::string Vector::operator[](int i) {
        return data[i];
    }

    // remove: x��° ���� ����, ���� ������ �� ĭ�� ������ ���
    void Vector::remove(int x) {
        for (int i = x + 1; i < length; i++)
            data[i - 1] = data[i];
        length--;
    }

    // size: ���� ����� ���� ���� ��ȯ
    int Vector::size() {
        return length;
    }

    // �Ҹ���: ���� �Ҵ�� �迭 ����
    Vector::~Vector() {
        if (data)
            delete[] data;
    }
}
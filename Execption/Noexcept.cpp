#include <iostream>

// foo �Լ��� noexcept�� ����Ǿ� ���ܸ� ������ �ʴ´ٰ� �����Ϸ��� ������
int foo() noexcept {
    return 0;  // ��ȯ Ÿ�� int�� �°� 0�� ��ȯ��
}

// bar �Լ��� noexcept�� �����Ƿ� ���ܸ� �����Ӱ� ���� �� ����
int bar() {
    throw 1;  // ������ ����(1)�� ����
    return 0; // �������� �ʴ� �ڵ�
}

int main() {
    foo();  // noexcept �Լ� ȣ��, ���� �߻� ����

    try {
        bar();  // bar �Լ� ȣ��, ���� �߻�
    }
    catch (int x) {
        // bar �Լ����� ���� int ���ܸ� ��Ƽ� ���
        std::cout << "Error :" << x << std::endl;
    }
}
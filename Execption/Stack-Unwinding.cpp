#include <iostream>
#include <stdexcept>

// ���ҽ� ������ ����ϴ� Ŭ����
// �����ڿ��� ���ܰ� �߻� �ÿ� �Ҹ��ڰ� ȣ�� ���� �ʴ´� 
class Resource {
	int id_;

public:
	Resource(int id) : id_(id) {}

	~Resource() {
		std::cout << "���ҽ� ����" << id_ << std::endl;
	}

};

int func3() {
    Resource r(3);                          // id 3�� Resource ��ü ����
    throw std::runtime_error("Exception from 3!\n");  // ���� �߻�

    // �� ���� �߻����� ���� �� �Լ� ����ǰ� ������ unwind ��
    // ȣ�� ������ Ǯ���鼭 func3() �� ���� ���� r(3)�� �Ҹ��� ȣ���
    return 0;                              // �������� ����
}

int func2() {
    Resource r(2);      // id 2�� Resource ��ü ����
    func3();            // func3 ȣ��

    // func3()���� ���ܰ� �߻��� �� ���α����� �������� ����
    // ȣ�� ������ unwind �Ǹ鼭 func2() �� ���� ��ü r(2)�� �Ҹ��� ȣ���

    std::cout << "���� �ȵ� " << std::endl;  // ���� �߻� �� ���� �� ��
    return 0;
}

int func() {
    Resource r(1);      // id 1�� Resource ��ü ����
    func2();            // func2 ȣ��

    // func2()���� ���ܰ� ���ĵǾ� �� ���ε� ������� ����
    // ȣ�� ���� unwind �� func() ���� r(1) �Ҹ��� ȣ���

    std::cout << "���� �ȵ� " << std::endl;  // ���� �߻� �� ���� �� ��
    return 0;
}

int main() {
	try {
		func();
	}
	catch (std::exception& e) {	
		std::cout << "Exception : " << e.what();
	}
}
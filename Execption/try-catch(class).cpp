#include <exception>
#include <iostream>

// ������ �⺻ Ŭ���� ������ �ϴ� Parent
class Parent : public std::exception {
public:
	// ���� �޽��� ��ȯ, noexcept ����Ͽ� ���� �� ������ ����
	virtual const char* what() const noexcept override {
		return "Parent!\n";
	}
};

// Parent�� ����� Child Ŭ���� (�� ��ü���� ����)
class Child : public Parent {
public:
	// Parent�� what() �Լ� �������̵�
	const char* what() const noexcept override {
		return "Child!\n";
	}
};

int func(int c) {
	if (c == 1)throw Parent();
	else if (c == 2) throw Child();

	return 0;
}

int main() {
	int c;
	std::cin >> c;

	try {
		func(c);
	}
	// Child Ÿ�� ���ܸ� ���� ĳġ�ؾ� �� (�� ��ü���� Ÿ��)
	catch (Child& c) {
		std::cout << "Child Catch!" << std::endl;
		std::cout << c.what();  // "Child!\n" ���
	}
	// �� �������� Parent Ÿ�� ���� ĳġ
	catch (Parent& p) {
		std::cout << "Parent Catch!" << std::endl;
		std::cout << p.what();  // "Parent!\n" ���
	}
}
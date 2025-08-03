#include <functional>
#include <iostream>

//Ref -> ���� ��ü�� ������ ���δ� ���� bind���� �Լ� ��ü�� ���鶧 �⺻������ ���ڰ� ���� �����ε�  ������ ���� �ǵ��� �� 

struct S {
	int data;
	S(int data) : data(data) { std::cout << "�Ϲ� ������ " << std::endl; }
	S(const S& s) {
		std::cout << "���� ������ " << std::endl;
		data = s.data;
	}

	S(S&& s) { 
		std::cout << "�̵� ������" << std::endl;
		data = s.data;
	}
};

void something(S& s1, const S& s2) { s1.data = s2.data + 3; }

int main() {
	S s1(1), s2(2);		 // s1.data=1, s2.data=2

	std::cout << "before : " << s1.data << std::endl;

	// std::bind�� ����� �Լ� something �� ù��° ���ڸ� ������ �����ϰ�,
	// �ι�° ���ڴ� ���߿� ȣ�� �� �޾Ƶ��̴� �Լ� ��ü temp ����
	auto temp = std::bind(something, std::ref(s1), std::placeholders::_1);

	temp(s2);	//temp(s2) ȣ���ϸ� something(s1, s2) ȣ���.

	std::cout << "after : " << s1.data << std::endl;
}
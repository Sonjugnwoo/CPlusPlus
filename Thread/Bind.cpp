#include <functional>
#include <iostream>

//Bind -> ���� �Լ��� Ư�� ���ڸ� �ٿ��� 
//Placeholders -> Bind ���� ���߿� ���޵� ������ ��ġ�� ǥ���ϴ� �ڸ� ǥ��

void add(int x, int y) {
	std::cout << x << "+" << y << "=" << x + y << std::endl;
}


void subtract(int x, int y) {
	std::cout << x << "-" << y << "=" << x - y << std::endl;
}

int main() {
	// add �Լ����� ù��° ���ڸ� 2�� �����ϰ�, �ι�° ���ڴ� ȣ�� �� �޴� ���·� ���ο� �Լ� ��ü ����
	auto add_with_2 = std::bind(add, 2, std::placeholders::_1);		 // x=2 ����, y = ù ��° ����
	add_with_2(3);   // y = 3 ���� �� 

	add_with_2(3, 4); // ȣ�� �� �� �� ���ڸ� ������, bind�� ����ϴ� ù ��° ���ڸ� ���

	//subtract �Լ����� �ι�° ���ڸ� 2�� �����ϰ�, ù��° ���ڴ� ȣ�� �� �޴� ���� ���� 
	auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);		 // y=2 ����
	auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);	 // subtract �Լ��� ���� ��ġ�� �ٲپ� ȣ���� �� �ִ� �Լ� ��ü ����

	subtract_from_2(3); // x = 3 ���� �� 
	negate(4, 2);	 // negate(4,2) ȣ�� �� subtract(2,4) ȣ��
}
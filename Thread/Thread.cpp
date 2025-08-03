//���μ��� -> �ü������ ����Ǵ� ���α׷��� �ּ� ���� 
//������ -> CPU�ھ�� ���ư��� ���α׷� ���� 

/*
					join()						detach()
����	������ ���Ḧ ��ٸ�			�����带 ���� ������� �и��Ͽ� ���� ����
����	�����ϰ� ������ ���� ����		���� ������ ���ŷ ���� ��� ����
����	���� �����尡 ����ؾ� ��		�����尡 �۾� �� ����� �� ����
����	�ݵ�� ȣ���ؼ� ������ ����		ȣ�� �� ������ ������ ��ȯ
*/

#include <iostream>
#include <thread>

void func1() {
	for (int i = 0; i < 10; i++)
		std::cout << "������ 1 �۵� �� \n";
}
void func2() {
	for (int i = 0; i < 10; i++)
		std::cout << "������ 2 �۵� �� \n";
}
void func3() {
	for (int i = 0; i < 10; i++)
		std::cout << "������ 3 �۵� �� \n";
}

int main() {
	// t1, t2, t3 ������ ���� �� join()
	std::thread t1(func1);
	std::thread t2(func2);
	std::thread t3(func3);

	//join  ->  ���� �����尡 �ش� �����尡 ������ ������ ��ٸ�
	t1.join();
	t2.join();
	t3.join();

	std::cout << "-----------------\n";
	//d1, d2, d3 ������ ���� �� detach()
	std::thread d1(func1);
	std::thread d2(func2);
	std::thread d3(func3);

	//detach  -> �ش� �����带 ���� ������� �и����� ���������� ����
	d1.detach();
	d2.detach();
	d3.detach();

	std::cout << "�����Լ� ���� \n";
}

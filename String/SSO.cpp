#include <iostream>
#include <string>

void* operator new(std::size_t count) {
	std::cout << count << "bytes �Ҵ� " << std::endl;
	return malloc(count);
}

int main() {

	// s1�� �� ���ڿ� �Ҵ� �� ���� ���� ũ�� �ʰ��� �� �޸� ���� �Ҵ� �߻�
	// operator new ȣ��Ǿ� �Ҵ� ����Ʈ �� ��µ�
	std::cout << "s1 ����" << std::endl;
	std::string s1 = "this is a pretty long sentence!!";
	std::cout << "s1 ũ�� :" << sizeof(s1) << std::endl;

	// s2�� ª�� ���ڿ� �Ҵ� �� ��κ��� �������� SSO �������� ���� ���ۿ� ����
	// ���� �Ҵ� ���� ����Ǿ� operator new ȣ���� �� ���� �� ����
	std::cout << "s2 ����" << std::endl;
	std::string s2 = "short setence";
	std::cout << "s1 ũ�� : " << sizeof(s2) << std::endl;


}
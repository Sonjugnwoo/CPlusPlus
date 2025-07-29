#include <iostream>
#include <string>


void* operator new(std::size_t count) {
	std::cout << count << "bytes �Ҵ� " << std::endl;
	return malloc(count);
}

//���ڿ��� very  ������ true ��ȯ 
bool contains_very(const std::string& str) {	 //�б⸸ �ϱ� ������ const 
	return str.find("very") != std::string::npos;
}

//C++ 17 �̻�  std::string_view �� �߰� �� 
// string_view ������ �޸� �Ҵ� �ʿ� ���� 
/*
bool contains_very(const std::string_view str) {	 //�б⸸ �ϱ� ������ const 
	return str.find("very") != std::string_view::npos;
}*/
int main() {

	//�Ϲ������� std::string ��ü ���ʿ��ϰ� ���� 
	std::cout << std::boolalpha << contains_very("C++ string is very hard to ues") << std::endl;

	std::cout << contains_very("C++ string is not easy to ues") << std::endl;
}
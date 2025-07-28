#include <iostream>
#include <string>

int main() {

	//							1234567890 123 4 567 
	// UTF-32 ���ڿ� ����
	// std::u32string�� UTF-32 ���ڵ� �������,
	// �� ���ڰ� 4����Ʈ(32��Ʈ)�� �����Ǿ� �����.
	// ���ڿ��� ���� '����' ����(�ڵ�����Ʈ ����)�� size()�� ��ȯ��.
	std::u32string u32_str = U"�̰� UTF-32 ���ڿ� �Դϴ�.";
	std::cout <<"UTF-32 ���ڿ� ũ�� : " << u32_str.size() << std::endl;

	//							12 345678901 2 3456
	// UTF-8 ���ڿ� ���� (���� ���� ��Ƽ����Ʈ ���ڵ�)
	// std::string�� UTF-8 ���ͷ�(u8"")�� ����
	std::string str = u8"�̰� UTF-8 ���ڿ� �Դϴ�.";
	std::cout <<"UTF-8 ���ڿ� ũ�� : " << u32_str.size() << std::endl;
	size_t i = 0; 
	size_t len = 0;

	while (i < str.size()) {
		int char_size = 0;
		// UTF-8 ���ڵ� ����:
	    // 1����Ʈ ����: 0xxxxxxx
	    // 2����Ʈ ����: 110xxxxx
	    // 3����Ʈ ����: 1110xxxx
	    // 4����Ʈ ����: 11110xxx

		if ((str[i] & 0b11111000) == 0b11110000)	char_size = 4;
		else if ((str[i] & 0b11110000) == 0b11100000) char_size = 3;
		else if ((str[i] & 0b11100000) == 0b11000000) char_size = 2;
		else if ((str[i] & 0b10000000) == 0b00000000) char_size = 1;
		else {
			std::cout << "�̻��� ���� �߰� " << std::endl;
			char_size = 1;
		}

		std::cout << str.substr(i, char_size) << std::endl;

		i += char_size;  // ���� ���� ���� ��ġ�� �̵�
		len++;          // ���� ���� ���� (���� ���� ī��Ʈ)

	}
	std::cout << "���ڿ��� ���� ���� " << len << std::endl;
	
	//							1234567890 123 4 567
	std::u16string u16_str = u"�̰� UTF-16 ���ڿ� �Դϴ�";

	std::u16string str_2 = u"�ȳ��ϼ��� �̰� �׽�Ʈ �� �ڵ� �Դϴ�";
	// �ѱ� �ʼ� ���� �迭 (19��)
	std::string jaum[] = { "��","��","��","��","��","��" ,"��" ,"��" ,"��" ,
	  "��" ,"��" ,"��" ,"��" ,"��" ,"��" ,"��" ,"��" , "��", "��" };
	for (char16_t c : str_2) {
		// �ѱ� �ϼ��� ���� ���� Ȯ�� (�� ~ �R)
		if (!(0xAC00 <= c && c <= 0xD7A3)) continue;

		// �ѱ� ���� ���� ��ȣ(offset) ���
		int offset = c - 0xAC00;

		// �ʼ� �ε��� ��� (offset / 588, 588=21*28)
		int jaum_offset = offset / 0x24C;  // 0x24C = 588 decimal

		std::cout << jaum[jaum_offset];
	}
}
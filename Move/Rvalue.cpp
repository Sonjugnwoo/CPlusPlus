#include <iostream>
#include <cstring>

class MyString {
	char* string_content;
	int string_length;

	int memory_capacity;

public:
	MyString() : string_length(0), memory_capacity(0), string_content(nullptr) {
		std::cout << " ������ ȣ�� " << std::endl;
	}

	MyString(const char* str) {
		std::cout << " ������ ȣ�� " << std::endl;
		string_length = strlen(str);
		memory_capacity = string_length;
		string_content = new char[string_length + 1];

		for (int i = 0; i < string_length; i++)
			string_content[i] = str[i];

		string_content[string_length] = '\0';
	}

	MyString(const MyString& str) {
		std::cout << " ���� ������ ȣ�� " << std::endl;
		string_length = str.string_length;
		memory_capacity = str.memory_capacity;
		string_content = new char[string_length + 1];

		for (int i = 0; i < string_length; i++)
			string_content[i] = str.string_content[i];

		string_content[string_length] = '\0';
	}

	MyString(MyString&& other) {// �̵� ������: ������ ����(&&)�� MyString �ӽ� ��ü�� ����

    // �̵� �����ڴ� ��ü�� ���ҽ�(�޸� ��)�� '������ ����' �ϹǷ�, 
    // ���� ��ü�� �޸𸮸� �����ϴ� ��� ������(�ּҰ�)�� �Ű��� (���� ��� ����)
		std::cout << "�̵� ������ ȣ�� " << std::endl;

		string_length = other.string_length;        // ���ڿ� ���� �̵�
		memory_capacity = other.memory_capacity;    // �޸� �뷮 �̵�
		string_content = other.string_content;      // ���ڿ� ������ �̵� (�ּҰ� ����)

		other.string_content = nullptr;  // ���� ��ü�� �������� �Ҿ��ٴ� ǥ��
									   // �̷� ���� ���� ��ü �Ҹ� �� �޸� ���� �� �� (���� ���� ����)
	}

	~MyString() {
		if(string_content)
		delete[] string_content;
	}

	void reserve(int size) {
		if (size > memory_capacity) {
			char* prev_string_content = string_content;

			string_content = new char[size + 1];
			memory_capacity = size;

			for (int i = 0; i != string_length; i++)
				string_content[i] = prev_string_content[i];

			string_content[string_length] = '\0';

			if (prev_string_content != nullptr)
				delete[] prev_string_content;
		}
	}

	MyString operator +(const MyString& s) {

		MyString str;
		str.reserve(string_length + s.string_length);

		// ���ڿ� ������ ����
		for (int i = 0; i < string_length; i++)
			str.string_content[i] = string_content[i];
		for (int i = 0; i < s.string_length; i++)
			str.string_content[string_length + i] = s.string_content[i];

		str.string_length = string_length + s.string_length;
		str.string_content[str.string_length] = '\0';

		return str;	//���� ���� �߻� 
	}


	int length() const { return string_length; }

	void print() const {
		for (int i = 0; i < string_length; i++)
			std::cout << string_content[i];

		std::cout << std::endl;
	}

};

int main() {
	MyString str1("abc");
	MyString str2("bbc");

	std::cout << "-------------" << std::endl;

	MyString str3 = str1 + str2;
	str3.print();
}
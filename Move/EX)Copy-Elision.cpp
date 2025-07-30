#include <iostream>
#include <cstring>

class MyString {
	char* string_content;
	int string_length;

	int memory_capacity;

public:
	MyString() : string_length(0), memory_capacity(0), string_content(nullptr) {
		std::cout << " 생성자 호출 " << std::endl;
	}

	MyString(const char* str) {
		std::cout << " 생성자 호출 " << std::endl;
		string_length = strlen(str);
		memory_capacity = string_length;
		string_content = new char[string_length+1];

		for (int i = 0; i < string_length; i++)
			string_content[i] = str[i];

		string_content[string_length] = '\0';
	}

	MyString(const MyString& str) {
		std::cout << " 복사 생성자 호출 " << std::endl;
		string_length = str.string_length;
		memory_capacity = str.memory_capacity;
		string_content = new char[string_length+1];

		for (int i = 0; i < string_length; i++)
			string_content[i] = str.string_content[i];

		string_content[string_length] = '\0';
	}

	~MyString() {
		delete[] string_content;
	}

	void reserve(int size) {
		if (size > memory_capacity) {
			char* prev_string_content = string_content;

			string_content = new char[size+1];
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

		// 문자열 데이터 복사
		for (int i = 0; i < string_length; i++)
			str.string_content[i] = string_content[i];
		for (int i = 0; i < s.string_length; i++)
			str.string_content[string_length + i] = s.string_content[i];

		str.string_length = string_length + s.string_length;
		str.string_content[str.string_length] = '\0';
			
		return str;	//복사 생략 발생 
	}
	

	int length() const { return string_length; }

	void print() const {
		for (int i = 0; i < string_length; i++)
			std::cout << string_content[i];

		std::cout << std::endl;
	}

};

int main() {
	// 기본 생성자 테스트
	MyString s1;
	std::cout << "s1 length: " << s1.length() << std::endl;
	s1.print();

	// const char* 생성자 테스트
	MyString s2("Hello");
	std::cout << "s2 length: " << s2.length() << std::endl;
	s2.print();

	// 복사 생성자 테스트
	MyString s3(s2);
	std::cout << "s3 length (copy of s2): " << s3.length() << std::endl;
	s3.print();

	// operator+ 테스트
	MyString s4 = s2 + MyString(", World!");
	std::cout << "s4 length (s2 + , World!): " << s4.length() << std::endl;
	s4.print();

	return 0;
}
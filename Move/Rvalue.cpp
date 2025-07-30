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
		string_content = new char[string_length + 1];

		for (int i = 0; i < string_length; i++)
			string_content[i] = str[i];

		string_content[string_length] = '\0';
	}

	MyString(const MyString& str) {
		std::cout << " 복사 생성자 호출 " << std::endl;
		string_length = str.string_length;
		memory_capacity = str.memory_capacity;
		string_content = new char[string_length + 1];

		for (int i = 0; i < string_length; i++)
			string_content[i] = str.string_content[i];

		string_content[string_length] = '\0';
	}

	MyString(MyString&& other) {// 이동 생성자: 우측값 참조(&&)로 MyString 임시 객체를 받음

    // 이동 생성자는 객체의 리소스(메모리 등)를 '소유권 이전' 하므로, 
    // 기존 객체의 메모리를 복사하는 대신 포인터(주소값)만 옮겨줌 (복사 비용 절감)
		std::cout << "이동 생성자 호출 " << std::endl;

		string_length = other.string_length;        // 문자열 길이 이동
		memory_capacity = other.memory_capacity;    // 메모리 용량 이동
		string_content = other.string_content;      // 문자열 포인터 이동 (주소값 복사)

		other.string_content = nullptr;  // 원본 객체가 소유권을 잃었다는 표시
									   // 이로 인해 원본 객체 소멸 시 메모리 해제 안 함 (이중 해제 방지)
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
	MyString str1("abc");
	MyString str2("bbc");

	std::cout << "-------------" << std::endl;

	MyString str3 = str1 + str2;
	str3.print();
}
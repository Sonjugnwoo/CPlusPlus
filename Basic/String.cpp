#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class string {
	char* str;
	int len;

public:
	// 문자 c를 n번 반복한 문자열 생성자
	string(char c, int n)
	{
		len = n;
		str = new char[len + 1];
		for (int i = 0; i < n; i++)
			str[i] = c;
		str[len] = '\0';
	}

	// C 문자열로부터 생성자
	string(const char* s)
	{
		len = std::strlen(s);
		str = new char[len + 1];
		std::strcpy(str, s);
	}

	// 복사 생성자
	string(const string& s)
	{
		len = s.len;
		str = new char[len + 1];
		std::strcpy(str, s.str);
	}

	// 소멸자
	~string()
	{
		delete[] str;
	}

	// str 뒤에 s 를 붙인다.
	void AddString(const string& s)
	{
		int new_len = len + s.len;
		char* new_str = new char[new_len + 1];
		strcpy(new_str, str);
		strcat(new_str, s.str);
		delete[] str;
		str = new_str;
		len = new_len;
	}

	// str 에 s 를 복사한다.
	void CopyString(const string& s)  
	{
		if (len != s.len)
		{
			delete[] str;
			str = new char[s.len + 1];
		}
		len = s.len;
		strcpy(str, s.str);
	}

	// 문자열 길이 리턴
	int Strlen()                  
	{
		return len;
	}

	//출력 
	void Print() const
	{
		std::cout << str << std::endl;
	}
};

int main() {
	string s1('A', 5);      // "AAAAA"
	string s2("Hello!");    // "Hello!"
	string s3 = s2;         // 복사 생성자 사용

	s1.Print(); // AAAAA
	s2.Print(); // Hello!
	s3.Print(); // Hello!

	// 이어붙이기 테스트
	s1.AddString(s2);
	s1.Print(); // AAAAAHello!

	// 복사 테스트
	s1.CopyString(s3);
	s1.Print(); // Hello!

	std::cout << "s1 길이: " << s1.Strlen() << std::endl; // 6

	return 0;
}
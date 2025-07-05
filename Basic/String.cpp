#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class string {
	char* str;
	int len;

public:
	// ���� c�� n�� �ݺ��� ���ڿ� ������
	string(char c, int n)
	{
		len = n;
		str = new char[len + 1];
		for (int i = 0; i < n; i++)
			str[i] = c;
		str[len] = '\0';
	}

	// C ���ڿ��κ��� ������
	string(const char* s)
	{
		len = std::strlen(s);
		str = new char[len + 1];
		std::strcpy(str, s);
	}

	// ���� ������
	string(const string& s)
	{
		len = s.len;
		str = new char[len + 1];
		std::strcpy(str, s.str);
	}

	// �Ҹ���
	~string()
	{
		delete[] str;
	}

	// str �ڿ� s �� ���δ�.
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

	// str �� s �� �����Ѵ�.
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

	// ���ڿ� ���� ����
	int Strlen()                  
	{
		return len;
	}

	//��� 
	void Print() const
	{
		std::cout << str << std::endl;
	}
};

int main() {
	string s1('A', 5);      // "AAAAA"
	string s2("Hello!");    // "Hello!"
	string s3 = s2;         // ���� ������ ���

	s1.Print(); // AAAAA
	s2.Print(); // Hello!
	s3.Print(); // Hello!

	// �̾���̱� �׽�Ʈ
	s1.AddString(s2);
	s1.Print(); // AAAAAHello!

	// ���� �׽�Ʈ
	s1.CopyString(s3);
	s1.Print(); // Hello!

	std::cout << "s1 ����: " << s1.Strlen() << std::endl; // 6

	return 0;
}
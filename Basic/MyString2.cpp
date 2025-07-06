#include <iostream>

// MyString Ŭ���� ����
class MyString
{
	char* str;              // ���ڿ� ������(���� �Ҵ�)
	int len;                // ���ڿ� ����
	int memory_capacity;    // �Ҵ�� ���� ũ��(�뷮)
public:

	// ���� 1���� ����
	MyString(char c)
	{
		str = new char[2];
		str[0] = c;
		str[1] = '\0';
		memory_capacity = 1;
		len = 1;
	}
	// C ���ڿ��� ����
	MyString(const char* str_2)
	{
		len = strlen(str_2);
		str = new char[len + 1];

		for (int i = 0; i < len; i++)
			str[i] = str_2[i];

		str[len] = '\0';
		memory_capacity = len;
	}
	// ���� ������
	MyString(const MyString& str_2)
	{
		len = str_2.len;
		str = new char[len+1];
		for (int i = 0; i < len; i++)
			str[i] = str_2.str[i];

		str[len] = '\0';
		memory_capacity = len;
	}
	// �Ҹ���
	~MyString()
	{
		delete[] str;
	}

	// ��� �Լ� ����
	void Print() const;                                 // ���ڿ� ���
	int MemoryCapacity() const;                         // capacity ��ȯ
	void Reserve(int size);                             // capacity ����
	char at(int i) const;                               // i��° ���� ��ȯ
	int Find(int find_from, const MyString& str_2) const; // �κ� ���ڿ� ã��
	int Find(int find_from, const char* str_2) const;
	int Find(int find_from, const char c) const;
	int BoyerMooreFind(int find_from, const MyString& str_2) const;
	int BoyerMooreFind(int find_from, const char* str_2) const;
	int BoyerMooreFind(int find_from, const char c) const;
	int Compare(const MyString& str_2) const;           // ���ڿ� ��

	MyString& Assign(const MyString& str_2);            // ����
	MyString& Assign(const char* str_2);
	MyString& Insert(int loc, const MyString& str_2);   // ����
	MyString& Insert(int loc, const char* str_2);
	MyString& Insert(int loc, char c);
	MyString& Erase(int loc, int num);                  // ����
};

// ���ڿ� ���
void MyString::Print() const
{
	std::cout << str << std::endl;
}

// ���� capacity ��ȯ
int MyString::MemoryCapacity() const
{
	return memory_capacity;
}

// capacity ����(���Ҵ�)
void MyString::Reserve(int size)
{
	if (size > memory_capacity)
	{
		char* buffer = str;

		str = new char[size+1];
		memory_capacity = size;

		// ���� �����͸� ����
		for (int i = 0; i < size; i++)
			str[i] = buffer[i];

		str[len] = '\0';
		delete[] buffer;
	}
	// size <= memory_capacity�� �ƹ� �͵� �� ��
}

// i��° ���� ��ȯ (���� ���̸� '\0' ��ȯ)
char MyString::at(int i) const
{
	if (i >= len || i < 0)
		return '\0';
	else
		return str[i];
}

// �κ� ���ڿ� ã�� (MyString ����)
int MyString::Find(int find_from, const MyString& str_2) const
{
	int i, j;
	if (str_2.len == 0) return -1;
	for ( i = find_from; i <= len-str_2.len; i++)
	{
		for (j = 0; j < str_2.len; j++)
		{
			if (str[i + j] != str_2.str[j])
				break;
		}
		if (j == str_2.len)
			return i;
	}
	return -1;
}

// �κ� ���ڿ� ã�� (C ���ڿ�)
int MyString::Find(int find_from, const char* str_2) const
{
	MyString temp(str_2);
	return Find(find_from, temp);
}

// ���� 1�� ã��
int MyString::Find(int find_from, const char c) const
{
	MyString temp(c);
	return Find(find_from, temp);
}

// Boyer-Moore-Horspool �˰����� �̿��� �κ� ���ڿ� �˻�
int MyString::BoyerMooreFind(int find_from, const MyString& str_2) const
{
	int str_p = 0;      // ���� �˻� ��ġ(���� ���ڿ�����)
	int str_2p = 0;     // ���� ���ڿ������� �ε���
	int len_2 = str_2.len; // ����(ã�� ���ڿ�)�� ����
	int skip[UCHAR_MAX + 1]; // skip ���̺� (���� �� ���ں� �̵� �Ÿ�)

	// ���� ó��: ã�� ������ ����ų�, �˻� ���� ��ġ�� ������ ���
	if (len_2 == 0 || find_from < 0 || find_from > len - len_2)
		return -1;

	//skip ���̺� �ʱ�ȭ: ��� ���ڿ� ���� �⺻ �̵� �Ÿ��� ���� ����
	for (int i = 0; i < UCHAR_MAX + 1; i++)
		skip[i] = len_2;

	//skip ���̺� ����: ���� �� �� ���ڿ� ���� �̵� �Ÿ� ���
	for (int i = 0; i < len_2 - 1; i++)
		skip[str_2.str[i]] = len_2 - i - 1;

	//�˻� ���� ��ġ ���� (find_from���� ���� ���̸�ŭ �ڿ��� ����)
	str_p = find_from + len_2 - 1;

	//���� ���ڿ����� ������ ã�� ������ �ݺ�
	while (str_p < len)
	{
		str_2p = len_2 - 1;     // ������ ������ ���ں��� ��
		int temp_p = str_p;     // ���� ���ڿ����� �� ���� ��ġ

		//�ڿ������� �� ���ھ� ��
		while (str[temp_p] == str_2.str[str_2p])
		{
			if (str_2p == 0)
				return temp_p;	// ���� ��ü�� ��ġ�ϸ� ���� ��ġ ��ȯ

			temp_p--;
			str_2p--;
		}

		//����ġ �� skip ���̺��� �̿��� �̵� �Ÿ� ���
		if (skip[str[str_p]] > len_2 - str_2p)
			str_p += skip[str[str_p]];
		else
			str_p += len_2 - str_2p;
	}

	return -1;
}

// �����ε�: C ���ڿ�
int MyString::BoyerMooreFind(int find_from, const char* str_2) const
{
	MyString temp(str_2);
	return BoyerMooreFind(find_from, temp);
}

// �����ε�: ���� 1��
int MyString::BoyerMooreFind(int find_from, const char c) const
{
	MyString temp(c);
	return BoyerMooreFind(find_from, temp);
}

// ���ڿ� �� (������, -1/0/1 ��ȯ)
int MyString::Compare(const MyString& str_2) const
{
	for (int i = 0; i < std::min(len,str_2.len); i++)
	{
		if (str[i] > str_2.str[i])
			return 1;
		else if (str[i] < str_2.str[i])
			return -1;
	}

	if (len == str_2.len)
		return 0;
	else if (len > str_2.len)
		return 1;

	return -1;
}

// ���� (MyString)
MyString& MyString::Assign(const MyString& str_2)
{
	if (str_2.len > memory_capacity)
	{
		delete[] str;
		str = new char[str_2.len + 1];
		memory_capacity = str_2.len;

	}
	for (int i = 0; i < str_2.len; i++)
		str[i] = str_2.str[i];

	str[str_2.len] = '\0';
	len = str_2.len;

	return *this;
}

// ���� (C ���ڿ�)
MyString& MyString::Assign(const char* str_2)
{
	int len_2 = strlen(str_2);
	if (len_2 > memory_capacity)
	{
		delete[] str;
		str = new char[len_2 + 1];
		memory_capacity = len_2;
	}

	for (int i = 0; i < len_2; i++)
		str[i] = str_2[i];

	str[len_2] = '\0';
	len = len_2;

	return *this;
}

// ���� (MyString)
MyString& MyString::Insert(int loc, const MyString& str_2)
{
	if (loc < 0) loc = 0;
	int new_len = len + str_2.len;
	if (new_len > memory_capacity)
	{
		// capacity Ȯ�� ��å (2�� or �ʿ��� ��ŭ)
		if (memory_capacity * 2 > new_len)
			memory_capacity *= 2;
		else
			memory_capacity = new_len;

		char* new_str = new char[memory_capacity + 1];
		// �պκ� ����
		for (int i = 0; i < loc; i++)
			new_str[i] = str[i];

		// ������ �κ� ����
		for (int i = 0; i < str_2.len; i++)
			new_str[loc + i] = str_2.str[i];

		// �޺κ� ����
		for (int i = loc; i < len; i++)
			new_str[str_2.len + i] = str[i];

		new_str[new_len] = '\0';
		delete[] str;

		len = new_len;
		str = new_str;

		return *this;
	}

	// capacity ����� �� 
	for (int i =len-1; i >= loc; i--)
		str[i + str_2.len] = str[i];

	for (int i = 0; i < str_2.len; i++)
		str[i + loc] = str_2.str[i];

	len = new_len;
	str[len] = '\0';

	return *this;
}

// ���� (C ���ڿ�)
MyString& MyString::Insert(int loc, const char* str_2)
{
	MyString temp(str_2);
	return Insert(loc, temp);
}

// ���� (���� 1��)
MyString& MyString::Insert(int loc, char c)
{
	MyString temp(c);
	return Insert(loc, temp);
}

// ���� (loc���� num�� ���� ����)
MyString& MyString::Erase(int loc, int num)
{
	if (num < 0 || loc < 0 || loc > len)
		return *this;

	// ���� ���� ����
	if (loc + num > len)
		num = len - loc;

	// �޺κ��� ������ ����
	for (int i = loc + num; i <= len; i++)
		str[i - num] = str[i];

	len -= num;

	return *this;
}

// ================== �׽�Ʈ�� main �Լ� ==================
int main()
{
	MyString s1("hello");           // "hello"
	MyString s2("world");           // "world"
	MyString s3(s1);                // ���� ������
	MyString s4('A');               // ���� 1��

	std::cout << "s1: "; s1.Print();
	std::cout << "s2: "; s2.Print();
	std::cout << "s3: "; s3.Print();
	std::cout << "s4: "; s4.Print();

	std::cout << "\nInsert 'world' into s1 at pos 3:\n";
	s1.Insert(3, s2);               // s1: "helworldlo"
	s1.Print();

	std::cout << "\nInsert 'world' into s1 at pos 3:\n";
	s1.BoyerMooreFind(3, s2);               // s1: "helworldlo"
	s1.Print();

	std::cout << "\nErase 3 chars from s1 at pos 2:\n";
	s1.Erase(2, 3);                 // s1: "heworldlo"
	s1.Print();

	std::cout << "\nCompare s2 and s3: " << s2.Compare(s3) << std::endl; // "world" vs "hello"

	std::cout << "\nFind 'lo' in s3: " << s3.Find(0, "lo") << std::endl; // "hello"���� "lo" ��ġ

	std::cout << "\nAssign s2 to s3:\n";
	s3.Assign(s2);                  // s3: "world"
	s3.Print();

	std::cout << "\nReserve 20 for s3:\n";
	s3.Reserve(20);                 // capacity �ø���
	std::cout << "s3 capacity: " << s3.MemoryCapacity() << std::endl;

	std::cout << "\nChar at position 1 of s3: " << s3.at(1) << std::endl; // 'o'

	return 0;
}
#include <iostream>

// MyString 클래스 선언
class MyString
{
	char* str;              // 문자열 데이터(동적 할당)
	int len;                // 문자열 길이
	int memory_capacity;    // 할당된 버퍼 크기(용량)
public:

	// 문자 1개로 생성
	MyString(char c)
	{
		str = new char[2];
		str[0] = c;
		str[1] = '\0';
		memory_capacity = 1;
		len = 1;
	}
	// C 문자열로 생성
	MyString(const char* str_2)
	{
		len = strlen(str_2);
		str = new char[len + 1];

		for (int i = 0; i < len; i++)
			str[i] = str_2[i];

		str[len] = '\0';
		memory_capacity = len;
	}
	// 복사 생성자
	MyString(const MyString& str_2)
	{
		len = str_2.len;
		str = new char[len+1];
		for (int i = 0; i < len; i++)
			str[i] = str_2.str[i];

		str[len] = '\0';
		memory_capacity = len;
	}
	// 소멸자
	~MyString()
	{
		delete[] str;
	}

	// 멤버 함수 선언
	void Print() const;                                 // 문자열 출력
	int MemoryCapacity() const;                         // capacity 반환
	void Reserve(int size);                             // capacity 예약
	char at(int i) const;                               // i번째 문자 반환
	int Find(int find_from, const MyString& str_2) const; // 부분 문자열 찾기
	int Find(int find_from, const char* str_2) const;
	int Find(int find_from, const char c) const;
	int BoyerMooreFind(int find_from, const MyString& str_2) const;
	int BoyerMooreFind(int find_from, const char* str_2) const;
	int BoyerMooreFind(int find_from, const char c) const;
	int Compare(const MyString& str_2) const;           // 문자열 비교

	MyString& Assign(const MyString& str_2);            // 대입
	MyString& Assign(const char* str_2);
	MyString& Insert(int loc, const MyString& str_2);   // 삽입
	MyString& Insert(int loc, const char* str_2);
	MyString& Insert(int loc, char c);
	MyString& Erase(int loc, int num);                  // 삭제
};

// 문자열 출력
void MyString::Print() const
{
	std::cout << str << std::endl;
}

// 현재 capacity 반환
int MyString::MemoryCapacity() const
{
	return memory_capacity;
}

// capacity 예약(재할당)
void MyString::Reserve(int size)
{
	if (size > memory_capacity)
	{
		char* buffer = str;

		str = new char[size+1];
		memory_capacity = size;

		// 실제 데이터만 복사
		for (int i = 0; i < size; i++)
			str[i] = buffer[i];

		str[len] = '\0';
		delete[] buffer;
	}
	// size <= memory_capacity면 아무 것도 안 함
}

// i번째 문자 반환 (범위 밖이면 '\0' 반환)
char MyString::at(int i) const
{
	if (i >= len || i < 0)
		return '\0';
	else
		return str[i];
}

// 부분 문자열 찾기 (MyString 버전)
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

// 부분 문자열 찾기 (C 문자열)
int MyString::Find(int find_from, const char* str_2) const
{
	MyString temp(str_2);
	return Find(find_from, temp);
}

// 문자 1개 찾기
int MyString::Find(int find_from, const char c) const
{
	MyString temp(c);
	return Find(find_from, temp);
}

// Boyer-Moore-Horspool 알고리즘을 이용한 부분 문자열 검색
int MyString::BoyerMooreFind(int find_from, const MyString& str_2) const
{
	int str_p = 0;      // 현재 검색 위치(메인 문자열에서)
	int str_2p = 0;     // 패턴 문자열에서의 인덱스
	int len_2 = str_2.len; // 패턴(찾을 문자열)의 길이
	int skip[UCHAR_MAX + 1]; // skip 테이블 (패턴 내 문자별 이동 거리)

	// 예외 처리: 찾을 패턴이 비었거나, 검색 시작 위치가 범위를 벗어남
	if (len_2 == 0 || find_from < 0 || find_from > len - len_2)
		return -1;

	//skip 테이블 초기화: 모든 문자에 대해 기본 이동 거리는 패턴 길이
	for (int i = 0; i < UCHAR_MAX + 1; i++)
		skip[i] = len_2;

	//skip 테이블 세팅: 패턴 내 각 문자에 대해 이동 거리 계산
	for (int i = 0; i < len_2 - 1; i++)
		skip[str_2.str[i]] = len_2 - i - 1;

	//검색 시작 위치 설정 (find_from부터 패턴 길이만큼 뒤에서 시작)
	str_p = find_from + len_2 - 1;

	//메인 문자열에서 패턴을 찾을 때까지 반복
	while (str_p < len)
	{
		str_2p = len_2 - 1;     // 패턴의 마지막 문자부터 비교
		int temp_p = str_p;     // 메인 문자열에서 비교 시작 위치

		//뒤에서부터 한 글자씩 비교
		while (str[temp_p] == str_2.str[str_2p])
		{
			if (str_2p == 0)
				return temp_p;	// 패턴 전체가 일치하면 시작 위치 반환

			temp_p--;
			str_2p--;
		}

		//불일치 시 skip 테이블을 이용해 이동 거리 계산
		if (skip[str[str_p]] > len_2 - str_2p)
			str_p += skip[str[str_p]];
		else
			str_p += len_2 - str_2p;
	}

	return -1;
}

// 오버로딩: C 문자열
int MyString::BoyerMooreFind(int find_from, const char* str_2) const
{
	MyString temp(str_2);
	return BoyerMooreFind(find_from, temp);
}

// 오버로딩: 문자 1개
int MyString::BoyerMooreFind(int find_from, const char c) const
{
	MyString temp(c);
	return BoyerMooreFind(find_from, temp);
}

// 문자열 비교 (사전식, -1/0/1 반환)
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

// 대입 (MyString)
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

// 대입 (C 문자열)
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

// 삽입 (MyString)
MyString& MyString::Insert(int loc, const MyString& str_2)
{
	if (loc < 0) loc = 0;
	int new_len = len + str_2.len;
	if (new_len > memory_capacity)
	{
		// capacity 확장 정책 (2배 or 필요한 만큼)
		if (memory_capacity * 2 > new_len)
			memory_capacity *= 2;
		else
			memory_capacity = new_len;

		char* new_str = new char[memory_capacity + 1];
		// 앞부분 복사
		for (int i = 0; i < loc; i++)
			new_str[i] = str[i];

		// 삽입할 부분 복사
		for (int i = 0; i < str_2.len; i++)
			new_str[loc + i] = str_2.str[i];

		// 뒷부분 복사
		for (int i = loc; i < len; i++)
			new_str[str_2.len + i] = str[i];

		new_str[new_len] = '\0';
		delete[] str;

		len = new_len;
		str = new_str;

		return *this;
	}

	// capacity 충분할 때 
	for (int i =len-1; i >= loc; i--)
		str[i + str_2.len] = str[i];

	for (int i = 0; i < str_2.len; i++)
		str[i + loc] = str_2.str[i];

	len = new_len;
	str[len] = '\0';

	return *this;
}

// 삽입 (C 문자열)
MyString& MyString::Insert(int loc, const char* str_2)
{
	MyString temp(str_2);
	return Insert(loc, temp);
}

// 삽입 (문자 1개)
MyString& MyString::Insert(int loc, char c)
{
	MyString temp(c);
	return Insert(loc, temp);
}

// 삭제 (loc부터 num개 문자 삭제)
MyString& MyString::Erase(int loc, int num)
{
	if (num < 0 || loc < 0 || loc > len)
		return *this;

	// 삭제 범위 보정
	if (loc + num > len)
		num = len - loc;

	// 뒷부분을 앞으로 당기기
	for (int i = loc + num; i <= len; i++)
		str[i - num] = str[i];

	len -= num;

	return *this;
}

// ================== 테스트용 main 함수 ==================
int main()
{
	MyString s1("hello");           // "hello"
	MyString s2("world");           // "world"
	MyString s3(s1);                // 복사 생성자
	MyString s4('A');               // 문자 1개

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

	std::cout << "\nFind 'lo' in s3: " << s3.Find(0, "lo") << std::endl; // "hello"에서 "lo" 위치

	std::cout << "\nAssign s2 to s3:\n";
	s3.Assign(s2);                  // s3: "world"
	s3.Print();

	std::cout << "\nReserve 20 for s3:\n";
	s3.Reserve(20);                 // capacity 늘리기
	std::cout << "s3 capacity: " << s3.MemoryCapacity() << std::endl;

	std::cout << "\nChar at position 1 of s3: " << s3.at(1) << std::endl; // 'o'

	return 0;
}
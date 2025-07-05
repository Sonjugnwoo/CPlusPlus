#include <iostream>
#include <cstring>

class string
{
    char* str;
    int len;
public:
    // 문자 c를 size번 반복한 문자열 생성자
    string(char c, int size)
    {
        len = size;
        str = new char[len + 1];
        for (int i = 0; i < len; i++)
            str[i] = c;
        str[len] = '\0';
    }
    // C 문자열로부터 생성자
    string(const char* c)
    {
        len = std::strlen(c);
        str = new char[len + 1];
        std::strcpy(str, c);
    }
    ~string()
    {
        delete[] str;
    }

    // 문자열 길이 반환
    int Strlen() const
    {
        return len;
    }

    // 문자열 뒤에 다른 문자열을 이어붙임
    void Append(const string& c)
    {
        int new_len = len + c.len;
        char* new_str = new char[new_len + 1];
        std::strcpy(new_str, str);
        std::strcat(new_str, c.str);
        delete[] str;
        str = new_str;
        len = new_len;
    }

    // 부분 문자열 검색
    void Find(const string& c) const
    {
        if (std::strstr(str, c.str) != nullptr)
            std::cout << "존재" << std::endl;
        else
            std::cout << "없음" << std::endl;
    }

    // 문자열 전체 비교
    void Compare(const string& c) const
    {
        if (std::strcmp(str, c.str) == 0)
            std::cout << "같음" << std::endl;
        else
            std::cout << "다름" << std::endl;
    }

    // 사전순 비교
    void SizeCompare(const string& c) const
    {
        int temp = std::strcmp(str, c.str);

        if (temp == 0)
            std::cout << "같음" << std::endl;
        else if (temp > 0)
            std::cout << "str이 더 큽니다." << std::endl;
        else
            std::cout << "c가 더 큽니다." << std::endl;
    }

    // 문자열 출력 함수
    void print() const
    {
        std::cout << str << std::endl;
    }
};

int main() {
    string s1('A', 5);      // "AAAAA"
    string s2("Hello!");    // "Hello!"

    s1.print(); // AAAAA
    s2.print(); // Hello!

    s1.Append(s2);
    s1.print(); // AAAAAHello!

    s1.Find(string("Hello")); // 존재
    s1.Compare(s2);           // 다름
    s2.Compare(string("Hello!")); // 같음
    s1.SizeCompare(s2);       // str이 더 큽니다. (사전순 비교)

    return 0;
}
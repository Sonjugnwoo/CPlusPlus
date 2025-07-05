#include <iostream>
#include <cstring>

class string
{
    char* str;
    int len;
public:
    // ���� c�� size�� �ݺ��� ���ڿ� ������
    string(char c, int size)
    {
        len = size;
        str = new char[len + 1];
        for (int i = 0; i < len; i++)
            str[i] = c;
        str[len] = '\0';
    }
    // C ���ڿ��κ��� ������
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

    // ���ڿ� ���� ��ȯ
    int Strlen() const
    {
        return len;
    }

    // ���ڿ� �ڿ� �ٸ� ���ڿ��� �̾����
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

    // �κ� ���ڿ� �˻�
    void Find(const string& c) const
    {
        if (std::strstr(str, c.str) != nullptr)
            std::cout << "����" << std::endl;
        else
            std::cout << "����" << std::endl;
    }

    // ���ڿ� ��ü ��
    void Compare(const string& c) const
    {
        if (std::strcmp(str, c.str) == 0)
            std::cout << "����" << std::endl;
        else
            std::cout << "�ٸ�" << std::endl;
    }

    // ������ ��
    void SizeCompare(const string& c) const
    {
        int temp = std::strcmp(str, c.str);

        if (temp == 0)
            std::cout << "����" << std::endl;
        else if (temp > 0)
            std::cout << "str�� �� Ů�ϴ�." << std::endl;
        else
            std::cout << "c�� �� Ů�ϴ�." << std::endl;
    }

    // ���ڿ� ��� �Լ�
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

    s1.Find(string("Hello")); // ����
    s1.Compare(s2);           // �ٸ�
    s2.Compare(string("Hello!")); // ����
    s1.SizeCompare(s2);       // str�� �� Ů�ϴ�. (������ ��)

    return 0;
}
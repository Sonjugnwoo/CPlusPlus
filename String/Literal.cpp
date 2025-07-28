#include <iostream>
#include <string>

using namespace std::literals; // "hello"s �� ���� ���� �ʿ�

int main() {
    // std::string ���ͷ� ���̻� s ���
    auto s1 = "hello"s;
    std::cout << "s1 ���ڿ�: " << s1 << std::endl;
    std::cout << "s1 ����: " << s1.size() << std::endl;

    // ������ �ʱ�ȭ
    std::string str = "hello";
    std::cout << "str ���ڿ�: " << str << std::endl;
    std::cout << "str ����: " << str.size() << std::endl;

    // ���̵� ���ڿ�  (�����ڵ� ���� ó���� �ʿ��� ȯ�濡�� ��� Ư�� Windows API ȣ�� ���� ���� ���)
    std::wstring wstr = L"hello";
    std::wcout << L"wstr ���̵� ���ڿ�: " << wstr << std::endl;
    std::wcout << L"wstr ����: " << wstr.size() << std::endl;

    // ���� ���ڿ� ���ͷ� (JSON,XML,����ǥ���� �� ������ ���ڿ� ���ϰ� ǥ���� ��� )
    std::string r_str = R"foo(�ƹ��ų� �Է°���
  \n\n �̷��͵� �ʿ� ���� );)foo";   // ���� ���� foo �� ��ȣ ����
    std::cout << "r_str ���� ���ڿ�:\n" << r_str << std::endl;
    std::cout << "r_str ����: " << r_str.size() << std::endl;

    return 0;
}
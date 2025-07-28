#include <iostream>
#include <string>

using namespace std::literals; // "hello"s 를 쓰기 위해 필요

int main() {
    // std::string 리터럴 접미사 s 사용
    auto s1 = "hello"s;
    std::cout << "s1 문자열: " << s1 << std::endl;
    std::cout << "s1 길이: " << s1.size() << std::endl;

    // 전통적 초기화
    std::string str = "hello";
    std::cout << "str 문자열: " << str << std::endl;
    std::cout << "str 길이: " << str.size() << std::endl;

    // 와이드 문자열  (유니코드 문자 처리가 필요한 환경에서 사용 특히 Windows API 호출 에서 많이 사용)
    std::wstring wstr = L"hello";
    std::wcout << L"wstr 와이드 문자열: " << wstr << std::endl;
    std::wcout << L"wstr 길이: " << wstr.size() << std::endl;

    // 원시 문자열 리터럴 (JSON,XML,정규표현식 등 복잡한 문자열 편하게 표현시 사용 )
    std::string r_str = R"foo(아무거나 입력가능
  \n\n 이런것도 필요 없음 );)foo";   // 양쪽 끝에 foo 는 괄호 역할
    std::cout << "r_str 원시 문자열:\n" << r_str << std::endl;
    std::cout << "r_str 길이: " << r_str.size() << std::endl;

    return 0;
}
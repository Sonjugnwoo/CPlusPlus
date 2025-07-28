#include <iostream>
#include <string>

void* operator new(std::size_t count) {
	std::cout << count << "bytes 할당 " << std::endl;
	return malloc(count);
}

int main() {

	// s1에 긴 문자열 할당 → 내부 버퍼 크기 초과로 힙 메모리 동적 할당 발생
	// operator new 호출되어 할당 바이트 수 출력됨
	std::cout << "s1 생성" << std::endl;
	std::string s1 = "this is a pretty long sentence!!";
	std::cout << "s1 크기 :" << sizeof(s1) << std::endl;

	// s2에 짧은 문자열 할당 → 대부분의 구현에서 SSO 적용으로 내부 버퍼에 저장
	// 동적 할당 없이 저장되어 operator new 호출이 안 나올 수 있음
	std::cout << "s2 생성" << std::endl;
	std::string s2 = "short setence";
	std::cout << "s1 크기 : " << sizeof(s2) << std::endl;


}
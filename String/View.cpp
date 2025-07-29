#include <iostream>
#include <string>


void* operator new(std::size_t count) {
	std::cout << count << "bytes 할당 " << std::endl;
	return malloc(count);
}

//문자열에 very  있으면 true 반환 
bool contains_very(const std::string& str) {	 //읽기만 하기 때문에 const 
	return str.find("very") != std::string::npos;
}

//C++ 17 이상  std::string_view 가 추가 됨 
// string_view 생성시 메모리 할당 필요 없음 
/*
bool contains_very(const std::string_view str) {	 //읽기만 하기 때문에 const 
	return str.find("very") != std::string_view::npos;
}*/
int main() {

	//암묵적으로 std::string 객체 불필요하게 생성 
	std::cout << std::boolalpha << contains_very("C++ string is very hard to ues") << std::endl;

	std::cout << contains_very("C++ string is not easy to ues") << std::endl;
}
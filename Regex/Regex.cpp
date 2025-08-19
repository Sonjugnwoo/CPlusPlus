// 1.문자열이 주어진 규칙에 맞는지 확인 
// 2.문자열에서 원하는 패턴의 문자열 검색
// 3.문자열에서 원하는 패턴의 문자열로 치환 

#include <iostream>
#include <regex>
#include <vector>

int main() {
	std::vector<std::string> file_names = { "db-123-log.txt","db-124-log.txt", "not-db-log.txt", "db-12-log.txt", "db-12-log.jpg", };

	// 정규표현식: "db-" 뒤에 숫자 0개 이상(\d*), "-log.txt" 로 끝나는 문자열
	std::regex re("db-\\d*-log\\.txt");

	// regex_match는 문자열 전체가 패턴과 일치할 경우 true 반환
	for (const auto& file_name : file_names)
		std::cout << file_name << " : " << std::boolalpha << std::regex_match(file_name, re) << std::endl;
}
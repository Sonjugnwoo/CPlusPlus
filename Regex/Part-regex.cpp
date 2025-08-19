#include <iostream>
#include <vector>
#include <regex>

int main() {
	std::vector<std::string> phone_numbers = { "010-1234-5678", "010-123-4567",
                                            "011-1234-5567", "010-12345-6789",
                                            "123-4567-8901", "010-1234-567" };
    // 정규식 설명
    // [01]{3}  : 0 또는 1이 3번 반복 (예: 010, 011)
    // -        : 구분자 하이픈
    // (\\d{3,4}): 3~4자리 숫자를 그룹으로 캡처
    // -        : 구분자 하이픈
    // \\d{4}   : 4자리 숫자
    std::regex re("[01]{3}-(\\d{3,4})-\\d{4}");
    std::smatch match;
    for (const auto& number : phone_numbers) {    // 매칭된 부분과 캡처된 그룹 출력
        if (std::regex_match(number, match, re)) {
            for (size_t i = 0; i < match.size(); i++)
                std::cout << "Match : " << match[i].str() << std::endl;

            std::cout << "-------------------\n";
        }
    }
}
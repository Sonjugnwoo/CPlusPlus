#include <iostream>
#include <vector>
#include <regex>

int main() {
	std::vector<std::string> phone_numbers = { "010-1234-5678", "010-123-4567",
                                            "011-1234-5567", "010-12345-6789",
                                            "123-4567-8901", "010-1234-567" };
    // ���Խ� ����
    // [01]{3}  : 0 �Ǵ� 1�� 3�� �ݺ� (��: 010, 011)
    // -        : ������ ������
    // (\\d{3,4}): 3~4�ڸ� ���ڸ� �׷����� ĸó
    // -        : ������ ������
    // \\d{4}   : 4�ڸ� ����
    std::regex re("[01]{3}-(\\d{3,4})-\\d{4}");
    std::smatch match;
    for (const auto& number : phone_numbers) {    // ��Ī�� �κа� ĸó�� �׷� ���
        if (std::regex_match(number, match, re)) {
            for (size_t i = 0; i < match.size(); i++)
                std::cout << "Match : " << match[i].str() << std::endl;

            std::cout << "-------------------\n";
        }
    }
}
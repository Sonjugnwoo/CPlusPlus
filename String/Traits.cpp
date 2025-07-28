#include <cctype>
#include <iostream>
#include <string>

//char_traits  : 문자와 문자열들 간에 간단한연산을 제공하는 클래스
//제공되는 함수는 전부 static (Statelee)
struct my_char_traits : public std::char_traits<char> {

	// 비숫자 문자는 ASCII 값 그대로 반환
	static int get_real_rank(char c) {
		if (isdigit(c)) return c + 256;		 // 숫자가 문자보다 큼

		return c;
	}

	// 두 문자 c1, c2의 대소 비교 함수
	static bool lt(char c1, char c2) {
		return get_real_rank(c1) < get_real_rank(c2);
	}

	// 두 문자열 s1과 s2를 최대 n개 문자까지 비교하는 함수
	static int compare(const char* s1, const char* s2, size_t n) {
		while (n-- != 0) {
			if (get_real_rank(*s1) < get_real_rank(*s2)) return -1;
			if (get_real_rank(*s1) > get_real_rank(*s2)) return 1;

			s1++;
			s2++;
		}
		return 0;
	}
};

int main() {
	std::basic_string<char, my_char_traits> my_s1 = "1a";
	std::basic_string<char, my_char_traits> my_s2 = "a1";

	std::cout << std::boolalpha;
	std::cout << "숫자의 우선순위가 더 높은 문자열 비교 (my_s1 < my_s2)? " << (my_s1 < my_s2) << std::endl;

	std::string s1 = "1a";
	std::string s2 = "a1";

	std::cout << "일반 문자열 비교 (s1 < s2)? " << (s1 < s2) << std::endl;
}
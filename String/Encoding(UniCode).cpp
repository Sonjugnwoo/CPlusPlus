#include <iostream>
#include <string>

int main() {

	//							1234567890 123 4 567 
	// UTF-32 문자열 생성
	// std::u32string은 UTF-32 인코딩 방식으로,
	// 각 문자가 4바이트(32비트)로 고정되어 저장됨.
	// 문자열이 가진 '문자' 개수(코드포인트 개수)를 size()로 반환함.
	std::u32string u32_str = U"이건 UTF-32 문자열 입니다.";
	std::cout <<"UTF-32 문자열 크기 : " << u32_str.size() << std::endl;

	//							12 345678901 2 3456
	// UTF-8 문자열 생성 (가변 길이 멀티바이트 인코딩)
	// std::string에 UTF-8 리터럴(u8"")을 저장
	std::string str = u8"이건 UTF-8 문자열 입니다.";
	std::cout <<"UTF-8 문자열 크기 : " << u32_str.size() << std::endl;
	size_t i = 0; 
	size_t len = 0;

	while (i < str.size()) {
		int char_size = 0;
		// UTF-8 인코딩 기준:
	    // 1바이트 문자: 0xxxxxxx
	    // 2바이트 문자: 110xxxxx
	    // 3바이트 문자: 1110xxxx
	    // 4바이트 문자: 11110xxx

		if ((str[i] & 0b11111000) == 0b11110000)	char_size = 4;
		else if ((str[i] & 0b11110000) == 0b11100000) char_size = 3;
		else if ((str[i] & 0b11100000) == 0b11000000) char_size = 2;
		else if ((str[i] & 0b10000000) == 0b00000000) char_size = 1;
		else {
			std::cout << "이상한 문자 발견 " << std::endl;
			char_size = 1;
		}

		std::cout << str.substr(i, char_size) << std::endl;

		i += char_size;  // 다음 문자 시작 위치로 이동
		len++;          // 문자 개수 증가 (글자 개수 카운트)

	}
	std::cout << "문자열의 실제 길이 " << len << std::endl;
	
	//							1234567890 123 4 567
	std::u16string u16_str = u"이건 UTF-16 문자열 입니다";

	std::u16string str_2 = u"안녕하세요 이건 테스트 용 코드 입니다";
	// 한글 초성 자음 배열 (19자)
	std::string jaum[] = { "ㄱ","ㄲ","ㄴ","ㄷ","ㄹ","ㅁ" ,"ㅂ" ,"ㅅ" ,"ㅆ" ,
	  "ㅇ" ,"ㅈ" ,"ㅉ" ,"ㅊ" ,"ㅋ" ,"ㅌ" ,"ㅍ" ,"ㅎ" , "ㅎ", "ㅎ" };
	for (char16_t c : str_2) {
		// 한글 완성형 음절 범위 확인 (가 ~ 힣)
		if (!(0xAC00 <= c && c <= 0xD7A3)) continue;

		// 한글 음절 음절 번호(offset) 계산
		int offset = c - 0xAC00;

		// 초성 인덱스 계산 (offset / 588, 588=21*28)
		int jaum_offset = offset / 0x24C;  // 0x24C = 588 decimal

		std::cout << jaum[jaum_offset];
	}
}
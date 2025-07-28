#include <iostream>
#include <string>

int main() {

	//							1234567890 123 4 567 
	// UTF-32 ¹®ÀÚ¿­ »ı¼º
	// std::u32stringÀº UTF-32 ÀÎÄÚµù ¹æ½ÄÀ¸·Î,
	// °¢ ¹®ÀÚ°¡ 4¹ÙÀÌÆ®(32ºñÆ®)·Î °íÁ¤µÇ¾î ÀúÀåµÊ.
	// ¹®ÀÚ¿­ÀÌ °¡Áø '¹®ÀÚ' °³¼ö(ÄÚµåÆ÷ÀÎÆ® °³¼ö)¸¦ size()·Î ¹İÈ¯ÇÔ.
	std::u32string u32_str = U"ÀÌ°Ç UTF-32 ¹®ÀÚ¿­ ÀÔ´Ï´Ù.";
	std::cout <<"UTF-32 ¹®ÀÚ¿­ Å©±â : " << u32_str.size() << std::endl;

	//							12 345678901 2 3456
	// UTF-8 ¹®ÀÚ¿­ »ı¼º (°¡º¯ ±æÀÌ ¸ÖÆ¼¹ÙÀÌÆ® ÀÎÄÚµù)
	// std::string¿¡ UTF-8 ¸®ÅÍ·²(u8"")À» ÀúÀå
	std::string str = u8"ÀÌ°Ç UTF-8 ¹®ÀÚ¿­ ÀÔ´Ï´Ù.";
	std::cout <<"UTF-8 ¹®ÀÚ¿­ Å©±â : " << u32_str.size() << std::endl;
	size_t i = 0; 
	size_t len = 0;

	while (i < str.size()) {
		int char_size = 0;
		// UTF-8 ÀÎÄÚµù ±âÁØ:
	    // 1¹ÙÀÌÆ® ¹®ÀÚ: 0xxxxxxx
	    // 2¹ÙÀÌÆ® ¹®ÀÚ: 110xxxxx
	    // 3¹ÙÀÌÆ® ¹®ÀÚ: 1110xxxx
	    // 4¹ÙÀÌÆ® ¹®ÀÚ: 11110xxx

		if ((str[i] & 0b11111000) == 0b11110000)	char_size = 4;
		else if ((str[i] & 0b11110000) == 0b11100000) char_size = 3;
		else if ((str[i] & 0b11100000) == 0b11000000) char_size = 2;
		else if ((str[i] & 0b10000000) == 0b00000000) char_size = 1;
		else {
			std::cout << "ÀÌ»óÇÑ ¹®ÀÚ ¹ß°ß " << std::endl;
			char_size = 1;
		}

		std::cout << str.substr(i, char_size) << std::endl;

		i += char_size;  // ´ÙÀ½ ¹®ÀÚ ½ÃÀÛ À§Ä¡·Î ÀÌµ¿
		len++;          // ¹®ÀÚ °³¼ö Áõ°¡ (±ÛÀÚ °³¼ö Ä«¿îÆ®)

	}
	std::cout << "¹®ÀÚ¿­ÀÇ ½ÇÁ¦ ±æÀÌ " << len << std::endl;
	
	//							1234567890 123 4 567
	std::u16string u16_str = u"ÀÌ°Ç UTF-16 ¹®ÀÚ¿­ ÀÔ´Ï´Ù";

	std::u16string str_2 = u"¾È³çÇÏ¼¼¿ä ÀÌ°Ç Å×½ºÆ® ¿ë ÄÚµå ÀÔ´Ï´Ù";
	// ÇÑ±Û ÃÊ¼º ÀÚÀ½ ¹è¿­ (19ÀÚ)
	std::string jaum[] = { "¤¡","¤¢","¤¤","¤§","¤©","¤±" ,"¤²" ,"¤µ" ,"¤¶" ,
	  "¤·" ,"¤¸" ,"¤¹" ,"¤º" ,"¤»" ,"¤¼" ,"¤½" ,"¤¾" , "¤¾", "¤¾" };
	for (char16_t c : str_2) {
		// ÇÑ±Û ¿Ï¼ºÇü À½Àı ¹üÀ§ È®ÀÎ (°¡ ~ ÆR)
		if (!(0xAC00 <= c && c <= 0xD7A3)) continue;

		// ÇÑ±Û À½Àı À½Àı ¹øÈ£(offset) °è»ê
		int offset = c - 0xAC00;

		// ÃÊ¼º ÀÎµ¦½º °è»ê (offset / 588, 588=21*28)
		int jaum_offset = offset / 0x24C;  // 0x24C = 588 decimal

		std::cout << jaum[jaum_offset];
	}
}
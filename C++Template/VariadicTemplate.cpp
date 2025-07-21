#include <iostream>
#include <cstring>
#include <string>

size_t GetStringSize(const char* s) { return strlen(s); }		//C 스타일 문자열의 길이를 구함
size_t GetStringSize(const std::string& s) { return s.size(); }	// std::string의 길이를 구함

template <typename String, typename... Strings>			// 2개 이상의 문자열 인자가 들어왔을 때 각각의 길이의 합을 재귀적으로 구함
size_t GetStringSize(const String& s, Strings...strs) {
	return GetStringSize(s) + GetStringSize(strs...);	// 첫 번째 인자의 길이 + 나머지 인자들의 길이(재귀)
}

void AppendToString(std::string* concat_str) { return; }		// 재귀 종료: 더 이상 붙일 문자열이 없을 때(아무 일도 안 함)

template<typename String,typename... Strings>
void AppendToString(std::string* concat_str, const String& s, Strings...strs) {		// 하나 이상의 문자열을 std::string에 이어 붙임(재귀적으로 호출)
	concat_str->append(s);                  // s를 문자열 끝에 추가
	AppendToString(concat_str, strs...);    // 나머지 인자들에 대해 재귀적으로 호출
}

template<typename String,typename...Strings>
std::string StrCat(const String& s, Strings...strs) {
	size_t total_size = GetStringSize(s, strs...);	   // 모든 인자의 길이의 합을 미리 구함
	std::string concat_str;

	concat_str.reserve(total_size);               // 미리 메모리 확보(성능 최적화)
	concat_str.append(s);
	AppendToString(&concat_str, strs...);         // 문자열을 하나씩 모두 이어붙임

	return concat_str;                            // 완성된 문자열 반환
}

int main() {
	std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"), " ", std::string("sentence"));
}

/*C++17 이상 Fold 사용

#include <iostream>
#include <string>
#include <cstring>

 문자열 길이 반환: std::string, const char* 모두 처리
size_t GetStringSize(const char* s) { return strlen(s); }
size_t GetStringSize(const std::string& s) { return s.size(); }

 fold expression을 사용하여 문자열 합치기
template<typename... Strings>
std::string StrCat(const Strings&... strs) {
	// 가변인자들의 총 길이 계산: binary left fold 사용
	size_t total_size = (GetStringSize(strs) + ...);

	std::string result;
	result.reserve(total_size); // 한 번에 필요한 만큼 메모리 할당

	// 각 인자를 result 뒤에 차례로 append: comma operator fold 사용
	(result.append(strs), ...);

	return result; // 최종 합쳐진 문자열 반환
}

int main() {
	// 다양한 타입의 문자열을 하나로 합쳐 출력
	std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"), " ", std::string("sentence")) << std::endl;
}
*/
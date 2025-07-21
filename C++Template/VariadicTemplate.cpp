#include <iostream>
#include <cstring>
#include <string>

size_t GetStringSize(const char* s) { return strlen(s); }		//C ��Ÿ�� ���ڿ��� ���̸� ����
size_t GetStringSize(const std::string& s) { return s.size(); }	// std::string�� ���̸� ����

template <typename String, typename... Strings>			// 2�� �̻��� ���ڿ� ���ڰ� ������ �� ������ ������ ���� ��������� ����
size_t GetStringSize(const String& s, Strings...strs) {
	return GetStringSize(s) + GetStringSize(strs...);	// ù ��° ������ ���� + ������ ���ڵ��� ����(���)
}

void AppendToString(std::string* concat_str) { return; }		// ��� ����: �� �̻� ���� ���ڿ��� ���� ��(�ƹ� �ϵ� �� ��)

template<typename String,typename... Strings>
void AppendToString(std::string* concat_str, const String& s, Strings...strs) {		// �ϳ� �̻��� ���ڿ��� std::string�� �̾� ����(��������� ȣ��)
	concat_str->append(s);                  // s�� ���ڿ� ���� �߰�
	AppendToString(concat_str, strs...);    // ������ ���ڵ鿡 ���� ��������� ȣ��
}

template<typename String,typename...Strings>
std::string StrCat(const String& s, Strings...strs) {
	size_t total_size = GetStringSize(s, strs...);	   // ��� ������ ������ ���� �̸� ����
	std::string concat_str;

	concat_str.reserve(total_size);               // �̸� �޸� Ȯ��(���� ����ȭ)
	concat_str.append(s);
	AppendToString(&concat_str, strs...);         // ���ڿ��� �ϳ��� ��� �̾����

	return concat_str;                            // �ϼ��� ���ڿ� ��ȯ
}

int main() {
	std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"), " ", std::string("sentence"));
}

/*C++17 �̻� Fold ���

#include <iostream>
#include <string>
#include <cstring>

 ���ڿ� ���� ��ȯ: std::string, const char* ��� ó��
size_t GetStringSize(const char* s) { return strlen(s); }
size_t GetStringSize(const std::string& s) { return s.size(); }

 fold expression�� ����Ͽ� ���ڿ� ��ġ��
template<typename... Strings>
std::string StrCat(const Strings&... strs) {
	// �������ڵ��� �� ���� ���: binary left fold ���
	size_t total_size = (GetStringSize(strs) + ...);

	std::string result;
	result.reserve(total_size); // �� ���� �ʿ��� ��ŭ �޸� �Ҵ�

	// �� ���ڸ� result �ڿ� ���ʷ� append: comma operator fold ���
	(result.append(strs), ...);

	return result; // ���� ������ ���ڿ� ��ȯ
}

int main() {
	// �پ��� Ÿ���� ���ڿ��� �ϳ��� ���� ���
	std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"), " ", std::string("sentence")) << std::endl;
}
*/
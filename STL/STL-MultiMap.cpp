#include <iostream>
#include <map>
#include <string>

template <typename T,typename V>
void print_multimap(std::multimap<T, V>& t) {
	for (const auto& elem : t)
		std::cout << elem.first << " : " << elem.second << std::endl;
}

int main() {
	std::multimap<int, std::string> m;

	m.insert(std::make_pair(1, "hello"));
	m.insert(std::make_pair(1, "hi"));
	m.insert(std::make_pair(2, "hihi"));
	m.insert(std::make_pair(3, "hello"));
	m.insert(std::make_pair(2, "hello hello"));

	auto range = m.equal_range(1);  // Ű�� 1�� ���ҵ��� ������ ��ȯ (pair of iterators)

	for (auto itr = range.first; itr != range.second; ++itr)
		std::cout << itr->first << " : " << itr->second << std::endl;

	std::cout << "\n��ü multimap ���:" << std::endl;
	print_multimap(m);
}
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

	auto range = m.equal_range(1);  // 키가 1인 원소들의 범위를 반환 (pair of iterators)

	for (auto itr = range.first; itr != range.second; ++itr)
		std::cout << itr->first << " : " << itr->second << std::endl;

	std::cout << "\n전체 multimap 출력:" << std::endl;
	print_multimap(m);
}
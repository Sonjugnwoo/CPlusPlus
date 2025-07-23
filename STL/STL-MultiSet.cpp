#include <iostream>
#include <set>
#include <string>

template <typename T>
void print_mulitset(std::multiset<T>& t) {
	for (const auto& elem : t)
		std::cout << elem << std::endl;
}

int main() {
	std::multiset<std::string> str;

	str.insert("A");
	str.insert("A");

	str.insert("B");
	str.insert("B");
	str.insert("C");
	str.insert("DA");

	print_mulitset(str);
}
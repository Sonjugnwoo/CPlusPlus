#include <filesystem>
#include <iostream>


int main() {
	std::filesystem::path p("./some_file");

	std::cout << "Dose" << p << "exist? [" << std::boolalpha << std::filesystem::exists(p) << "]" << std::endl;
	std::cout << "Is" << p << "filse? [ " << std::filesystem::is_regular_file(p) << "]" << std::endl;
	std::cout << "Is" << p << "directory? [" << std::filesystem::is_directory(p) << "]" << std::endl;
}
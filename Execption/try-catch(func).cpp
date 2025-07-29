#include <iostream>
#include <string>

int func(int c) {
	if (c == 1) throw 10;                      // int 예외 throw
	else if (c == 2) throw std::string("hi"); // std::string 예외 throw
	else if (c == 3) throw 'a';                // char 예외 throw
	else if (c == 4) throw "hello";            // const char* (string literal) 예외 throw
	return 0;
}
int main() {
	int c;
	std::cin >> c;

	try {
		func(c);
	}
	catch (char x) {
		std::cout << "Char : " << x << std::endl;
	}
	catch (int x) {
		std::cout << "Int : " << x << std::endl;
	}
	catch (std::string& x) {
		std::cout << "String : " << x << std::endl;
	}
	catch (const char* x) {
		std::cout << "String Literal : " << x << std::endl;
	}

}
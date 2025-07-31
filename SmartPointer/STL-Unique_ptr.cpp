#include <iostream>
#include <memory>
#include <vector>

//emplace_back() : 완벽한 전달을 통해 직접 unique_ptr에 생성자에 전달 후 vector 맨뒤에 unique_ptr 객체 생성 


class A {
	int* data;
	
public:
	A(int i) {
		std::cout << "자원 획득 " << std::endl;
		data = new int[100];
		data[0] = i;
	}

	void some() { std::cout << "값 : "<< data[0] << std::endl; }

	~A() {
		std::cout << "자원 해제" << std::endl;
		delete[] data;
	}
};

int main() {
	std::vector<std::unique_ptr<A>> vec;

	vec.emplace_back(new A(1));				//vec.push_back(std::qunique_ptr<A>(new A(1))); 과 동일 
	vec.back()->some();

	vec.emplace_back(std::make_unique<A>(5));		//임시 unique_ptr를 만들어 바로 이동시키는 방식
	vec.back()->some();
}
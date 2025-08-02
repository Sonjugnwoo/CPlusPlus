#include <iostream>
#include <string>
#include <memory>
#include <vector>

class A {
	std::string s;
	std::weak_ptr<A> other;	 // 다른 A 객체를 약하게 참조

public:
	A(const std::string& s) : s(s) { std::cout << "자원 획득" << std::endl; }

	~A() { std::cout << "소멸자 호출" << std::endl; }

	void set_other(std::weak_ptr<A> o) { other = o; }	  // other 멤버에 weak_ptr<A> 값 할당

	 // other가 가리키는 객체에 접근 시도
	void access_other() {

		std::shared_ptr<A> o = other.lock();	// weak_ptr이 유효한지 확인하고 shared_ptr로 변환

		if (o) std::cout << "접근 :" << o->name() << std::endl;
		else std::cout << "이미 소멸" << std::endl;
	}

	std::string name() { return s; }
};

int main() {
	std::vector<std::shared_ptr<A>> vec;	 // A 객체를 저장할 vector

	// "자원 1", "자원 2"를 갖는 A 객체 2개를 vector에 저장
	vec.push_back(std::make_shared<A>("자원 1"));
	vec.push_back(std::make_shared<A>("자원 2"));

	// 두 객체가 서로를 weak_ptr로 참조하도록 설정(순환 참조 방지)
	vec[0]->set_other(vec[1]);
	vec[1]->set_other(vec[0]);

	std::cout << "vec[0] ref count : " << vec[0].use_count() << std::endl;
	std::cout << "vec[1] ref count : " << vec[1].use_count() << std::endl;

	vec[0]->access_other();	    // 0번 객체가 1번 객체에 접근 시도("접근 :자원 2" 출력)

	vec.pop_back();				// 벡터에서 마지막 원소(자원2)를 pop_back으로 제거(자원2 소멸)
	

	vec[0]->access_other();     // 다시 0번 객체에서 other(이미 소멸된 자원2)에 접근 시도 ("이미 소멸" 출력)
}
#include <iostream>
#include <string>
#include <memory>
#include <vector>

class A {
	std::string s;
	std::weak_ptr<A> other;	 // �ٸ� A ��ü�� ���ϰ� ����

public:
	A(const std::string& s) : s(s) { std::cout << "�ڿ� ȹ��" << std::endl; }

	~A() { std::cout << "�Ҹ��� ȣ��" << std::endl; }

	void set_other(std::weak_ptr<A> o) { other = o; }	  // other ����� weak_ptr<A> �� �Ҵ�

	 // other�� ����Ű�� ��ü�� ���� �õ�
	void access_other() {

		std::shared_ptr<A> o = other.lock();	// weak_ptr�� ��ȿ���� Ȯ���ϰ� shared_ptr�� ��ȯ

		if (o) std::cout << "���� :" << o->name() << std::endl;
		else std::cout << "�̹� �Ҹ�" << std::endl;
	}

	std::string name() { return s; }
};

int main() {
	std::vector<std::shared_ptr<A>> vec;	 // A ��ü�� ������ vector

	// "�ڿ� 1", "�ڿ� 2"�� ���� A ��ü 2���� vector�� ����
	vec.push_back(std::make_shared<A>("�ڿ� 1"));
	vec.push_back(std::make_shared<A>("�ڿ� 2"));

	// �� ��ü�� ���θ� weak_ptr�� �����ϵ��� ����(��ȯ ���� ����)
	vec[0]->set_other(vec[1]);
	vec[1]->set_other(vec[0]);

	std::cout << "vec[0] ref count : " << vec[0].use_count() << std::endl;
	std::cout << "vec[1] ref count : " << vec[1].use_count() << std::endl;

	vec[0]->access_other();	    // 0�� ��ü�� 1�� ��ü�� ���� �õ�("���� :�ڿ� 2" ���)

	vec.pop_back();				// ���Ϳ��� ������ ����(�ڿ�2)�� pop_back���� ����(�ڿ�2 �Ҹ�)
	

	vec[0]->access_other();     // �ٽ� 0�� ��ü���� other(�̹� �Ҹ�� �ڿ�2)�� ���� �õ� ("�̹� �Ҹ�" ���)
}
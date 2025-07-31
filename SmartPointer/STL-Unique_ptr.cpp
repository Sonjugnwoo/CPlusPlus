#include <iostream>
#include <memory>
#include <vector>

//emplace_back() : �Ϻ��� ������ ���� ���� unique_ptr�� �����ڿ� ���� �� vector �ǵڿ� unique_ptr ��ü ���� 


class A {
	int* data;
	
public:
	A(int i) {
		std::cout << "�ڿ� ȹ�� " << std::endl;
		data = new int[100];
		data[0] = i;
	}

	void some() { std::cout << "�� : "<< data[0] << std::endl; }

	~A() {
		std::cout << "�ڿ� ����" << std::endl;
		delete[] data;
	}
};

int main() {
	std::vector<std::unique_ptr<A>> vec;

	vec.emplace_back(new A(1));				//vec.push_back(std::qunique_ptr<A>(new A(1))); �� ���� 
	vec.back()->some();

	vec.emplace_back(std::make_unique<A>(5));		//�ӽ� unique_ptr�� ����� �ٷ� �̵���Ű�� ���
	vec.back()->some();
}
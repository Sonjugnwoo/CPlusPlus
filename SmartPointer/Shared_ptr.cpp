#include <iostream>
#include <memory>
#include <vector>

class A {
	int* data;

public:
	A() {
		data = new int[100];
		std::cout << "�ڿ� ȹ��" << std::endl;
	}

	~A() {
		std::cout << "�Ҹ��� ȣ��" << std::endl;
		delete[] data;
	}
};

// Ŭ���� B�� std::enable_shared_from_this�� ��ӹ޾�, ��ü ���ο��� �ڽſ� ���� shared_ptr�� �����ϰ� ����
class B : public std::enable_shared_from_this<B> {
	int* data;

public:
	B() {
		data = new int[100];
		std::cout << "�ڿ� ȹ��" << std::endl;
	}

	~B() {
		std::cout << "�Ҹ��� ȣ��" << std::endl;
		delete[] data;
	}

	std::shared_ptr<B> get_shared_ptr() { return shared_from_this(); }	//std::enable_shared_from_this<B>�� shared_from_this() ȣ��
};

int main() {
	std::vector<std::shared_ptr<A>> vec1;				// A ��ü�� �����ϴ� ����Ʈ �����͸� �����ϴ� ���� ����
	vec1.push_back(std::shared_ptr<A>(new A()));		// vec1�� �� A ��ü�� ����Ű�� shared_ptr �߰� ,  new A()�� ���� ������ ��ü�� shared_ptr�� ���� ����
	

	std::cout << "�Ҹ�" << std::endl;		  // vec1�� ù ��° ��Ҹ� ����鼭 shared_ptr �Ҹ� , ���� ī��Ʈ 0�� �Ǿ� ���� A ��ü �Ҹ�
	vec1.erase(vec1.begin());


	std::shared_ptr<A> p1(new A());			 // p1�� �� A ��ü ����, ���� ī��Ʈ 1
	std::shared_ptr<A> p2(p1);				 // p2�� p1�� ������ ���� ��ü ����, ���� ī��Ʈ 2

	// p1�� p2 ��� ���� ��ü�� ����Ű�Ƿ� ���� ī��Ʈ�� 2
	std::cout << p1.use_count() << std::endl;  // ���: 2
	std::cout << p2.use_count() << std::endl;  // ���: 2

	std::shared_ptr<A> p3 = std::make_shared<A>();	  // p3�� make_shared�� ����� �� A ��ü ���� �� ����

	std::shared_ptr<B> pa1 = std::make_shared<B>();
	std::shared_ptr<B> pa2 = pa1->get_shared_ptr();		//�� shared_ptr�� ���� ��ü�� �����ϰ� ������

	std::cout << pa1.use_count() << std::endl;  // ���: 2
	std::cout << pa2.use_count() << std::endl;  // ���: 2
}
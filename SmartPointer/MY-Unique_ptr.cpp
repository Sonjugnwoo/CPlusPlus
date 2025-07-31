#include <iostream>
#include <vector>

// ���� ����Ʈ ������(MyUniquePtr) ���ø� Ŭ����
// ���� �迭(T*)�� �������� �����ϸ�, ���� ����, �̵� ��� ����� ����
template <typename T>
class MyUniquePtr {
	T* ptr;	//���� ������

public:
	MyUniquePtr() :ptr(nullptr) {}	//�⺻ ������ �ʱ���� nullptr
	MyUniquePtr(T* p) : ptr(p) {}	//������ ���ڸ� �޾� ���� ���� 

	MyUniquePtr(const MyUniquePtr& other) = delete;	// ���� ������ ����: ���� �Ұ� (���� ������ ����)

	MyUniquePtr(MyUniquePtr&& other) noexcept : ptr(other.ptr) {	//�̵� ������  ������ ���� ,  ���� �����ڴ� nullptr ó�� 
		other.ptr = nullptr;
	}

	MyUniquePtr& operator = (const MyUniquePtr& other) = delete;	// ���� ���� ������ ����: ���� ���� �Ұ�
	MyUniquePtr& operator = ( MyUniquePtr&& other) noexcept {		//�̵� ���� ������: ���� �ڿ� ���� �� ������ ����
		if (this != &other) {     // �ڱ� �ڽ��� �ƴ� ��쿡�� ó��
			delete[] ptr;          // ������ ������ �迭 �޸� ����
			ptr = other.ptr;       // ������ �̵�
			other.ptr = nullptr;   // ���� ������ null ó��
		}
		return *this;            
	};

	T& operator *() const { return *ptr;  }	//������ ������: ���� �����Ͱ� ����Ű�� �迭 ù ��ҿ� ���� ���� ��ȯ
	T* operator ->() const { return ptr; }	//��� ���� ������: ���� ������ ��ü�� ��ȯ (�迭�� ù �ּ�)

	~MyUniquePtr() {	//�Ҹ���: ������ �޸� ����, null üũ �� delete[]
		if (ptr != nullptr)
			delete[] ptr;
	}

	void get_data(T data) {	//���� ������ �� ���� �Լ�: �迭 ù ��° ���ҿ� �� ����
		ptr[0] = data;
 	}

	T* get() const { return ptr; }	//���� ���� ������ ��ȯ �Լ�: �ܺο��� �ּ� ���� ���� ����
};

template <typename T>
void data(MyUniquePtr<T>* ptr) {  ptr->get_data(static_cast<T>(3)); }	// // ������ Ÿ�� ĳ���� �� �Լ� ȣ��

int main() {
	// 1) �⺻ ������ �� nullptr ���� �׽�Ʈ
	MyUniquePtr<int> p1;
	std::cout << "p1 �ʱ� ���� ������: " << p1.get() << std::endl;

	// 2) ������ ���� ���� �׽�Ʈ
	MyUniquePtr<int> p2(new int[5]{ 10, 20, 30, 40, 50 });
	std::cout << "p2 �ʱ� ��(0��° ���): " << p2.get()[0] << std::endl;

	// 3) get_data() ��� �Լ� ȣ�� �׽�Ʈ
	data(&p2);
	std::cout << "p2 get_data �� ��(0��° ���): " << p2.get()[0] << std::endl; // 3 ���� ����� ��

	// 4) �̵� ������ �׽�Ʈ
	MyUniquePtr<int> p3(std::move(p2));
	std::cout << "p3 ��(0��° ���): " << p3.get()[0] << std::endl;
	std::cout << "p2 ���� ������ �� (�̵� ��): " << p2.get() << std::endl; // nullptr

	// 5) �̵� ���� ������ �׽�Ʈ
	MyUniquePtr<int> p4;
	p4 = std::move(p3);
	std::cout << "p4 ��(0��° ���): " << p4.get()[0] << std::endl;
	std::cout << "p3 ���� ������ �� (�̵� ��): " << p3.get() << std::endl; // nullptr

	return 0;
}
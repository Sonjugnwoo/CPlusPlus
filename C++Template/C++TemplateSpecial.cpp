#include <iostream>
#include <string>

template <typename T>
class Vector {
	T* data;
	int capacity;
	int length;

public:
	typedef T value_type;
	Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}

	void push_back(T s) {
		if (capacity <= length) {
			T* temp = new T[capacity * 2];
			for (int i = 0; i < length; i++)
				temp[i] = data[i];

			delete[] data;
			data = temp;
			capacity *= 2;
		}
		data[length] = s;
		length++;
	}
	T operator[] (int i) { return data[i]; }
	void remove(int x) {
		for (int i = x + 1; i < length; i++)
			data[i - 1] = data[i];

		length--;
	}
	int size() { return length; }
	~Vector() {
		if (data)
			delete[] data;
	}
};
template<>
class Vector<bool> {

	unsigned int* data; // ��Ʈ�� �����ϹǷ� unsigned int �迭 ���
	int capacity;       // int ������ �Ҵ�� �뷮(�� �� int����)
	int length;         // ���� ����� bool ����

public:
	typedef bool value_type;
	
	// ������: �ʿ��� ��ŭ�� unsigned int �迭 ���� �� 0���� �ʱ�ȭ
	Vector(int n = 1) : data(new unsigned int[n / 32 + 1]), capacity(n / 32 + 1), length(0) {
	for(int i = 0 ; i <capacity;i++)
			data[i] = 0 ; 
	}

	// bool �� �߰�
	void push_back(bool s) {
		if (capacity <= length) { // ���� ���� �� ��������
			unsigned int* temp = new unsigned int[capacity * 2];
			for (int i = 0; i < length; i++)
				temp[i] = data[i];

			for (int i = capacity; i < 2 * capacity; i++)
				temp[i] = 0; // �� ���� 0���� �ʱ�ȭ

			delete[] data;
			data = temp;
			capacity *= 2;
		}
		if (s) // true�� ��쿡�� �ش� ��Ʈ 1�� ����
			data[length / 32] |= (1 << (length % 32));

		length++; // ���� ���� ����
	}

	// �� ��ȸ (i��° ��Ʈ�� 1�̸� true, �ƴϸ� false)
	bool operator[](int i) {
		return (data[i / 32] & (1 << (i % 32))) != 0;
	}

	// x��° bool ���� (���� ��Ʈ���� �� ĭ ������ ���)
	void remove(int x) {
		for (int i = x + 1; i < length; i++) {
			int prev = i - 1;
			int curr = i;

			if (data[curr / 32] & (1 << (curr % 32)))
				data[prev / 32] |= (1 << (prev % 32)); // ���� 1�� ����
			else {
				unsigned int all_ones_except_prev = 0xFFFFFFFF;
				all_ones_except_prev ^= (1 << (prev % 32)); // �ش� �ڸ��� 0
				data[prev / 32] &= all_ones_except_prev;     // ���� 0���� ����
			}
		}
		length--;
	}

	// ���� ���� ���� ��ȯ
	int size() { return length; }

	// �Ҹ���
	~Vector() {
		if (data)
			delete[] data;
	}
};

int main() {
	Vector<int> vec_int;
	Vector<std::string> vec_str;
	Vector<bool> vec_bool;

	// int �׽�Ʈ
	vec_int.push_back(10);
	vec_int.push_back(20);
	vec_int.push_back(30);

	std::cout << "Vector<int>: ";
	for (int i = 0; i < vec_int.size(); ++i)
		std::cout << vec_int[i] << " ";
	std::cout << std::endl;

	vec_int.remove(1); // 20 ����
	std::cout << "Vector<int> (remove index 1): ";
	for (int i = 0; i < vec_int.size(); ++i)
		std::cout << vec_int[i] << " ";
	std::cout << std::endl;

	// string �׽�Ʈ
	vec_str.push_back("hi");
	vec_str.push_back("world");

	std::cout << "Vector<string>: ";
	for (int i = 0; i < vec_str.size(); ++i)
		std::cout << vec_str[i] << " ";
	std::cout << std::endl;

	vec_str.remove(0); // "hi" ����
	std::cout << "Vector<string> (remove index 0): ";
	for (int i = 0; i < vec_str.size(); ++i)
		std::cout << vec_str[i] << " ";
	std::cout << std::endl;

	// bool �׽�Ʈ
	vec_bool.push_back(true);
	vec_bool.push_back(false);
	vec_bool.push_back(true);
	vec_bool.push_back(false);

	std::cout << "Vector<bool>: ";
	for (int i = 0; i < vec_bool.size(); ++i)
		std::cout << vec_bool[i] << " ";
	std::cout << std::endl;

	vec_bool.remove(1); // false(�� ��°) ����
	std::cout << "Vector<bool> (remove index 1): ";
	for (int i = 0; i < vec_bool.size(); ++i)
		std::cout << vec_bool[i] << " ";
	std::cout << std::endl;

	return 0;
}
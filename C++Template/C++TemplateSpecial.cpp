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

	unsigned int* data; // 비트로 저장하므로 unsigned int 배열 사용
	int capacity;       // int 단위로 할당된 용량(몇 개 int인지)
	int length;         // 실제 저장된 bool 개수

public:
	typedef bool value_type;
	
	// 생성자: 필요한 만큼의 unsigned int 배열 생성 및 0으로 초기화
	Vector(int n = 1) : data(new unsigned int[n / 32 + 1]), capacity(n / 32 + 1), length(0) {
	for(int i = 0 ; i <capacity;i++)
			data[i] = 0 ; 
	}

	// bool 값 추가
	void push_back(bool s) {
		if (capacity <= length) { // 공간 부족 시 리사이즈
			unsigned int* temp = new unsigned int[capacity * 2];
			for (int i = 0; i < length; i++)
				temp[i] = data[i];

			for (int i = capacity; i < 2 * capacity; i++)
				temp[i] = 0; // 새 공간 0으로 초기화

			delete[] data;
			data = temp;
			capacity *= 2;
		}
		if (s) // true일 경우에만 해당 비트 1로 설정
			data[length / 32] |= (1 << (length % 32));

		length++; // 원소 개수 증가
	}

	// 값 조회 (i번째 비트가 1이면 true, 아니면 false)
	bool operator[](int i) {
		return (data[i / 32] & (1 << (i % 32))) != 0;
	}

	// x번째 bool 삭제 (이후 비트들을 한 칸 앞으로 당김)
	void remove(int x) {
		for (int i = x + 1; i < length; i++) {
			int prev = i - 1;
			int curr = i;

			if (data[curr / 32] & (1 << (curr % 32)))
				data[prev / 32] |= (1 << (prev % 32)); // 값을 1로 복사
			else {
				unsigned int all_ones_except_prev = 0xFFFFFFFF;
				all_ones_except_prev ^= (1 << (prev % 32)); // 해당 자리만 0
				data[prev / 32] &= all_ones_except_prev;     // 값을 0으로 복사
			}
		}
		length--;
	}

	// 현재 저장 개수 반환
	int size() { return length; }

	// 소멸자
	~Vector() {
		if (data)
			delete[] data;
	}
};

int main() {
	Vector<int> vec_int;
	Vector<std::string> vec_str;
	Vector<bool> vec_bool;

	// int 테스트
	vec_int.push_back(10);
	vec_int.push_back(20);
	vec_int.push_back(30);

	std::cout << "Vector<int>: ";
	for (int i = 0; i < vec_int.size(); ++i)
		std::cout << vec_int[i] << " ";
	std::cout << std::endl;

	vec_int.remove(1); // 20 삭제
	std::cout << "Vector<int> (remove index 1): ";
	for (int i = 0; i < vec_int.size(); ++i)
		std::cout << vec_int[i] << " ";
	std::cout << std::endl;

	// string 테스트
	vec_str.push_back("hi");
	vec_str.push_back("world");

	std::cout << "Vector<string>: ";
	for (int i = 0; i < vec_str.size(); ++i)
		std::cout << vec_str[i] << " ";
	std::cout << std::endl;

	vec_str.remove(0); // "hi" 삭제
	std::cout << "Vector<string> (remove index 0): ";
	for (int i = 0; i < vec_str.size(); ++i)
		std::cout << vec_str[i] << " ";
	std::cout << std::endl;

	// bool 테스트
	vec_bool.push_back(true);
	vec_bool.push_back(false);
	vec_bool.push_back(true);
	vec_bool.push_back(false);

	std::cout << "Vector<bool>: ";
	for (int i = 0; i < vec_bool.size(); ++i)
		std::cout << vec_bool[i] << " ";
	std::cout << std::endl;

	vec_bool.remove(1); // false(두 번째) 삭제
	std::cout << "Vector<bool> (remove index 1): ";
	for (int i = 0; i < vec_bool.size(); ++i)
		std::cout << vec_bool[i] << " ";
	std::cout << std::endl;

	return 0;
}
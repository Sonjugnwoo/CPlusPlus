#include <iostream>
#include <stdexcept>

//throw 했는데 catch 가없으면 runtime_error 예외 발생시키며 프로그램이 비정상으로 종료 


template <typename T>
class Vector {
	T* data_;
	size_t size_;
public:
	Vector(size_t size) : size_(size), data_(new T[size_]) {
		for (size_t i = 0; i < size_; i++)
			data_[i] = 3;
	}

	// 복사 생성자
	Vector(const Vector& other) : size_(other.size_), data_(new T[other.size_]) {
		for (size_t i = 0; i < size_; ++i) {
			data_[i] = other.data_[i];
		}
	}

	// 복사 대입 연산자 
	Vector& operator=(const Vector& other) {
		if (this == &other) return *this;

		delete[] data_;
		size_ = other.size_;
		data_ = new T[size_];
		for (size_t i = 0; i < size_; ++i) {
			data_[i] = other.data_[i];
		}
		return *this;
	}

	const T& at(size_t index) const {
		if (index >= size_)
			throw std::out_of_range("vector 의 index 가 범위 초과");

		return data_[index];
	}
	~Vector() {
		delete[] data_;
	}

};

int main() {
	Vector<int> v(5);
	try {
		std::cout << v.at(0) << std::endl;  // 출력: 3
		std::cout << v.at(4) << std::endl;  // 출력: 3
		std::cout << v.at(6) << std::endl;  // 예외 발생
	}
	catch (const std::out_of_range& e) {
		std::cerr << "예외: " << e.what() << std::endl;
	}
}
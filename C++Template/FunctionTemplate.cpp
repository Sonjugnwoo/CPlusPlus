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

	void push_back(const T& s) {
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
	T operator[](int i) { return data[i]; }
	const T& operator[](int i) const { return data[i]; }

	void remove(int x) {
		for (int i = x + 1; i < length; i++)
			data[i - 1] = data[i];

		length--;
	}
	int size() { return length; }

	void swap(int a, int b) {
		T temp = data[a];
		data[a] = data[b];
		data[b] = temp;
	}
	~Vector() {
		if (data)
			delete[] data;
	}
};
template <typename Cont>
void bubble_sort(Cont& cont) {
	for (int i = 0; i < cont.size(); i++) {
		for (int j = i + 1; j < cont.size(); j++) {
			if (cont[i] > cont[j])
				cont.swap(i, j);
		}
	}
}
template<typename Cont>
void quick_sort(Cont& cont,int left , int right) {
	int first_idx = left;
	int last_idx = right;
	int pivot = cont[(left + right)/2] ;

	while (first_idx <= last_idx) {
		while (cont[first_idx] < pivot) first_idx++;
		while (cont[last_idx] > pivot) last_idx--;

		if (first_idx <= last_idx) {
			cont.swap(first_idx, last_idx);
			first_idx++;
			last_idx--;
		}
	}
	if (left < last_idx) quick_sort(cont, left, last_idx);
	if (first_idx < right) quick_sort(cont, first_idx, right);
}

int main() {
	Vector<int> bv,qv;
	bv.push_back(7);
	bv.push_back(3);
	bv.push_back(8);
	bv.push_back(1);
	bv.push_back(5);

	std::cout << "정렬 전: ";
	for (int i = 0; i < bv.size(); i++)
		std::cout << bv[i] << ' ';
	std::cout << std::endl;

	bubble_sort(bv);
	std::cout << "정렬 후: ";
	for (int i = 0; i < bv.size(); i++)
		std::cout << bv[i] << ' ';
	std::cout << std::endl << std::endl;
	
	qv.push_back(3);
	qv.push_back(1);
	qv.push_back(6);
	qv.push_back(2);
	qv.push_back(5);

	std::cout << "정렬 전: ";
	for (int i = 0; i < qv.size(); i++)
		std::cout << qv[i] << ' ';
	std::cout << std::endl;

	quick_sort(qv, 0 ,qv.size()-1);

	std::cout << "정렬 후: ";
	for (int i = 0; i < qv.size(); i++)
		std::cout << qv[i] << ' ';
	std::cout << std::endl;

	return 0;
}
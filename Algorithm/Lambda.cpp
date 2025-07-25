#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

//Lambda   ---> [Capture List](�޴� ����) -> ���� Ÿ��{�Լ� ��ü}    (���� ���� ���� ) 
//[Capture List] ---> [] : �ƹ��͵� ���� , [&a,b] : a�� ���۷��� ĸ�� b�� ���纻 
//					  [&] : �ܺ��� ��� ���� ���۷��� ĸ�� , [=] : �ܺ��� ��� �������� ���纻 ���� ĸ�� 

template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "]";
		begin++;
	}
	std::cout << std::endl;
}

class SomeClass {
	std::vector<int> vec2;
	int num_delete;

public:
	SomeClass() {
		vec2.push_back(3);
		vec2.push_back(1);
		vec2.push_back(6);
		vec2.push_back(2);
		vec2.push_back(9);
		vec2.push_back(5);

		num_delete = 0;

		std::cout << "SomeClass ������ ���� �� vec2: ";
		print(vec2.begin(), vec2.end());
		
		// ���� ĸó [this]�� this �����͸� ĸó�մϴ�.
		// -> ���� ���ο��� ��� ���� num_delete�� ���� ����
		vec2.erase(std::remove_if(vec2.begin(), vec2.end(),
			[this](int i) {				//  ��� ���� num_delete�� �����ϱ� ���� ���� ��ü �����͸� ĸó�ϴ� ��.
			if (this->num_delete >= 2)
				return false;
			else if (i % 2 == 1) {
				num_delete++;
				return true;
			}
			return false;
		}), vec2.end());

		std::cout << "SomeClass ������ ���� �� vec2: ";
		print(vec2.begin(), vec2.end());
	}


};

int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(7);
	vec.push_back(2);
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);

	std::cout << "ó�� Vec : ";
	print(vec.begin(), vec.end());

	std::cout << "Vec Ȧ�� 2���� ���� ";
	int num_erased = 0;	

	vec.erase(std::remove_if(vec.begin(), vec.end(),
		[&num_erased](int i) {			//num_erased �� ���۷����� ĸ�� (�Լ� ���ο��� �� ���� ���� )  & ������ ������ ���纻�� ��µ� ���°� const�� ���� �ٲ� �� ���� 
		if (num_erased >= 2)
			return false;
		else if (i % 2 == 1) {
			num_erased++;
			return true;
		}
		return false;
		})	,vec.end());

	print(vec.begin(), vec.end());

	std::cout << "\n--- SomeClass ��ü ���� �� vec2 ó�� ---\n";
	SomeClass someObject;   // �����ڿ��� vec2 ó�� �� ���

}
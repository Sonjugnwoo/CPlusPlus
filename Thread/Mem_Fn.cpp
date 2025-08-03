#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>

int main() {

	std::vector<int> a(1); // ũ�� 1
	std::vector<int> b(2); // ũ�� 2
	std::vector<int> c(4); // ũ�� 4
	std::vector<int> d(6); // ũ�� 6
	std::vector<int> e(8); // ũ�� 8

	//���͵��� 2���� ���� container�� ������� �߰��Ѵ�.
	std::vector<std::vector<int>> container;
	container.push_back(a);
	container.push_back(b);
	container.push_back(c);
	container.push_back(d);
	container.push_back(e);

	std::vector<int> size_vec(5);	//ũ�� 5

	//std::transform(�Է�_����, �Է�_��, ���_����, �Լ�)

	//std::mem_fn�� ����� size ��� �Լ� ȣ��
	// std::mem_fn�� �̿��� container �� ���(����)�� size() ��� �Լ��� ȣ���Ͽ� �� ����� size_vec�� ����
	std::transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&std::vector<int>::size));
	for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr)
		std::cout << "���� ũ�� " << *itr << std::endl;

	//���� �Լ��� �̿��Ͽ� container �� ����� size() ��ȯ ���� size_vec�� ����
	std::transform(container.begin(), container.end(), size_vec.begin(), [](const auto& v) {return v.size(); });
	for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr)
		std::cout << "���� ũ�� " << *itr << std::endl;

}
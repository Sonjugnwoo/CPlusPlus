#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>


template <typename T,typename V>
void print_unordered_map(std::unordered_map<T, V>& t) {
	for (const auto& elem : t)
		std::cout << elem.first << " : " << elem.second << std::endl;
}

template <typename T, typename V>

void is_exist(std::unordered_map<T, V>& t, T key) {
	auto itr = t.find(key);
	if (itr != t.end())
		std::cout << "���� " << itr->first << " : " << itr->second << std::endl;
	else
		std::cout << "����" << std::endl;
}

class Baseball {
	double batting;
	std::string name;

public:
	Baseball(double batting, std::string name) : batting(batting), name(name) {}

	bool operator==(const Baseball& ba) const {
		return batting == ba.batting && name == ba.name;
	}
	friend std::ostream& operator <<(std::ostream& o,const Baseball& ba);
	friend struct std::hash<Baseball>;
};

template<>
struct std::hash<Baseball> {
	size_t operator()(const Baseball& ba) const {
		std::hash<std::string> hash_func;  // ���ڿ� �ؽ� �Լ� ����
		std::hash<double> hash_double;

		return hash_double(ba.batting) ^ (hash_func(ba.name));	 
	}
};

std::ostream& operator <<(std::ostream& o, const Baseball& ba) {
	o << "Ÿ�� : " << ba.batting << " , �̸� " << ba.name;
	return o;
}

int main() {
	// Baseball ��ü�� Ű, string�� ������ �ϴ� unordered_map ����
	std::unordered_map<Baseball, std::string> player_map;

	// ������ ����
	player_map.insert({ Baseball(0.312, "������"), "Ÿ��" });
	player_map.insert({ Baseball(0.278, "�ں�ȣ"), "Ÿ��" });
	player_map.insert({ Baseball(0.295, "������"), "����" });

	// ��ü ������ ���
	std::cout << "��ü ���� ���:" << std::endl;
	print_unordered_map(player_map);
	std::cout << "----------------------" << std::endl;

	// ���� ���� Ȯ��
	is_exist(player_map, Baseball(0.312, "������"));  // ����
	is_exist(player_map, Baseball(0.300, "�̴�ȣ"));  // ����

	return 0;
}
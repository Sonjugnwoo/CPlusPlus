#include <iostream>
#include <map>
#include <string>

template <typename K,typename V>
void print_map(std::map<K,V>& m) {
	for (const auto& elem : m)
		std::cout << elem.first << ":" << elem.second << std::endl;

	// �ݺ��ڸ� ����� ��ȸ ����
	/*
	for (auto itr = m.begin(); itr != m.end(); ++itr)
		std::cout << itr->first << ":" << itr->second << std::endl;
	*/
}

template <typename K,typename V>
void search_map(std::map<K, V>& m,K key) {
	auto itr = m.find(key);
	if (itr != m.end())
		std::cout << key << "--->" << itr->second << std::endl;
	else
		std::cout << key << " ����" << std::endl;
}
int main() {
	//map  - > ���ø� ���ڷ� 2���� ���� Ű - �� 
	//Map�� ���δ� �׻� **Ű�� ��������(�����ڵ� ����)**���� ���ĵǾ� ����/��ȸ�˴ϴ�.
	std::map < std::string, double> pitcher_list;

	pitcher_list.insert(std::pair < std::string, double > ("�ڼ���", 2.33));
	//pair - > T1 first , T2 second 2���� ��ü�� ����� ������ ��ü 

	pitcher_list.insert(std::make_pair("������", 3.04));
	//make_pair - > ���ڷ� ������ ��ü�� ���� Ÿ�� �����ؼ� pair ��ü ����

	pitcher_list["����Ʈ"] = 3.56;
	// [] �� ���� ���� �߰� ���� 

	print_map(pitcher_list);

	std::cout << "�������� �����" << pitcher_list["������"] << std::endl;

	search_map(pitcher_list, std::string("����ȯ"));
	search_map(pitcher_list, std::string("������"));
}
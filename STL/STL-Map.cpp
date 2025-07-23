#include <iostream>
#include <map>
#include <string>

template <typename K,typename V>
void print_map(std::map<K,V>& m) {
	for (const auto& elem : m)
		std::cout << elem.first << ":" << elem.second << std::endl;

	// 반복자를 사용한 순회 예시
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
		std::cout << key << " 없음" << std::endl;
}
int main() {
	//map  - > 템플릿 인자로 2개를 가짐 키 - 값 
	//Map의 내부는 항상 **키의 오름차순(유니코드 기준)**으로 정렬되어 저장/순회됩니다.
	std::map < std::string, double> pitcher_list;

	pitcher_list.insert(std::pair < std::string, double > ("박세웅", 2.33));
	//pair - > T1 first , T2 second 2개의 객체를 멤버로 가지는 객체 

	pitcher_list.insert(std::make_pair("차우찬", 3.04));
	//make_pair - > 인자로 들어오는 객체를 보고 타입 추측해서 pair 객체 만듬

	pitcher_list["니퍼트"] = 3.56;
	// [] 을 통해 원소 추가 가능 

	print_map(pitcher_list);

	std::cout << "차우찬의 방어율" << pitcher_list["차우찬"] << std::endl;

	search_map(pitcher_list, std::string("오승환"));
	search_map(pitcher_list, std::string("차우찬"));
}
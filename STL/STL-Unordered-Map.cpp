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
		std::cout << "존재 " << itr->first << " : " << itr->second << std::endl;
	else
		std::cout << "없음" << std::endl;
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
		std::hash<std::string> hash_func;  // 문자열 해시 함수 생성
		std::hash<double> hash_double;

		return hash_double(ba.batting) ^ (hash_func(ba.name));	 
	}
};

std::ostream& operator <<(std::ostream& o, const Baseball& ba) {
	o << "타율 : " << ba.batting << " , 이름 " << ba.name;
	return o;
}

int main() {
	// Baseball 객체를 키, string을 값으로 하는 unordered_map 선언
	std::unordered_map<Baseball, std::string> player_map;

	// 데이터 삽입
	player_map.insert({ Baseball(0.312, "김현수"), "타자" });
	player_map.insert({ Baseball(0.278, "박병호"), "타자" });
	player_map.insert({ Baseball(0.295, "류현진"), "투수" });

	// 전체 데이터 출력
	std::cout << "전체 선수 목록:" << std::endl;
	print_unordered_map(player_map);
	std::cout << "----------------------" << std::endl;

	// 존재 여부 확인
	is_exist(player_map, Baseball(0.312, "김현수"));  // 존재
	is_exist(player_map, Baseball(0.300, "이대호"));  // 없음

	return 0;
}
#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

// 중복이나 순서와 관계 없이 조건을 '모두 만족하는지(all_of)', '하나라도 만족하는지(any_of)' 검사

// std::all_of(First, Last, Pred) : 반복자 구간 [First, Last)에서 모든 원소가 
// 조건적용자 Pred를 만족하면 true를 반환한다.  
// 단, 한 개라도 조건을 만족하지 않는 원소가 있으면 false를 반환한다.

// std::any_of(First, Last, Pred) : 반복자 구간 [First, Last)에서 적어도 하나의 원소가 
// 조건적용자 Pred를 만족하면 true를 반환한다.  
// 모든 원소가 조건을 만족하지 않으면 false를 반환한다.


template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "]";
		begin++;
	}
	std::cout << std::endl;
}

struct User {
	std::string name;
	int level;

	User(std::string name, int level) : name(name), level(level) {}
	bool operator ==(const User& user) const {
		return name == user.name && level == user.level;
	}
};

class Party {
	std::vector<User> users;

public:
	bool add_user(std::string name, int level) {
		User new_user(name, level);
		if (std::find(users.begin(), users.end(), new_user) != users.end()) return false;

		users.push_back(new_user);
		return true;
	}

	bool can_join_dungeon() {
		return std::all_of(users.begin(), users.end(), [](const User& user) {return user.level >= 15; });
	}

	bool can_item() {
		return std::any_of(users.begin(), users.end(), [](const User& user) {return user.level >= 19; });
	}

};

int main() {
	Party party;
	party.add_user("전사", 16);
	party.add_user("법사", 13);
	party.add_user("궁수", 19);
	party.add_user("사제", 20);
	party.add_user("도적", 12);

	std::cout << std::boolalpha;
	std::cout << "던전 입장 가능 ? " << party.can_join_dungeon() << std::endl;
	std::cout << "아이템 사용 가능 ? " << party.can_item() << std::endl;
}
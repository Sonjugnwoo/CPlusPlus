#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

// �ߺ��̳� ������ ���� ���� ������ '��� �����ϴ���(all_of)', '�ϳ��� �����ϴ���(any_of)' �˻�

// std::all_of(First, Last, Pred) : �ݺ��� ���� [First, Last)���� ��� ���Ұ� 
// ���������� Pred�� �����ϸ� true�� ��ȯ�Ѵ�.  
// ��, �� ���� ������ �������� �ʴ� ���Ұ� ������ false�� ��ȯ�Ѵ�.

// std::any_of(First, Last, Pred) : �ݺ��� ���� [First, Last)���� ��� �ϳ��� ���Ұ� 
// ���������� Pred�� �����ϸ� true�� ��ȯ�Ѵ�.  
// ��� ���Ұ� ������ �������� ������ false�� ��ȯ�Ѵ�.


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
	party.add_user("����", 16);
	party.add_user("����", 13);
	party.add_user("�ü�", 19);
	party.add_user("����", 20);
	party.add_user("����", 12);

	std::cout << std::boolalpha;
	std::cout << "���� ���� ���� ? " << party.can_join_dungeon() << std::endl;
	std::cout << "������ ��� ���� ? " << party.can_item() << std::endl;
}
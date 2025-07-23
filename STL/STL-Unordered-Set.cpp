#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>

template <typename T>
void print_unordered_set(std::unordered_set<T>& m) {
	for (const auto& elem : m)
		std::cout << elem << std::endl;
}

template <typename T>
void is_exist(std::unordered_set<T>& m ,T key) {
	auto itr = m.find(key);
	if (itr != m.end())
		std::cout << key << "존재 " << std::endl;
	else
		std::cout << key << "없음" << std::endl;
}

class Todo {
	int priority;
	std::string job_desc;

public:
	Todo(int priority, std::string job_desc) : priority(priority), job_desc(job_desc) {}

	bool operator ==(const Todo& t) const{
		if (priority == t.priority && job_desc == t.job_desc) return true;
		else return false;
	}

	friend std::ostream& operator<< (std::ostream& o, const Todo& t);
	friend struct std::hash<Todo>;
};

// std::hash 특수화: Todo 객체를 해시할 수 있도록 정의
template<>
struct std::hash<Todo> {
	size_t operator()(const Todo& t) const {
		std::hash<std::string> hash_func;  // 문자열 해시 함수 생성

		// 현재는 간단하게 우선순위 값을 직접 XOR 연산에 사용
		return t.priority ^ (hash_func(t.job_desc));
	}
};

std::ostream& operator<< (std::ostream& o, const Todo& t) {
	o << "[중요도 " << t.priority << " ]" << t.job_desc ;
	return o;
}


int main() {
	// Todo 객체를 저장하는 unordered_set 생성
	std::unordered_set<Todo> todo_set;

	// Todo 객체 삽입
	todo_set.insert(Todo(1, "빨래하기"));
	todo_set.insert(Todo(2, "장보기"));
	todo_set.insert(Todo(3, "코딩하기"));
	todo_set.insert(Todo(2, "장보기"));  // 중복된 항목, unordered_set 이므로 무시됨

	// 전체 Todo 목록 출력
	std::cout << "=== 전체 할 일 목록 ===" << std::endl;
	print_unordered_set(todo_set);

	// 특정 할 일 존재 여부 확인
	std::cout << "\n=== 특정 할 일 존재 여부 확인 ===" << std::endl;
	is_exist(todo_set, Todo(2, "장보기"));      // 존재하는 항목
	is_exist(todo_set, Todo(5, "책읽기"));      // 없는 항목

	return 0;
}
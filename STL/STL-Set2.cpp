#include <iostream>
#include <set>
#include <string>


template <typename T,typename C>
void print_set(std::set<T, C>& s) {
	for (const auto& elem : s)
		std::cout << elem << " " << std::endl;
}

class Todo {
	int priority;
	std::string job_desc;

public:
	Todo(int priority, std::string job_desc) : priority(priority), job_desc(job_desc) {}
	
	// TodoCmp 구조체가 Todo의 private 멤버에 접근할 수 있도록 friend 선언
	friend struct TodoCmp;


	friend std::ostream& operator<<(std::ostream& o, const Todo& td);
};


// Todo 객체의 정렬 기준을 위한 함수 객체 (비교자)
struct TodoCmp {
	// 정렬 기준: 우선순위가 같으면 job_desc 사전순 비교, 아니면 높은 priority 먼저
	bool operator()(const Todo& t1, const Todo& t2) const {
		if (t1.priority == t2.priority)
			return t1.job_desc < t2.job_desc; // 사전순 오름차순
		return t1.priority > t2.priority;     // priority 내림차순 (높은 게 먼저)
	}
};
std::ostream& operator<<(std::ostream& o, const Todo& td) {
	o << "[중요도 " << td.priority << "] " << td.job_desc;
	return o;
}

int main() {
	// TodoCmp 비교기준을 사용한 set 선언
	std::set<Todo, TodoCmp> todos;

	// 여러 할 일 추가
	todos.insert(Todo(1, "Write report"));
	todos.insert(Todo(3, "Prepare presentation"));
	todos.insert(Todo(2, "Reply emails"));
	todos.insert(Todo(3, "Call client"));

	// 정렬된 순서대로 출력
	print_set(todos);

	return 0;
}
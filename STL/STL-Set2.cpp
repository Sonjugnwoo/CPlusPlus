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
	
	friend struct TodoCmp;

	friend std::ostream& operator << (std::ostream& o, const Todo& td);
};
struct TodoCmp{
	bool operator()(const Todo& t1, const Todo& t2) const {
		if (t1.priority == t2.priority)
			return t1.job_desc < t2.job_desc;

		return t1.priority > t2.priority;
	}
};

std::ostream& operator<<(std::ostream& o, const Todo& td) {
	o << "[�߿䵵 " << td.priority << "] " << td.job_desc;
	return o;
}

int main() {
	// TodoCmp �񱳱����� ����� set ����
	std::set<Todo, TodoCmp> todos;

	// ���� �� �� �߰�
	todos.insert(Todo(1, "Write report"));
	todos.insert(Todo(3, "Prepare presentation"));
	todos.insert(Todo(2, "Reply emails"));
	todos.insert(Todo(3, "Call client"));

	// ���ĵ� ������� ���
	print_set(todos);

	return 0;
}
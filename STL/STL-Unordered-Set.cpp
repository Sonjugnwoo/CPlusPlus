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
		std::cout << key << "���� " << std::endl;
	else
		std::cout << key << "����" << std::endl;
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

// std::hash Ư��ȭ: Todo ��ü�� �ؽ��� �� �ֵ��� ����
template<>
struct std::hash<Todo> {
	size_t operator()(const Todo& t) const {
		std::hash<std::string> hash_func;  // ���ڿ� �ؽ� �Լ� ����

		// ����� �����ϰ� �켱���� ���� ���� XOR ���꿡 ���
		return t.priority ^ (hash_func(t.job_desc));
	}
};

std::ostream& operator<< (std::ostream& o, const Todo& t) {
	o << "[�߿䵵 " << t.priority << " ]" << t.job_desc ;
	return o;
}


int main() {
	// Todo ��ü�� �����ϴ� unordered_set ����
	std::unordered_set<Todo> todo_set;

	// Todo ��ü ����
	todo_set.insert(Todo(1, "�����ϱ�"));
	todo_set.insert(Todo(2, "�庸��"));
	todo_set.insert(Todo(3, "�ڵ��ϱ�"));
	todo_set.insert(Todo(2, "�庸��"));  // �ߺ��� �׸�, unordered_set �̹Ƿ� ���õ�

	// ��ü Todo ��� ���
	std::cout << "=== ��ü �� �� ��� ===" << std::endl;
	print_unordered_set(todo_set);

	// Ư�� �� �� ���� ���� Ȯ��
	std::cout << "\n=== Ư�� �� �� ���� ���� Ȯ�� ===" << std::endl;
	is_exist(todo_set, Todo(2, "�庸��"));      // �����ϴ� �׸�
	is_exist(todo_set, Todo(5, "å�б�"));      // ���� �׸�

	return 0;
}
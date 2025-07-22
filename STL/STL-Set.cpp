#include <iostream>
#include <set>
#include <string>

// ���� Ÿ�� T�� ���� std::set<T> ���� ���ҵ��� ����ϴ� �Լ�
template <typename T>
void print_set(const std::set<T>& s) {
    // �����̳� �� ��� ���Ҹ� ��ȸ�ϸ� ���
    for (const auto& elem : s) {
        std::cout << elem << std::endl;  // ostream ������<<�� �����ε� �Ǿ� �־�� ��
    }
}

// �� �� ����� ǥ���ϴ� Ŭ����
class Todo {
    int priority;         // �߿䵵 (���ڰ� Ŭ���� �켱������ ����)
    std::string job_desc; // �� �� ����

public:
    // ������: �켱������ �� �� ������ ����
    Todo(int priority, std::string job_desc) : priority(priority), job_desc(std::move(job_desc)) {}

    // ������ ���� �� ������ �����ε�
    bool operator<(const Todo& t) const {
        if (priority == t.priority)
            return job_desc < t.job_desc;           // �߿䵵�� ������ ���ڿ� ������ ��
        return priority > t.priority;                // �߿䵵�� ū ���� �� �켱(��)�� ��ġ
    }

    // ��� ������ �����ε带 ���� friend ����
    friend std::ostream& operator<<(std::ostream& o, const Todo& td);
};

// Todo ��ü�� ����� �� ȣ��Ǵ� �Լ�
std::ostream& operator<<(std::ostream& o, const Todo& td) {
    o << "[�߿䵵 " << td.priority << "] " << td.job_desc;
    return o;
}

int main() {
	std::set<Todo> todos;
	todos.insert(Todo(1, "Write report"));
	todos.insert(Todo(3, "Prepare presentation"));
	todos.insert(Todo(2, "Reply emails"));
	todos.insert(Todo(3, "Call client"));

	print_set(todos);
	return 0;
}
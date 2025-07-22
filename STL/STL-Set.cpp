#include <iostream>
#include <set>
#include <string>

// 임의 타입 T에 대해 std::set<T> 내부 원소들을 출력하는 함수
template <typename T>
void print_set(const std::set<T>& s) {
    // 컨테이너 내 모든 원소를 순회하며 출력
    for (const auto& elem : s) {
        std::cout << elem << std::endl;  // ostream 연산자<<가 오버로드 되어 있어야 함
    }
}

// 할 일 목록을 표현하는 클래스
class Todo {
    int priority;         // 중요도 (숫자가 클수록 우선순위가 높음)
    std::string job_desc; // 할 일 내용

public:
    // 생성자: 우선순위와 할 일 설명을 받음
    Todo(int priority, std::string job_desc) : priority(priority), job_desc(std::move(job_desc)) {}

    // 정렬을 위한 비교 연산자 오버로드
    bool operator<(const Todo& t) const {
        if (priority == t.priority)
            return job_desc < t.job_desc;           // 중요도가 같으면 문자열 사전순 비교
        return priority > t.priority;                // 중요도가 큰 것이 더 우선(앞)에 위치
    }

    // 출력 연산자 오버로드를 위해 friend 선언
    friend std::ostream& operator<<(std::ostream& o, const Todo& td);
};

// Todo 객체를 출력할 때 호출되는 함수
std::ostream& operator<<(std::ostream& o, const Todo& td) {
    o << "[중요도 " << td.priority << "] " << td.job_desc;
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
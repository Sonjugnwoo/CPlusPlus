#include <iostream>
#include <string>

// 직원 클래스
class Employee {
protected:
	std::string name;      // 이름
	int age;               // 나이
	std::string position;  // 직급
	int rank;              // 직급 등급(정수)

public:
	// 일반 생성자
	Employee(std::string name, int age, std::string position, int rank)
		: name(name), age(age), position(position), rank(rank) {}

	// 복사 생성자
	Employee(const Employee& employee) {
		name = employee.name;
		age = employee.age;
		position = employee.position;
		rank = employee.rank;
	}

	// 디폴트 생성자
	Employee() {}

	// 직원 정보 출력
	void PrintInfo() {
		std::cout << name << "(" << position << "," << age << ") ==>" << CalculatePay() << "만원" << std::endl;
	}

	// 급여 계산 (기본: 200 + 등급*50)
	int CalculatePay() { return 200 + rank * 50; }
};


// 매니저 클래스 (직원 클래스 상속)
class Manager : public Employee {
	int year_service; // 근속 연수

public:
	// 일반 생성자
	Manager(std::string name, int age, std::string position, int rank, int year_service)
		: Employee(name, age, position, rank), year_service(year_service) {}

	// 복사 생성자
	Manager(const Manager& manager)
		: Employee(manager.name, manager.age, manager.position, manager.rank) {
		year_service = manager.year_service;
	}

	// 디폴트 생성자
	Manager() : Employee() {}

	// 매니저 급여 계산 (연차에 따라 추가)
	int CalculatePay() { return 200 + rank * 50 + 5 * year_service; }

	// 매니저 정보 출력 (연차도 함께 출력)
	void PrintInfo() {
		std::cout << name << "(" << position << "," << age << "," << year_service << "년차"
			<< ") ==>" << CalculatePay() << "만원" << std::endl;
	}
};
// 직원/매니저 리스트 관리 클래스
class EmployeeList {
	int alloc_employee;      // 배열로 할당한 최대 인원 수
	int current_employee;    // 현재 직원 수
	int current_manager;     // 현재 매니저 수

	Employee** employee_list; // 직원 포인터 배열
	Manager** manager_list;   // 매니저 포인터 배열

public:
	// 리스트 생성자 (최대 인원 수 할당)
	EmployeeList(int alloc_employee) : alloc_employee(alloc_employee) {
		employee_list = new Employee * [alloc_employee];
		manager_list = new Manager * [alloc_employee];
		current_employee = 0;
		current_manager = 0;
	}

	// 직원 추가
	void AddEmployee(Employee* employee) {
		// 배열 크기를 넘지 않을 때만 추가
		if (current_employee < alloc_employee)
			employee_list[current_employee++] = employee;
	}

	// 매니저 추가
	void AddManager(Manager* manager) {
		// 배열 크기를 넘지 않을 때만 추가
		if (current_manager < alloc_employee)
			manager_list[current_manager++] = manager;
	}

	// 전체 인원 수 반환
	int TotalEmployee() { return current_employee + current_manager; }

	// 전체 직원/매니저 정보 및 총 급여 출력
	void PrintInfo() {
		int total_pay = 0;
		// 직원 정보 출력 및 급여 합산
		for (int i = 0; i < current_employee; i++) {
			employee_list[i]->PrintInfo();
			total_pay += employee_list[i]->CalculatePay();
		}
		// 매니저 정보 출력 및 급여 합산
		for (int i = 0; i < current_manager; i++) {
			manager_list[i]->PrintInfo();
			total_pay += manager_list[i]->CalculatePay();
		}
		std::cout << "총 비용:" << total_pay << "만원" << std::endl;
	}

	// 소멸자: 동적 할당된 메모리 해제
	~EmployeeList() {
		// 직원 객체 해제
		for (int i = 0; i < current_employee; i++)
			delete employee_list[i];
		// 매니저 객체 해제
		for (int i = 0; i < current_manager; i++)
			delete manager_list[i];
		// 배열 자체 해제
		delete[] employee_list;
		delete[] manager_list;
	}
};

int main() {
	// 총 7명을 저장할 수 있도록 리스트 생성
	EmployeeList list(7);

	// 사원 4명 추가
	list.AddEmployee(new Employee("홍길동", 28, "사원", 1));
	list.AddEmployee(new Employee("김철수", 31, "대리", 2));
	list.AddEmployee(new Employee("이영희", 26, "사원", 1));
	list.AddEmployee(new Employee("박민수", 35, "과장", 3));

	// 매니저 3명 추가
	list.AddManager(new Manager("최강민", 45, "부장", 4, 15));
	list.AddManager(new Manager("장서연", 50, "이사", 5, 20));
	list.AddManager(new Manager("오지훈", 38, "팀장", 3, 10));

	// 전체 정보 출력
	list.PrintInfo();

	// EmployeeList 소멸자에서 메모리 정리됨
	return 0;
}
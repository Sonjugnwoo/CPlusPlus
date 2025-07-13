#include <iostream>
#include <string>

// ���� Ŭ����
class Employee {
protected:
	std::string name;      // �̸�
	int age;               // ����
	std::string position;  // ����
	int rank;              // ���� ���(����)

public:
	// �Ϲ� ������
	Employee(std::string name, int age, std::string position, int rank)
		: name(name), age(age), position(position), rank(rank) {}

	// ���� ������
	Employee(const Employee& employee) {
		name = employee.name;
		age = employee.age;
		position = employee.position;
		rank = employee.rank;
	}

	// ����Ʈ ������
	Employee() {}

	//virtual: �θ� Ŭ�������� "�� �Լ��� �ڽ� Ŭ�������� ������(�������̵�)�� �� �ְ�, �����ͷ� ȣ���� �� ���� ��ü Ÿ�Կ� �´� �Լ��� ����

	// ���� ���� ���
	virtual void PrintInfo() {
		std::cout << name << "(" << position << "," << age << ") ==>" << CalculatePay() << "����" << std::endl;
	}

	// �޿� ��� (�⺻: 200 + ���*50)
	virtual int CalculatePay() { return 200 + rank * 50; }
};


// �Ŵ��� Ŭ���� (���� Ŭ���� ���)
class Manager : public Employee {
	int year_service; // �ټ� ����

public:
	// �Ϲ� ������
	Manager(std::string name, int age, std::string position, int rank, int year_service)
		: Employee(name, age, position, rank), year_service(year_service) {}

	//override: �ڽ� Ŭ�������� "�� �Լ��� �θ��� virtual �Լ��� ��Ȯ�� ������(�������̵�)�� ��

	// �Ŵ��� �޿� ��� (������ ���� �߰�)
	int CalculatePay() override { return 200 + rank * 50 + 5 * year_service; }

	// �Ŵ��� ���� ��� (������ �Բ� ���)
	void PrintInfo() override {
		std::cout << name << "(" << position << "," << age << "," << year_service << "����"
			<< ") ==>" << CalculatePay() << "����" << std::endl;
	}
};
// ����/�Ŵ��� ����Ʈ ���� Ŭ����
class EmployeeList {
	int alloc_employee;      // �迭�� �Ҵ��� �ִ� �ο� ��
	int current_employee;    // ���� ���� ��

	Employee** employee_list; // ���� ������ �迭

public:
	// ����Ʈ ������ (�ִ� �ο� �� �Ҵ�)
	EmployeeList(int alloc_employee) : alloc_employee(alloc_employee) {
		employee_list = new Employee * [alloc_employee];
		current_employee = 0;
	}

	// ���� �߰�
	void AddEmployee(Employee* employee) {
		// �迭 ũ�⸦ ���� ���� ���� �߰�
		if (current_employee < alloc_employee)
			employee_list[current_employee++] = employee;
	}



	// ��ü �ο� �� ��ȯ
	int TotalEmployee() { return current_employee ; }

	// ��ü ����/�Ŵ��� ���� �� �� �޿� ���
	void PrintInfo() {
		int total_pay = 0;
		// ���� ���� ��� �� �޿� �ջ�
		for (int i = 0; i < current_employee; i++) {
			employee_list[i]->PrintInfo();
			total_pay += employee_list[i]->CalculatePay();
		}

		std::cout << "�� ���:" << total_pay << "����" << std::endl;
	}

	// �Ҹ���: ���� �Ҵ�� �޸� ����
	~EmployeeList() {
		// ���� ��ü ����
		for (int i = 0; i < current_employee; i++)
			delete employee_list[i];

		// �迭 ��ü ����
		delete[] employee_list;
	}
};

int main() {
	// �� 7���� ������ �� �ֵ��� ����Ʈ ����
	EmployeeList list(7);

	// ��� 4�� �߰�
	list.AddEmployee(new Employee("ȫ�浿", 28, "���", 1));
	list.AddEmployee(new Employee("��ö��", 31, "�븮", 2));
	list.AddEmployee(new Employee("�̿���", 26, "���", 1));
	list.AddEmployee(new Employee("�ڹμ�", 35, "����", 3));

	// �Ŵ��� 3�� �߰�
	list.AddEmployee(new Manager("�ְ���", 45, "����", 4, 15));
	list.AddEmployee(new Manager("�弭��", 50, "�̻�", 5, 20));
	list.AddEmployee(new Manager("������", 38, "����", 3, 10));

	// ��ü ���� ���
	list.PrintInfo();

	// EmployeeList �Ҹ��ڿ��� �޸� ������
	return 0;
}
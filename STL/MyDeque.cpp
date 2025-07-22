#include <iostream>

template <typename T>
class Deque {
	int capacity;  // ������� �� �뷮
	int size;      // ���� ����� ���� ����
	int front;     // ���� ù ��° ���� �ε���
	int rear;      // ���� ������ ���� �ٷ� ���� �ε���
	T* dq;         // ���� �迭 ������

public:
	// �⺻ ������ (�ʱ� �뷮 1)
	Deque() : dq(new T[1]), capacity(1), size(0), front(0), rear(0) {}

	// �ʱ� �뷮 ���� ������ (0 ���� �Է� �� 1�� ����)
	Deque(int value)
		: dq(new T[value]), capacity(value > 0 ? value : 1), size(0), front(0), rear(0) {}

	// ���� ������ (other ���� ���� ����)
	Deque(const Deque& other) {
		capacity = other.capacity;
		size = other.size;
		front = 0;        // �� �迭���� ������ 0
		rear = size;      // rear�� size ��ġ

		dq = new T[capacity];
		// other ���� ���Ҹ� ������� ���� (���� ���� �ε��� ���)
		for (int i = 0; i < size; i++) {
			dq[i] = other.dq[(other.front + i) % other.capacity];		//capacity �� ������ ���� > �迭 ���� �Ѿ�� �ٽ� 0 ���� ��ȸ �ϰ� �ҷ��� (����)
		}
	}

	// �Ҹ��� - ���� �޸� ����
	~Deque() {
		delete[] dq;
	}
	// ���� ������
	Deque& operator=(const Deque& other) {
		if (this == &other) return *this; // �ڱ��ڽ� ���� ����

		delete[] dq;

		capacity = other.capacity;
		size = other.size;
		front = 0;
		rear = size;

		dq = new T[capacity];
		for (int i = 0; i < size; i++) {
			dq[i] = other.dq[(other.front + i) % other.capacity];
		}

		return *this;
	}

	// �ε��� ������ (front���� i��° ���� ��ȯ)
	const T& operator[](int i) {
		return dq[(front + i) % capacity];
	}

	// �ڿ� ���� �߰�
	void push_back(const T& value) {
		// ���� ũ�Ⱑ �뷮�� ������ �뷮 2�� Ȯ��
		if (capacity <= size) {
			T* temp = new T[capacity * 2];

			// ���� ���Ҹ� ������� �� �迭�� ����
			for (int i = 0; i < size; ++i) {
				temp[i] = dq[(front + i) % capacity];
			}

			delete[] dq;
			dq = temp;
			capacity *= 2;

			// �ε��� �缳��: �� �迭�� 0���� ����
			front = 0;
			rear = size;
		}

		// �� ���Ҹ� rear ��ġ�� �����ϰ� rear ����
		dq[rear] = value;
		rear = (rear + 1) % capacity;
		++size;
	}

	// �տ� ���� �߰�
	void push_front(const T& value) {
		// �뷮 ���� �� 2�� Ȯ�� �� ����
		if (capacity <= size) {
			T* temp = new T[capacity * 2];

			for (int i = 0; i < size; ++i) {
				temp[i] = dq[(front + i) % capacity];
			}

			delete[] dq;
			dq = temp;
			capacity *= 2;

			front = 0;
			rear = size;
		}

		// front �ε����� �� ĭ �ڷ� �̵���Ű�� �� �ֱ�
		front = (front - 1 + capacity) % capacity;
		dq[front] = value;
		++size;
	}

	// �� ���� ����
	void pop_front() {
		if (size == 0) return;    // �� ��������� ����

		front = (front + 1) % capacity;
		--size;
	}

	// �� ���� ����
	void pop_back() {
		if (size == 0) return;

		rear = (rear - 1 + capacity) % capacity;
		--size;
	}

	// �� ���� Ȯ��
	T peek_front() const {
		if (empty())
			throw std::out_of_range("Deque is empty");
		return dq[front];
	}

	// �� ���� Ȯ��
	T peek_back() const {
		if (empty())
			throw std::out_of_range("Deque is empty");
		return dq[(rear - 1 + capacity) % capacity];
	}

	// ���� ������� Ȯ��
	bool empty() const { return size == 0; }

	// ���� ���� á���� Ȯ��
	bool full() const { return size == capacity; }

	// �� ���Ҹ� ������� ���
	void print_dq() {
		int i = front;
		while (i != rear) {
			std::cout << dq[i] << " ";
			i = (i + 1) % capacity;
		}
		std::cout << std::endl;
	}

	// ���� ���� ��ȯ
	int Size() const { return size; }

	// ��� ���� ����, ���� �ʱ�ȭ
	void clear() {
		size = 0;
		front = 0;
		rear = 0;
	}
};

int main() {
	Deque<int> d;

	// 1. ������� Ȯ��
	std::cout << "Empty? " << (d.empty() ? "Yes" : "No") << std::endl;

	// 2. push_back �׽�Ʈ
	d.push_back(10);
	d.push_back(20);
	d.push_back(30);
	std::cout << "After push_back 10,20,30 : ";
	d.print_dq();

	// 3. push_front �׽�Ʈ
	d.push_front(5);
	d.push_front(3);
	std::cout << "After push_front 5,3: ";
	d.print_dq();

	// 4. peek_front, peek_back �׽�Ʈ
	std::cout << "Front element: " << d.peek_front() << std::endl;
	std::cout << "Back element: " << d.peek_back() << std::endl;

	// 5. pop_front �׽�Ʈ
	d.pop_front();
	std::cout << "After pop_front: ";
	d.print_dq();

	// 6. pop_back �׽�Ʈ
	d.pop_back();
	std::cout << "After pop_back: ";
	d.print_dq();

	// 7. operator[] �׽�Ʈ
	std::cout << "Elements by operator[]: ";
	for (int i = 0; i < d.Size(); ++i) {
		std::cout << d[i] << " ";
	}
	std::cout << std::endl;

	// 8. clear �׽�Ʈ
	d.clear();
	std::cout << "After clear, empty? " << (d.empty() ? "Yes" : "No") << std::endl;

	// 9. check pushing after clear
	d.push_back(100);
	d.push_front(50);
	std::cout << "After push_back 100, push_front 50: ";
	d.print_dq();

	return 0;
}
#include <iostream>

template <typename T>
class Deque {
	int capacity;  // 저장공간 총 용량
	int size;      // 현재 저장된 원소 개수
	int front;     // 덱의 첫 번째 원소 인덱스
	int rear;      // 덱의 마지막 원소 바로 다음 인덱스
	T* dq;         // 동적 배열 포인터

public:
	// 기본 생성자 (초기 용량 1)
	Deque() : dq(new T[1]), capacity(1), size(0), front(0), rear(0) {}

	// 초기 용량 지정 생성자 (0 이하 입력 시 1로 설정)
	Deque(int value)
		: dq(new T[value]), capacity(value > 0 ? value : 1), size(0), front(0), rear(0) {}

	// 복사 생성자 (other 덱의 원소 복사)
	Deque(const Deque& other) {
		capacity = other.capacity;
		size = other.size;
		front = 0;        // 새 배열에서 시작은 0
		rear = size;      // rear는 size 위치

		dq = new T[capacity];
		// other 덱의 원소를 순서대로 복사 (원형 버퍼 인덱스 고려)
		for (int i = 0; i < size; i++) {
			dq[i] = other.dq[(other.front + i) % other.capacity];		//capacity 로 나누는 이유 > 배열 끝을 넘어가면 다시 0 부터 순회 하게 할려고 (원형)
		}
	}

	// 소멸자 - 동적 메모리 해제
	~Deque() {
		delete[] dq;
	}
	// 대입 연산자
	Deque& operator=(const Deque& other) {
		if (this == &other) return *this; // 자기자신 대입 방지

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

	// 인덱스 연산자 (front부터 i번째 원소 반환)
	const T& operator[](int i) {
		return dq[(front + i) % capacity];
	}

	// 뒤에 원소 추가
	void push_back(const T& value) {
		// 현재 크기가 용량과 같으면 용량 2배 확장
		if (capacity <= size) {
			T* temp = new T[capacity * 2];

			// 기존 원소를 순서대로 새 배열에 복사
			for (int i = 0; i < size; ++i) {
				temp[i] = dq[(front + i) % capacity];
			}

			delete[] dq;
			dq = temp;
			capacity *= 2;

			// 인덱스 재설정: 새 배열은 0부터 시작
			front = 0;
			rear = size;
		}

		// 새 원소를 rear 위치에 저장하고 rear 갱신
		dq[rear] = value;
		rear = (rear + 1) % capacity;
		++size;
	}

	// 앞에 원소 추가
	void push_front(const T& value) {
		// 용량 부족 시 2배 확장 및 복사
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

		// front 인덱스를 한 칸 뒤로 이동시키고 값 넣기
		front = (front - 1 + capacity) % capacity;
		dq[front] = value;
		++size;
	}

	// 앞 원소 제거
	void pop_front() {
		if (size == 0) return;    // 덱 비어있으면 무시

		front = (front + 1) % capacity;
		--size;
	}

	// 뒤 원소 제거
	void pop_back() {
		if (size == 0) return;

		rear = (rear - 1 + capacity) % capacity;
		--size;
	}

	// 앞 원소 확인
	T peek_front() const {
		if (empty())
			throw std::out_of_range("Deque is empty");
		return dq[front];
	}

	// 뒤 원소 확인
	T peek_back() const {
		if (empty())
			throw std::out_of_range("Deque is empty");
		return dq[(rear - 1 + capacity) % capacity];
	}

	// 덱이 비었는지 확인
	bool empty() const { return size == 0; }

	// 덱이 가득 찼는지 확인
	bool full() const { return size == capacity; }

	// 덱 원소를 순서대로 출력
	void print_dq() {
		int i = front;
		while (i != rear) {
			std::cout << dq[i] << " ";
			i = (i + 1) % capacity;
		}
		std::cout << std::endl;
	}

	// 원소 개수 반환
	int Size() const { return size; }

	// 모든 원소 제거, 상태 초기화
	void clear() {
		size = 0;
		front = 0;
		rear = 0;
	}
};

int main() {
	Deque<int> d;

	// 1. 비어있음 확인
	std::cout << "Empty? " << (d.empty() ? "Yes" : "No") << std::endl;

	// 2. push_back 테스트
	d.push_back(10);
	d.push_back(20);
	d.push_back(30);
	std::cout << "After push_back 10,20,30 : ";
	d.print_dq();

	// 3. push_front 테스트
	d.push_front(5);
	d.push_front(3);
	std::cout << "After push_front 5,3: ";
	d.print_dq();

	// 4. peek_front, peek_back 테스트
	std::cout << "Front element: " << d.peek_front() << std::endl;
	std::cout << "Back element: " << d.peek_back() << std::endl;

	// 5. pop_front 테스트
	d.pop_front();
	std::cout << "After pop_front: ";
	d.print_dq();

	// 6. pop_back 테스트
	d.pop_back();
	std::cout << "After pop_back: ";
	d.print_dq();

	// 7. operator[] 테스트
	std::cout << "Elements by operator[]: ";
	for (int i = 0; i < d.Size(); ++i) {
		std::cout << d[i] << " ";
	}
	std::cout << std::endl;

	// 8. clear 테스트
	d.clear();
	std::cout << "After clear, empty? " << (d.empty() ? "Yes" : "No") << std::endl;

	// 9. check pushing after clear
	d.push_back(100);
	d.push_front(50);
	std::cout << "After push_back 100, push_front 50: ";
	d.print_dq();

	return 0;
}
//Memory_order_seq_cst �޸� ����� ������ �ϰ����� ���� ���� CPU�� �۵��ϴ� ���

#include <atomic>
#include <iostream>
#include <thread>

// ������ ���� ����: ���� �����尡 ���ÿ� �����ص� �����ϰ� ������
std::atomic<bool> x(false);   
std::atomic<bool> y(false); 
std::atomic<int> z(0);      

std::atomic<bool> a(false);
std::atomic<bool> b(false);
std::atomic<int> c(0);

// x�� true�� �����ϴ� �Լ� (release �޸� ������ ����ȭ ����)
void write_x() {
	x.store(true, std::memory_order_release);
}

// y�� true�� �����ϴ� �Լ� (release �޸� ������ ����ȭ ����)
void write_y() {
	y.store(true, std::memory_order_release);
}

// x�� true�� �� ������ �ݺ��ؼ� üũ, x�� true�� �ٲ�� z�� ����
void read_x_then_y() {
	while (!x.load(std::memory_order_acquire)) {}        // x�� false�� �ݺ�

		if (x.load(std::memory_order_acquire))          // �߰��� x�� true�� �ٲ��
			++z;                                        // z �� ����
	
}

// y�� true�� �� ������ �ݺ��ؼ� üũ, y�� true�� �ٲ�� z�� ����
void read_y_then_x() {
	while (!y.load(std::memory_order_acquire)) {}        // y�� false�� �ݺ�

		if (y.load(std::memory_order_acquire))          // �߰��� y�� true�� �ٲ��
			++z;                                        // z �� ����
	
}

/*------------------------------------------------------------------*/

// a�� true�� �����ϴ� �Լ�, ������ �ϰ���(Sequential Consistency)�� �����Ͽ� ��� �����尡 ������ ������ �� ������ ����
void write_a() {
	a.store(true, std::memory_order_seq_cst);
}

// b�� true�� �����ϴ� �Լ�, ������ �ϰ���(Sequential Consistency)�� �����Ͽ� ��� �����尡 ������ ������ �� ������ ����
void write_b() {
	b.store(true, std::memory_order_seq_cst);
}

// a�� true�� �� ������ �ݺ��ؼ� üũ
// �ݺ��� ���ο��� a.load()�� memory_order_seq_cst�� �������ν�,
// ��� �����尡 ������ ������ ���� ������ �� �ְ� ��
void read_a_then_b() {
	while (!a.load(std::memory_order_seq_cst)) {}       // a �� false�� �ݺ�

		if (a.load(std::memory_order_seq_cst))          // a �� true ���� ��Ȯ��
			++c;                                        // c �� ����
	
}

// ���� ������ read_a_then_b()�� ����
void read_b_then_a() {
	while (!b.load(std::memory_order_seq_cst)) {}       // b �� false�� �ݺ�

		if (b.load(std::memory_order_seq_cst))          // b �� true ���� ��Ȯ��
			++c;                                        // c �� ����
	
}


int main() {
	//x, y, z �׷�	release/acquire	����ȭ�� ��, ������ ���� ��Ȯ��. z�� 0,1,2 �� ��ȭ ����
	std::thread x1(write_x);
	std::thread y1(write_y);
	std::thread x2(read_x_then_y);
	std::thread y2(read_y_then_x);

	x1.join();
	y1.join();
	x2.join();
	y2.join();

	std::cout << "z : " << z << std::endl;  

	std::cout << "---------------"<< std::endl;

	//a, b, c �׷�	sequential consistency	������ ���� ����, c�� ���� 2�� ��, �ϰ��� ����
	std::thread a1(write_a);
	std::thread b1(write_b);
	std::thread a2(read_a_then_b);
	std::thread b2(read_b_then_a);

	a1.join();
	b1.join();
	a2.join();
	b2.join();

	std::cout << "c : " << c << std::endl;
}
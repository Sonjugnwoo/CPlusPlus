//Memory_order_seq_cst 메모리 명령의 순차적 일관성을 보장 해줌 CPU가 작동하는 방식

#include <atomic>
#include <iostream>
#include <thread>

// 원자적 변수 선언: 여러 스레드가 동시에 접근해도 안전하게 동작함
std::atomic<bool> x(false);   
std::atomic<bool> y(false); 
std::atomic<int> z(0);      

std::atomic<bool> a(false);
std::atomic<bool> b(false);
std::atomic<int> c(0);

// x를 true로 설정하는 함수 (release 메모리 순서로 동기화 보장)
void write_x() {
	x.store(true, std::memory_order_release);
}

// y를 true로 설정하는 함수 (release 메모리 순서로 동기화 보장)
void write_y() {
	y.store(true, std::memory_order_release);
}

// x가 true가 될 때까지 반복해서 체크, x가 true로 바뀌면 z를 증가
void read_x_then_y() {
	while (!x.load(std::memory_order_acquire)) {}        // x가 false면 반복

		if (x.load(std::memory_order_acquire))          // 중간에 x가 true로 바뀌면
			++z;                                        // z 값 증가
	
}

// y가 true가 될 때까지 반복해서 체크, y가 true로 바뀌면 z를 증가
void read_y_then_x() {
	while (!y.load(std::memory_order_acquire)) {}        // y가 false면 반복

		if (y.load(std::memory_order_acquire))          // 중간에 y가 true로 바뀌면
			++z;                                        // z 값 증가
	
}

/*------------------------------------------------------------------*/

// a를 true로 설정하는 함수, 순차적 일관성(Sequential Consistency)을 보장하여 모든 스레드가 동일한 순서로 이 변경을 관찰
void write_a() {
	a.store(true, std::memory_order_seq_cst);
}

// b를 true로 설정하는 함수, 순차적 일관성(Sequential Consistency)을 보장하여 모든 스레드가 동일한 순서로 이 변경을 관찰
void write_b() {
	b.store(true, std::memory_order_seq_cst);
}

// a가 true가 될 때까지 반복해서 체크
// 반복문 내부에서 a.load()를 memory_order_seq_cst로 읽음으로써,
// 모든 스레드가 동일한 순서로 값을 관찰할 수 있게 함
void read_a_then_b() {
	while (!a.load(std::memory_order_seq_cst)) {}       // a 가 false면 반복

		if (a.load(std::memory_order_seq_cst))          // a 가 true 인지 재확인
			++c;                                        // c 값 증가
	
}

// 동작 원리는 read_a_then_b()와 동일
void read_b_then_a() {
	while (!b.load(std::memory_order_seq_cst)) {}       // b 가 false면 반복

		if (b.load(std::memory_order_seq_cst))          // b 가 true 인지 재확인
			++c;                                        // c 값 증가
	
}


int main() {
	//x, y, z 그룹	release/acquire	동기화는 됨, 하지만 순서 불확실. z가 0,1,2 중 변화 가능
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

	//a, b, c 그룹	sequential consistency	엄격한 순서 보장, c가 보통 2가 됨, 일관성 높음
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
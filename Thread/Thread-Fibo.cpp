#include <iostream>
#include <thread>
#include <vector>

using std::thread;
using std::vector;

// 피보나치 수열을 계산하는 함수
int Fibo(int n, int depth = 0) {		// depth: 병렬화 깊이 제한을 위한 파라미터 (재귀 호출 깊이 체크)
	if (n <= 1) return n;			    // 베이스 케이스: n이 0 또는 1이면 그 값을 그대로 반환
	
	if (depth > 2)	 // 병렬화를 깊이 2까지만 허용하고, 그 이후에는 단일 쓰레드 재귀 호출로 처리
		return Fibo(n - 1, depth + 1) + Fibo(n - 2, depth + 1);

	int x, y;
	// 쓰레드를 하나 생성하여 fib(n-1)을 병렬 계산
	// 람다 함수로 호출, 캡처 리스트에 x를 포함해 저장
	thread t1([&]() {x = Fibo(n - 1, depth + 1); });

	y = Fibo(n - 2, depth + 1);	//메인 쓰레드에서는 fib(n-2)를 계산

	t1.join();	   // 병렬 쓰레드가 끝날 때까지 대기(동기화)

	return x + y;
}


int main() {
	int size = 20;
	std::cout << "fib(" << size << ") = " << Fibo(size) << std::endl;
}
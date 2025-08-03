//프로세스 -> 운영체제에서 실행되는 프로그램의 최소 단위 
//쓰레드 -> CPU코어에서 돌아가는 프로그램 단위 

/*
					join()						detach()
역할	쓰레드 종료를 기다림			쓰레드를 메인 쓰레드와 분리하여 독립 실행
장점	안전하게 쓰레드 종료 보장		메인 쓰레드 블로킹 없이 계속 진행
단점	메인 쓰레드가 대기해야 함		쓰레드가 작업 중 종료될 수 있음
사용법	반드시 호출해서 쓰레드 정리		호출 후 쓰레드 소유권 반환
*/

#include <iostream>
#include <thread>

void func1() {
	for (int i = 0; i < 10; i++)
		std::cout << "쓰레드 1 작동 중 \n";
}
void func2() {
	for (int i = 0; i < 10; i++)
		std::cout << "쓰레드 2 작동 중 \n";
}
void func3() {
	for (int i = 0; i < 10; i++)
		std::cout << "쓰레드 3 작동 중 \n";
}

int main() {
	// t1, t2, t3 쓰레드 생성 후 join()
	std::thread t1(func1);
	std::thread t2(func2);
	std::thread t3(func3);

	//join  ->  메인 쓰레드가 해당 쓰레드가 종료할 때까지 기다림
	t1.join();
	t2.join();
	t3.join();

	std::cout << "-----------------\n";
	//d1, d2, d3 쓰레드 생성 후 detach()
	std::thread d1(func1);
	std::thread d2(func2);
	std::thread d3(func3);

	//detach  -> 해당 쓰레드를 메인 쓰레드와 분리시켜 독립적으로 실행
	d1.detach();
	d2.detach();
	d3.detach();

	std::cout << "메인함수 종료 \n";
}

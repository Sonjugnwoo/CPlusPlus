#include <iostream>

// foo 함수는 noexcept로 선언되어 예외를 던지지 않는다고 컴파일러에 보장함
int foo() noexcept {
    return 0;  // 반환 타입 int에 맞게 0을 반환함
}

// bar 함수는 noexcept가 없으므로 예외를 자유롭게 던질 수 있음
int bar() {
    throw 1;  // 정수형 예외(1)를 던짐
    return 0; // 도달하지 않는 코드
}

int main() {
    foo();  // noexcept 함수 호출, 예외 발생 없음

    try {
        bar();  // bar 함수 호출, 예외 발생
    }
    catch (int x) {
        // bar 함수에서 던진 int 예외를 잡아서 출력
        std::cout << "Error :" << x << std::endl;
    }
}
//동기적 실행: 호출한 쪽이 끝날 때까지 기다린 후 다음 작업 진행  

#include <string>
#include <thread>
#include <iostream>

// 스레드에서 실행할 함수
void text_read(std::string* result) {
    std::string txt = "읽은 데이터"; // 가상의 읽기 작업
    *result = txt;                  // 읽은 데이터를 호출 측 문자열에 대입
}

int main() {
    std::string result;

    // 새로운 스레드 t 실행 
    std::thread t(text_read, &result);

    // ===== 동기적 실행 포인트 =====
    // join() 호출 → t 스레드가 종료될 때까지 메인 스레드가 대기
    // 즉, text_read가 끝나야 아래 코드가 실행됨
    t.join();

    // 스레드가 종료된 이후 실행
    std::cout << "result: " << result << std::endl;
}
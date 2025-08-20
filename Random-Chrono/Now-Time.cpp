#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

int main() {
    auto now = std::chrono::system_clock::now();          // 현재 시간(시스템 클록 기준)을 구함
    std::time_t t = std::chrono::system_clock::to_time_t(now); // time_t 타입으로 변환

    // std::put_time을 사용해 로컬 시간으로 포맷팅 후 출력
    // "%F" -> YYYY-MM-DD, "%T" -> HH:MM:SS, "%z" -> 시간대 오프셋
    std::cout << "현재 시간 : " << std::put_time(std::localtime(&t), "%F %T %z") << std::endl;
}
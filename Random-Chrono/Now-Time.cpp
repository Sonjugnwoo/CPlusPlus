#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

int main() {
    auto now = std::chrono::system_clock::now();          // ���� �ð�(�ý��� Ŭ�� ����)�� ����
    std::time_t t = std::chrono::system_clock::to_time_t(now); // time_t Ÿ������ ��ȯ

    // std::put_time�� ����� ���� �ð����� ������ �� ���
    // "%F" -> YYYY-MM-DD, "%T" -> HH:MM:SS, "%z" -> �ð��� ������
    std::cout << "���� �ð� : " << std::put_time(std::localtime(&t), "%F %T %z") << std::endl;
}
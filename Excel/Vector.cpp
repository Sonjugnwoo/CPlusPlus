#include "vector.h"

namespace Excel {
    // 생성자: capacity 크기의 문자열 배열을 동적 할당, 초기 길이는 0
    Vector::Vector(int n) : data(new std::string[n]), capacity(n), length(0) {}

    // push_back: 배열 끝에 문자열 추가, 공간 부족 시 2배로 확장
    void Vector::push_back(std::string str) {
        if (capacity <= length) {
            // 새 배열 할당 (용량 2배)
            std::string* temp = new std::string[capacity * 2];
            // 기존 데이터 복사
            for (int i = 0; i < length; i++)
                temp[i] = data[i];
            // 기존 배열 해제
            delete[] data;
            // 새 배열로 교체
            data = temp;
            capacity *= 2;
        }
        // 새 데이터 추가
        data[length] = str;
        length++;
    }

    // operator[]: i번째 원소 반환 (읽기/쓰기 가능)
    std::string Vector::operator[](int i) {
        return data[i];
    }

    // remove: x번째 원소 삭제, 뒤의 데이터 한 칸씩 앞으로 당김
    void Vector::remove(int x) {
        for (int i = x + 1; i < length; i++)
            data[i - 1] = data[i];
        length--;
    }

    // size: 현재 저장된 원소 개수 반환
    int Vector::size() {
        return length;
    }

    // 소멸자: 동적 할당된 배열 해제
    Vector::~Vector() {
        if (data)
            delete[] data;
    }
}
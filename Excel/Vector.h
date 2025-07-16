#ifndef EXCEL_VECTOR_H
#define EXCEL_VECTOR_H

#include <string>

namespace Excel {

    class Vector {
        std::string* data;   // 동적 문자열 배열의 시작 주소
        int capacity;        // 현재 할당된 배열의 크기(최대 저장 가능 개수)
        int length;          // 실제 저장된 원소 개수
     
    public:
        // 생성자: n개의 공간을 가진 동적 배열 생성 (기본값 1)
        Vector(int n = 1);

        // 맨 뒤에 새로운 원소 추가 (필요시 배열 크기 2배로 확장)
        void push_back(std::string str);

        // 임의의 위치의 원소 접근 (읽기/쓰기 가능)
        std::string operator[](int i);

        // x번째 위치한 원소 제거 (뒤의 원소들을 한 칸씩 앞으로 이동)
        void remove(int x);

        // 현재 벡터에 저장된 원소 개수 반환
        int size();

        // 소멸자: 동적 배열 메모리 해제
        ~Vector();
    };
}

#endif
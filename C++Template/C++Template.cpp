#include <iostream>
#include <string>

template <typename T>
class Vector {
    T* data;      // 실제 데이터를 담을 배열 포인터
    int capacity; // 현재 할당된 배열 크기(용량)
    int length;   // 현재 저장된 원소 개수

public:
	Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}         // 생성자: 크기 n(기본값 1)만큼 동적 배열 할당

 // 원소 추가 함수
    void push_back(T s) {
        if (capacity <= length) { // 공간이 부족하면
            T* temp = new T[capacity * 2];           // 더 큰 새 배열 할당
            for (int i = 0; i < length; i++)
                temp[i] = data[i];                   // 기존 데이터 복사

            delete[] data;                           // 기존 배열 메모리 해제
            data = temp;                             // 새 배열로 교체
            capacity *= 2;                           // 용량 2배로 증가
        }
        data[length] = s;    // 끝에 값 저장
        length++;            // 원소 개수 증가
    }

    // 인덱스를 통한 값 조회 (값을 복사해서 반환)
    T operator[](int i) { return data[i]; }

    // x번째 원소 삭제 (뒤에 있는 값들을 한 칸 당김)
    void remove(int x) {
        for (int i = x + 1; i < length; i++)
            data[i - 1] = data[i];
        length--; // 원소 개수 하나 줄이기
    }

    // 현재 저장 개수 반환
    int size() { return length; }

    // 소멸자: 동적 메모리 해제
    ~Vector() {
        if (data)
            delete[] data;
    }
};


int main() {
    Vector<int> vec_int;
    Vector<std::string> vec_str;

    // 정수 벡터에 값 추가
    vec_int.push_back(1);
    vec_int.push_back(2);
    vec_int.push_back(3);

    // 문자열 벡터에 값 추가
    vec_str.push_back("hello");
    vec_str.push_back("world");

    // 값 출력
    std::cout << "vec_int의 내용: ";
    for (int i = 0; i < vec_int.size(); ++i)
        std::cout << vec_int[i] << " ";
    std::cout << std::endl;

    std::cout << "vec_str의 내용: ";
    for (int i = 0; i < vec_str.size(); ++i)
        std::cout << vec_str[i] << " ";
    std::cout << std::endl;

    // 첫 번째 원소 삭제
    vec_int.remove(0);
    vec_str.remove(0);

    // 삭제 후 출력
    std::cout << "vec_int(삭제 후): ";
    for (int i = 0; i < vec_int.size(); ++i)
        std::cout << vec_int[i] << " ";
    std::cout << std::endl;

    std::cout << "vec_str(삭제 후): ";
    for (int i = 0; i < vec_str.size(); ++i)
        std::cout << vec_str[i] << " ";
    std::cout << std::endl;

    return 0;
}
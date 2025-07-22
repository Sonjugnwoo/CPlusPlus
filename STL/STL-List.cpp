#include <iostream>
#include <list>

/*
임의 원소 접근 (인덱스) : O(n) (선형 탐색 필요)

앞/뒤 원소 추가 (push_front, push_back) : O(1)

중간 삽입/삭제 (반복자 위치 알고 있을 때) : O(1)

중간 탐색 : O(n)
*/

// 리스트의 모든 요소를 출력하는 함수
template <typename T>
void print_list(const std::list<T>& lst) {
    // 범위 기반 for문으로 리스트 요소를 하나씩 출력
    for (const auto& elem : lst)
        std::cout << elem << " ";
}

// 리스트에 값 num을 삽입하는 함수
template <typename T>
void insert_list(std::list<T>& lst, const T& num) {
    // 리스트 순회 반복자
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (*it == num) {           // 현재 원소가 num과 같으면
            lst.insert(it, num);    // 현재 위치 앞에 num 삽입
            return;                 // 삽입 완료 후 함수 종료
        }
    }
    lst.push_back(num);             // 리스트에 num이 없으면 맨 뒤에 추가
}

// 리스트에서 값 num을 찾아서 제거하는 함수
template<typename T>
void erase_list(std::list<T>& lst, const T& num) {
    // 리스트를 처음부터 끝까지 순회
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (*it == num) {           // 현재 원소가 num과 같으면
            lst.erase(it);          // 해당 위치 원소 제거
            return;                 // 제거 후 함수 종료
        }
    }
}

int main() {
    std::list<int> lst;

    lst.push_back(1);
    lst.push_back(4);
    lst.push_back(2);
    lst.push_back(7);
    lst.push_back(4);

    std::cout << "초기 리스트: [ ";
    print_list(lst);
    std::cout << "]" << std::endl;

    // insert_list 테스트
    std::cout << "insert_list(lst, 4) 호출 => 4 앞에 4 삽입" << std::endl;
    insert_list(lst, 4);
    std::cout << "[ ";
    print_list(lst);
    std::cout << "]" << std::endl;

    std::cout << "insert_list(lst, 10) 호출 => 리스트 끝에 10 추가" << std::endl;
    insert_list(lst, 10);
    std::cout << "[ ";
    print_list(lst);
    std::cout << "]" << std::endl;

    // erase_list 테스트
    std::cout << "erase_list(lst, 4) 호출 => 첫 4 삭제" << std::endl;
    erase_list(lst, 4);
    std::cout << "[ ";
    print_list(lst);
    std::cout << "]" << std::endl;

    std::cout << "erase_list(lst, 100) 호출 => 없는 값, 변화 없음" << std::endl;
    erase_list(lst, 100);
    std::cout << "[ ";
    print_list(lst);
    std::cout << "]" << std::endl;

    return 0;
}
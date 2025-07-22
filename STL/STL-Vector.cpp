#include <iostream>
#include <vector>

/*
임의 원소 접근 (index) : O(1)

끝에 원소 추가 (push_back) : 평균 O(1) (amortized)

앞에 원소 추가 (push_front) : O(n)

중간 삽입/삭제 : O(n) (뒤 원소 이동 필요)

중간 탐색 : O(n)
*/

// 일반적인 iterator 기반 for문을 이용해 벡터 원소 출력
template <typename T>
void print_vector(std::vector<T>& vec) {
	// 벡터의 시작부터 끝까지 반복자 itr로 순회
	for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end(); ++itr)
		std::cout << *itr << std::endl; // 반복자가 가리키는 원소 출력
}

// 범위 기반 for문(range-based for)을 이용해 벡터 원소 출력 (read-only)
template <typename T>
void print_vector_range_base(const std::vector<T>& vec) {
	// 벡터의 각 원소 elem에 대해 순차적으로 접근
	for (const auto& elem : vec)
		std::cout << elem << std::endl; // elem 출력
}

template <typename T>
void insert_vector(std::vector<T>& vec, const T& num) {
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		if (*it == num) {
			vec.insert(it, num);  // num이 있는 위치 "앞"에 num 삽입
			return;               // 삽입 후 함수 종료
		}
	}
	// num이 벡터에 없으면 맨 뒤에 추가
	vec.push_back(num);
}

int main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(2);
    vec.push_back(1);
    vec.push_back(6);

    std::cout << "일반적 for문" << std::endl;
    print_vector(vec);

    std::cout << "범위기반 for문" << std::endl;
    print_vector_range_base(vec);

    // insert_vector 테스트 추가
    std::cout << "insert_vector(vec, 3) 호출 (3 앞에 3 삽입)" << std::endl;
    insert_vector(vec, 3);
    print_vector_range_base(vec);

    std::cout << "insert_vector(vec, 10) 호출 (10이 없으므로 맨 뒤에 추가)" << std::endl;
    insert_vector(vec, 10);
    print_vector_range_base(vec);

    return 0;
}
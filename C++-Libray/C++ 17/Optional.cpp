#include <iostream>
#include <map>
#include <string>
#include <optional>  // std::optional 사용을 위한 헤더 파일

// 주어진 map에서 key에 해당하는 값을 찾아서 반환하는 함수
// 값이 있으면 std::optional에 담아서 반환, 없으면 std::nullopt 반환
std::optional<std::string> GetValueFromMap(const std::map<int, std::string>& m, int key) {
    // key를 이용해 map에서 항목 탐색
    auto itr = m.find(key);

    // key가 존재하면 해당 값 반환
    if (itr != m.end()) {
        return itr->second;
    }

    // key가 없으면 값을 담지 않은 optional 반환
    return std::nullopt;
}

int main() {
    // 테스트용 map 초기화
    std::map<int, std::string> data = { {1,"hi"}, {2,"hello"}, {3,"hiroo"} };

    // key=2에 해당하는 값을 찾음
    auto v = GetValueFromMap(data, 2);
    if (v) {
        // 값이 존재하면 *v로 값을 꺼내 출력
        std::cout << "map 2 -> " << *v << std::endl;
    }
    else {
        // 값이 없으면 "값 없음" 메시지 출력
        std::cout << "map 2 -> 값 없음" << std::endl;
    }

    // key=4에 해당하는 값을 찾음 (없음)
    v = GetValueFromMap(data, 4);
    if (v) {
        std::cout << "map 4 -> " << *v << std::endl;
    }
    else {
        std::cout << "map 4 -> 값 없음" << std::endl;
    }

}
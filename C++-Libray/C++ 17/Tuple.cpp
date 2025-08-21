#include <iostream>
#include <string>
#include <tuple>
#include <map>

// 학생 정보를 반환하는 함수, id에 따라 나이, 이름, 성별(bool)을 튜플로 반환
std::tuple<int, std::string, bool> GetStudent(int id) {
    if (id == 0)
        return std::make_tuple(25, "철스", true);   // id가 0이면 나이 25, 이름 "철스", 남자(true)
    else
        return std::make_tuple(26, "영시", false);  // 그 외 id면 나이 26, 이름 "영시", 여자(false)
}

int main() {
    auto student = GetStudent(0);  // 학생 정보 받아오기

    // 구조적 바인딩을 통해 튜플 값들을 변수에 분해
    auto [age, name, is_male] = student;

    // 분해한 변수들을 출력
    std::cout << "나이 :" << age << std::endl;
    std::cout << "이름 :" << name << std::endl;
    std::cout << "남자? :" << std::boolalpha << is_male << std::endl; // boolalpha로 true/false 출력

    std::cout << "--------------------------\n";

    // std::map 초기화 및 선언 (키: int, 값: string)
    std::map<int, std::string> m = { {3, "hi"}, {5, "hello"} };

    // map의 각 요소(key, value)를 구조적 바인딩으로 분해해서 출력
    for (auto& [key, val] : m)
        std::cout << "key : " << key << " value : " << val << std::endl;
}
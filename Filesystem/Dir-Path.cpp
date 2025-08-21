#include <filesystem>
#include <iostream>

// std::filesystem 네임스페이스를 fs란 이름으로 별칭
namespace fs = std::filesystem;

int main() {
    // 상대 경로 './some_file'을 fs::path 객체 p에 저장
    fs::path p("./some_file");

    // 현재 작업 디렉터리(프로그램 실행 기준 경로) 출력
    std::cout << "현재 경로 : " << fs::current_path() << std::endl;

    // p의 상대 경로(설정한 그대로, ./some_file)를 출력
    std::cout << "상대 경로 : " << p.relative_path() << std::endl;

    // p의 절대 경로(현재 경로 기준으로 변환된 경로)를 출력
    std::cout << "절대 경로 : " << fs::absolute(p) << std::endl;

    // p의 공식적인 절대 경로(실제로 존재해야 하며, 심볼릭 링크는 실제 경로로 변환됨)
    // 파일/폴더가 없으면 오류(예외) 발생!
    std::cout << "공식적인 절대 경로 : " << fs::canonical(p) << std::endl;
}
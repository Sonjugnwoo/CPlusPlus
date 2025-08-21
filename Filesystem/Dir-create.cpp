#include <filesystem>
#include <iostream>

// std::filesystem 네임스페이스를 fs로 별칭
namespace fs = std::filesystem;

int main() {
    // 상대 경로 "./some_file/test"를 나타내는 path 객체 p 생성
    fs::path p("./some_file/test");

    // 폴더 또는 파일 존재 여부 출력
    std::cout << "Dose" << p << " exist [" << std::boolalpha << fs::exists(p) << "]" << std::endl;

    // p 경로 위치에 디렉터리 생성 시도 (없으면 만듦)
    fs::create_directory(p);  //  -> 부모디렉토리가 존재 하지 않으면 오류 발생 
                              // 한번에 만들고 싶으면 fs::create_directorise(p) 사용 

    // 디렉터리 생성 후 존재 여부 재확인 출력
    std::cout << "Dose" << p << " exist [" << std::boolalpha << fs::exists(p) << "]" << std::endl;

    // p 경로가 디렉터리인지 확인하여 출력
    std::cout << "It" << p << " directory ? [" << fs::is_directory(p) << "]" << std::endl;
}
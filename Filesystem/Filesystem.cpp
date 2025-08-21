#include <filesystem>
#include <iostream>

int main() {
    // 상대 경로 "./some_file"을 path 객체 p로 생성
    std::filesystem::path p("./some_file");

    // p 경로가 실제로 존재하는지 확인
    std::cout << "Dose" << p << " exist? [" << std::boolalpha << std::filesystem::exists(p) << "]" << std::endl;

    // p 경로가 일반 파일인지(regular file) 확인
    std::cout << "Is" << p << " file? [ " << std::filesystem::is_regular_file(p) << "]" << std::endl;

    // p 경로가 디렉터리(폴더)인지 확인
    std::cout << "Is" << p << " directory? [" << std::filesystem::is_directory(p) << "]" << std::endl;

    // 현재 작업 디렉터리 경로 출력(실행되는 위치 기준)
    std::cout << "Current path: " << std::filesystem::current_path() << std::endl;
}

//일반 파일: 텍스트 파일, 이미지 파일, 바이너리 파일 등 “실제 내용이 저장된 파일”
//폴더,디렉토리: 일반 파일 아님!
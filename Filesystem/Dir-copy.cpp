#include <filesystem>
#include <iostream>

// std::filesystem 네임스페이스를 fs라는 별칭으로 사용
namespace fs = std::filesystem;
/*
skip_existing : 이미 존재하는 파일은 무시 (예외 안던지고)
overwrite_existing : 이미 존재하는 파일은 덮어 씌운다.
update_existing : 이미 존재하는 파일이 더 오래되었을 경우 덮어 씌운다.
*/
int main() {
    // 복사할 원본 파일 경로 설정
    fs::path from("./some_file/text1.txt");
    // 복사 대상 파일 경로 설정 (some_file 폴더 내 TEXT2라는 이름)
    fs::path to("./some_file/TEXT2");

    try {
        // 원본 파일이 존재하고 일반 파일인지 확인
        if (fs::exists(from) && fs::is_regular_file(from)) {

            // 파일 복사 실행, 기존 대상 파일이 있으면 덮어씀
            fs::copy(from, to, fs::copy_options::overwrite_existing);

            // 복사 성공 메시지 출력
            std::cout << "파일 복사 성공\n";
        }
        else {
            // 원본 파일이 없거나 일반 파일이 아니면 출력
            std::cout << "복사할 파일이 존재하지 않습니다.\n";
        }
    }
    // 복사 과정에서 파일 시스템 관련 예외가 발생하면 캐치하여 출력
    catch (const fs::filesystem_error& e) {
        std::cout << "복사 중 오류 발생: " << e.what() << std::endl;
    }
}
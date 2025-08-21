#include <filesystem>
#include <iostream>

// std::filesystem 네임스페이스를 fs란 이름으로 별칭
namespace fs = std::filesystem;

int main() {
    // 현재 작업 디렉터리의 "some_file" 하위 폴더를 탐색할 directory_iterator 생성
    fs::directory_iterator itr(fs::current_path() / "some_file");

    // 반복자 itr가 끝(end)까지 아닐 때까지 반복
    while (itr != fs::end(itr)) {
        // 현재 반복자가 가리키는 디렉터리 엔트리(파일 또는 폴더)에 접근
        const fs::directory_entry& entry = *itr;
        // 해당 엔트리의 전체 경로 출력
        std::cout << entry.path() << std::endl;
        // 다음 엔트리로 이동
        itr++;
    }
}
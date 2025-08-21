#include <filesystem>
#include <iostream>

// std::filesystem 네임스페이스를 fs란 이름으로 별칭
namespace fs = std::filesystem;

int main() {
    // 삭제할 대상이 있는지 반복으로 확인하기 위함
    while (true) {
        bool is_modified = false;  // 이번 순회에서 파일 삭제 여부

        // some_file 폴더 내 모든 항목 순회
        for (const auto& entry : fs::directory_iterator("./some_file")) {
            // 확장자 가져오기
            const std::string ext = entry.path().extension().string();

            // 확장자가 .txt면 삭제 시도
            if (ext == ".txt") {
                // 파일 삭제
                fs::remove(entry.path());

                // 변경됐으니 다시 탐색 루프 실행하기 위해 true 설정
                is_modified = true;
                break;  // 삭제 후 바로 루프 빠져나가 재탐색
            }
        }

        // 만약 이번 순회에서 아무것도 삭제되지 않았다면 반복 종료
        if (!is_modified)
            break;
    }
}
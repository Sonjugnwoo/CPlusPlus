#include <filesystem>
#include <iostream>

// std::filesystem ���ӽ����̽��� fs�� �̸����� ��Ī
namespace fs = std::filesystem;

int main() {
    // ������ ����� �ִ��� �ݺ����� Ȯ���ϱ� ����
    while (true) {
        bool is_modified = false;  // �̹� ��ȸ���� ���� ���� ����

        // some_file ���� �� ��� �׸� ��ȸ
        for (const auto& entry : fs::directory_iterator("./some_file")) {
            // Ȯ���� ��������
            const std::string ext = entry.path().extension().string();

            // Ȯ���ڰ� .txt�� ���� �õ�
            if (ext == ".txt") {
                // ���� ����
                fs::remove(entry.path());

                // ��������� �ٽ� Ž�� ���� �����ϱ� ���� true ����
                is_modified = true;
                break;  // ���� �� �ٷ� ���� �������� ��Ž��
            }
        }

        // ���� �̹� ��ȸ���� �ƹ��͵� �������� �ʾҴٸ� �ݺ� ����
        if (!is_modified)
            break;
    }
}
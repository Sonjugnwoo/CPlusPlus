#include <filesystem>
#include <iostream>

// std::filesystem ���ӽ����̽��� fs�� �̸����� ��Ī
namespace fs = std::filesystem;

int main() {
    // ���� �۾� ���͸��� "some_file" ���� ������ Ž���� directory_iterator ����
    fs::directory_iterator itr(fs::current_path() / "some_file");

    // �ݺ��� itr�� ��(end)���� �ƴ� ������ �ݺ�
    while (itr != fs::end(itr)) {
        // ���� �ݺ��ڰ� ����Ű�� ���͸� ��Ʈ��(���� �Ǵ� ����)�� ����
        const fs::directory_entry& entry = *itr;
        // �ش� ��Ʈ���� ��ü ��� ���
        std::cout << entry.path() << std::endl;
        // ���� ��Ʈ���� �̵�
        itr++;
    }
}
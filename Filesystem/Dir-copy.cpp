#include <filesystem>
#include <iostream>

// std::filesystem ���ӽ����̽��� fs��� ��Ī���� ���
namespace fs = std::filesystem;
/*
skip_existing : �̹� �����ϴ� ������ ���� (���� �ȴ�����)
overwrite_existing : �̹� �����ϴ� ������ ���� �����.
update_existing : �̹� �����ϴ� ������ �� �����Ǿ��� ��� ���� �����.
*/
int main() {
    // ������ ���� ���� ��� ����
    fs::path from("./some_file/text1.txt");
    // ���� ��� ���� ��� ���� (some_file ���� �� TEXT2��� �̸�)
    fs::path to("./some_file/TEXT2");

    try {
        // ���� ������ �����ϰ� �Ϲ� �������� Ȯ��
        if (fs::exists(from) && fs::is_regular_file(from)) {

            // ���� ���� ����, ���� ��� ������ ������ ���
            fs::copy(from, to, fs::copy_options::overwrite_existing);

            // ���� ���� �޽��� ���
            std::cout << "���� ���� ����\n";
        }
        else {
            // ���� ������ ���ų� �Ϲ� ������ �ƴϸ� ���
            std::cout << "������ ������ �������� �ʽ��ϴ�.\n";
        }
    }
    // ���� �������� ���� �ý��� ���� ���ܰ� �߻��ϸ� ĳġ�Ͽ� ���
    catch (const fs::filesystem_error& e) {
        std::cout << "���� �� ���� �߻�: " << e.what() << std::endl;
    }
}
#include <filesystem>
#include <iostream>

// std::filesystem ���ӽ����̽��� fs�� �̸����� ��Ī
namespace fs = std::filesystem;

int main() {
    // ��� ��� './some_file'�� fs::path ��ü p�� ����
    fs::path p("./some_file");

    // ���� �۾� ���͸�(���α׷� ���� ���� ���) ���
    std::cout << "���� ��� : " << fs::current_path() << std::endl;

    // p�� ��� ���(������ �״��, ./some_file)�� ���
    std::cout << "��� ��� : " << p.relative_path() << std::endl;

    // p�� ���� ���(���� ��� �������� ��ȯ�� ���)�� ���
    std::cout << "���� ��� : " << fs::absolute(p) << std::endl;

    // p�� �������� ���� ���(������ �����ؾ� �ϸ�, �ɺ��� ��ũ�� ���� ��η� ��ȯ��)
    // ����/������ ������ ����(����) �߻�!
    std::cout << "�������� ���� ��� : " << fs::canonical(p) << std::endl;
}
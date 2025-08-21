#include <filesystem>
#include <iostream>

// std::filesystem ���ӽ����̽��� fs�� ��Ī
namespace fs = std::filesystem;

int main() {
    // ��� ��� "./some_file/test"�� ��Ÿ���� path ��ü p ����
    fs::path p("./some_file/test");

    // ���� �Ǵ� ���� ���� ���� ���
    std::cout << "Dose" << p << " exist [" << std::boolalpha << fs::exists(p) << "]" << std::endl;

    // p ��� ��ġ�� ���͸� ���� �õ� (������ ����)
    fs::create_directory(p);  //  -> �θ���丮�� ���� ���� ������ ���� �߻� 
                              // �ѹ��� ����� ������ fs::create_directorise(p) ��� 

    // ���͸� ���� �� ���� ���� ��Ȯ�� ���
    std::cout << "Dose" << p << " exist [" << std::boolalpha << fs::exists(p) << "]" << std::endl;

    // p ��ΰ� ���͸����� Ȯ���Ͽ� ���
    std::cout << "It" << p << " directory ? [" << fs::is_directory(p) << "]" << std::endl;
}
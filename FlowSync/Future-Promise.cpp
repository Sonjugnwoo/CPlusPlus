// Future-Promise -> �̷��� ������ T�� ���ϴ� �����͸� ���� �ְٴ� ��� ���

#include <future>
#include <iostream>
#include <string>
#include <thread>

// ��Ŀ �����忡�� ����� �Լ�
void worker(std::promise<std::string>* p) {
	// promise�� �� ���� -> ����� future�� �� ���� ���� �� �ְ� ��
	p->set_value("some data");
}

int main() {
    //  promise ���� : �̷��� std::string Ÿ�� �����͸� �����ϰڴٴ� ��� ��ü
    std::promise<std::string> p;

    //  future ȹ�� : promise�� ����� future�� ���, ���߿� ������ ���� ����
    std::future<std::string> data = p.get_future();

    //  ��Ŀ ������ ����, promise �����͸� ���ڷ� �ѱ�
    std::thread t(worker, &p);

    //  future ������ �غ�� ������ ��� (worker���� set_value ȣ���� ������ ���)
    data.wait();

    //  future���� �� ������ (get ȣ�� �� ���� �غ���� �ʾҴٸ� ���������� wait)
    std::cout << "���� ������ " << data.get() << std::endl;

    //  ��Ŀ �����尡 ���� ������ ���� �����忡�� ���
    t.join();
}
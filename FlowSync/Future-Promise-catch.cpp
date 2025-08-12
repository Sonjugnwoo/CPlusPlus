#include <exception>
#include <string>
#include <thread>
#include <future>
#include <iostream>

//���ܸ� �߻���Ű�� promise�� ���� main ������� ����
void worker(std::promise<std::string>* p) {
	try {
		throw std::runtime_error("Some Error");	 // �Ϻη� ���� �߻�
	}
	catch (...) {
		// ��� Ÿ���� ���ܸ� ����
	    // ���� ���� ���¸� exception_ptr�� �����ͼ� promise�� ����
	    // �� ���߿� future.get()���� �� ���ܰ� �ٽ� ������
		p->set_exception(std::current_exception());
	}
}

int main() {
	std::promise<std::string> p;					 // �� �Ǵ� ���ܸ� ������ promise
	std::future<std::string> data = p.get_future();	 // promise�� ����� future

	std::thread t(worker, &p);						 // worker ������ ����, promise �ּ� ����

	data.wait();								     // future�� ���̳� ���ܰ� ������ ������ ���

	try {
		// future���� �� �ޱ� (Ȥ�� ���� �߻�)
		// �� ��� ���ܰ� �����Ǿ� ������ �� �������� ���ܰ� �ٽ� ������
		data.get();
	}
	catch (const std::exception& e) {
		// ������ ������ ���ܸ� ����
		std::cout << "���� : " << e.what() << std::endl;
	}

	t.join();
}
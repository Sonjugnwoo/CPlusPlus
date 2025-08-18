#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    // ������: num_threads ��ŭ�� ��Ŀ �����带 ����
    ThreadPool(size_t num_threads)
        : num_thread(num_threads), stop(false)
    {
        workers.reserve(num_threads); // ���� �޸� �̸� Ȯ��
        for (size_t i = 0; i < num_threads; ++i)
            // �� �����尡 workerThread() �Լ��� �����ϵ��� ����
            workers.emplace_back([this]() { this->workerThread(); });
    }

    // �Ҹ���: ������ ���� ó��
    ~ThreadPool() {
        // ���� �÷��� ����
        stop = true;
        // ��� ��� ���� ������ �����
        cv.notify_all();
        // ��� �����尡 ����� ������ join()
        for (auto& t : workers)
            t.join();
    }

    // �۾��� �߰��ϴ� �Լ�
    void enqueue(std::function<void()> job) {
        if (stop) throw std::runtime_error("ThreadPool �������");
        {
            // �۾� ť ��ȣ�� ���� ���ؽ� lock
            std::lock_guard<std::mutex> lock(queue_mutex);
            // ���ο� �۾��� ť�� �߰�
            jobs.push(std::move(job));
        }
        // �ϳ��� �����带 ������ �۾��� ó���ϰ� ��
        cv.notify_one();
    }
    // ���� �۾� �Լ� (t�� ���� ��� �� id ���)
    void work(int t , int id ) {
        printf("%d start\n", id);
        std::this_thread::sleep_for(std::chrono::seconds(t));
        printf("%d end after %ds\n", id, t);
    }

private:
    // ���� ��Ŀ �����尡 �����ϴ� �Լ�
    void workerThread() {
        while (true) {
            std::unique_lock<std::mutex> lock(queue_mutex);
            // ���� ���� ���: jobs�� ������� �ʰų� stop ������ �� ���
            cv.wait(lock, [this]() { return !this->jobs.empty() || stop; });

            // ���� ����: stop�̰� jobs�� ��������� ������ ����
            if (stop && this->jobs.empty())
                return;

            // ť���� �۾��� �ϳ� ����
            std::function<void()> job = std::move(jobs.front());
            jobs.pop();

            // �۾� ���� �� ���ؽ� ����
            lock.unlock();

            // �۾� ����
            job();
        }
    }

    size_t num_thread;                       // ������ ������ ����
    std::vector<std::thread> workers;        // ��Ŀ ��������� �����̳�
    std::queue<std::function<void()>> jobs;  // ������ �۾� ť
    std::mutex queue_mutex;                  // �۾� ť ��ȣ�� ���ؽ�
    std::condition_variable cv;              // ������ ����ȭ�� ���� ���� ����
    bool stop = false;                       // ������Ǯ ���� ����
};

int main() {
    ThreadPool pool(5);

    for (int i = 0; i < 10; i++)
        pool.enqueue([&pool,i]() {pool.work(i % 3 + 1, i); });
        
}
#include <chrono>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <future>
#include <thread>
#include <vector>
#include <queue>
#include <cstdio>

namespace ThreadPool {
	class ThreadPool {
	public:
		ThreadPool(size_t num_threads);  // ������
		~ThreadPool();                   // �Ҹ���

		// �۾��� ť�� �߰��ϰ� future�� ��ȯ�ϴ� ���ø� �Լ�
		template<class F, class... Args>
		std::future<typename std::result_of<F(Args...)>::type>
			EnqueueJob(F&& f, Args&&... args);

	private:
		size_t num_threads_;                       // ������ ����
		std::vector<std::thread> worker_threads_;  // ��Ŀ �������
		std::queue<std::function<void()>> jobs_;   // ���� ��� ���� �۾� ť

		std::condition_variable cv_job; // ���� ���� (�۾� ��� & �����)
		std::mutex m_job;               // �۾� ť ��ȣ�� ���ؽ�
		bool stop_all;                  // ThreadPool ���� �÷���

		void WorkerThread();            // ��Ŀ ������ �Լ�
	};

	// ThreadPool ������
	ThreadPool::ThreadPool(size_t num_threads) : num_threads_(num_threads), stop_all(false) {
		worker_threads_.reserve(num_threads);

		// �� �����忡�� WorkerThread �Լ� ����
		for (size_t i = 0; i < num_threads; ++i)
			worker_threads_.emplace_back([this]() {this->WorkerThread(); });	
	}

	// ��Ŀ �����尡 �����ϴ� �Լ�
	void ThreadPool::WorkerThread() {
		while (true) {
			std::unique_lock<std::mutex> lock(m_job);
			// jobs_�� ��� ���� �ʰų� ���� ��ȣ�� �� ������ ���
			cv_job.wait(lock, [this]() {return !this->jobs_.empty() || stop_all; });

			// ���� ���� : ���� �÷��װ� �����ǰ� �۾� ť�� ������� ����
			if (stop_all && this->jobs_.empty())
				return;

			// ť���� �۾� ������
			std::function<void()> job = std::move(jobs_.front());
			jobs_.pop();
			lock.unlock();

			// ���� �۾� ����
			job();
		}

	}

	// ThreadPool �Ҹ���
	ThreadPool::~ThreadPool() {
		stop_all = true;      // ���� �÷��� ����
		cv_job.notify_all();  // ��� ��� ������ �����
		for (auto& t : worker_threads_)
			t.join();        // ��� �����尡 ����� ������ ���
	}

	// �۾��� ť�� �ְ�, ���� ����� future�� �޴� �Լ�
	template<class F, class... Args>
	std::future<typename std::result_of<F(Args...)>::type>
		ThreadPool::EnqueueJob(F&& f, Args&&... args) {
		if (stop_all)
			throw std::runtime_error("ThreadPool �۵� �ߴ�");

		// ��ȯ�� �߷�
		using return_type = typename std::result_of<F(Args...)>::type;

		// �۾��� packaged_task�� �����Ͽ� future�� ��ȯ �����ϰ� ��
		auto job = std::make_shared<std::packaged_task<return_type()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
			);

		std::future<return_type> job_result_future = job->get_future();
		{
			std::lock_guard<std::mutex> lock(m_job);
			// ���ٷ� ���� ������ ���·� ť�� ����
			jobs_.push([job]() { (*job)(); });
		}

		// �۾��� �߰��Ǿ����� �˸� �� ��� ���� ������ �ϳ� �����
		cv_job.notify_one();

		return job_result_future; // ���� ����� ���� future ��ȯ
	}
}

// ���� �۾� �Լ�
int work(int t, int id) {
	printf("%d start\n", id);
	std::this_thread::sleep_for(std::chrono::seconds(t)); // t�� ���
	printf("%d end after %ds\n", id, t);
	return t + id; // ����� ����
}

int main() {
	ThreadPool::ThreadPool pool(5); // ������Ǯ ���� (��Ŀ 5��)
	std::vector<std::future<int>> futures;

	// 10���� �۾��� ������Ǯ�� ť��
	for (int i = 0; i < 10; i++)
		futures.emplace_back(pool.EnqueueJob(work, i % 3 + 1, i));

	// ��� future���� ���� ����� �޾� ���
	for (auto& f : futures)
		printf("result : %d \n", f.get());
}
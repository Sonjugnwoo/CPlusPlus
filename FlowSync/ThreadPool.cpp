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
		ThreadPool(size_t num_threads);  // 생성자
		~ThreadPool();                   // 소멸자

		// 작업을 큐에 추가하고 future를 반환하는 템플릿 함수
		template<class F, class... Args>
		std::future<typename std::result_of<F(Args...)>::type>
			EnqueueJob(F&& f, Args&&... args);

	private:
		size_t num_threads_;                       // 스레드 개수
		std::vector<std::thread> worker_threads_;  // 워커 스레드들
		std::queue<std::function<void()>> jobs_;   // 실행 대기 중인 작업 큐

		std::condition_variable cv_job; // 조건 변수 (작업 대기 & 깨우기)
		std::mutex m_job;               // 작업 큐 보호용 뮤텍스
		bool stop_all;                  // ThreadPool 종료 플래그

		void WorkerThread();            // 워커 스레드 함수
	};

	// ThreadPool 생성자
	ThreadPool::ThreadPool(size_t num_threads) : num_threads_(num_threads), stop_all(false) {
		worker_threads_.reserve(num_threads);

		// 각 스레드에서 WorkerThread 함수 실행
		for (size_t i = 0; i < num_threads; ++i)
			worker_threads_.emplace_back([this]() {this->WorkerThread(); });	
	}

	// 워커 스레드가 수행하는 함수
	void ThreadPool::WorkerThread() {
		while (true) {
			std::unique_lock<std::mutex> lock(m_job);
			// jobs_가 비어 있지 않거나 종료 신호가 올 때까지 대기
			cv_job.wait(lock, [this]() {return !this->jobs_.empty() || stop_all; });

			// 종료 조건 : 종료 플래그가 설정되고 작업 큐가 비었으면 종료
			if (stop_all && this->jobs_.empty())
				return;

			// 큐에서 작업 꺼내기
			std::function<void()> job = std::move(jobs_.front());
			jobs_.pop();
			lock.unlock();

			// 실제 작업 실행
			job();
		}

	}

	// ThreadPool 소멸자
	ThreadPool::~ThreadPool() {
		stop_all = true;      // 종료 플래그 설정
		cv_job.notify_all();  // 모든 대기 스레드 깨우기
		for (auto& t : worker_threads_)
			t.join();        // 모든 스레드가 종료될 때까지 대기
	}

	// 작업을 큐에 넣고, 실행 결과를 future로 받는 함수
	template<class F, class... Args>
	std::future<typename std::result_of<F(Args...)>::type>
		ThreadPool::EnqueueJob(F&& f, Args&&... args) {
		if (stop_all)
			throw std::runtime_error("ThreadPool 작동 중단");

		// 반환형 추론
		using return_type = typename std::result_of<F(Args...)>::type;

		// 작업을 packaged_task로 래핑하여 future를 반환 가능하게 함
		auto job = std::make_shared<std::packaged_task<return_type()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
			);

		std::future<return_type> job_result_future = job->get_future();
		{
			std::lock_guard<std::mutex> lock(m_job);
			// 람다로 실행 가능한 형태로 큐에 저장
			jobs_.push([job]() { (*job)(); });
		}

		// 작업이 추가되었음을 알림 → 대기 중인 스레드 하나 깨우기
		cv_job.notify_one();

		return job_result_future; // 실행 결과를 담을 future 반환
	}
}

// 예시 작업 함수
int work(int t, int id) {
	printf("%d start\n", id);
	std::this_thread::sleep_for(std::chrono::seconds(t)); // t초 대기
	printf("%d end after %ds\n", id, t);
	return t + id; // 결과값 리턴
}

int main() {
	ThreadPool::ThreadPool pool(5); // 스레드풀 생성 (워커 5개)
	std::vector<std::future<int>> futures;

	// 10개의 작업을 스레드풀에 큐잉
	for (int i = 0; i < 10; i++)
		futures.emplace_back(pool.EnqueueJob(work, i % 3 + 1, i));

	// 모든 future에서 실행 결과를 받아 출력
	for (auto& f : futures)
		printf("result : %d \n", f.get());
}
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    // 생성자: num_threads 만큼의 워커 스레드를 생성
    ThreadPool(size_t num_threads)
        : num_thread(num_threads), stop(false)
    {
        workers.reserve(num_threads); // 벡터 메모리 미리 확보
        for (size_t i = 0; i < num_threads; ++i)
            // 각 스레드가 workerThread() 함수를 실행하도록 설정
            workers.emplace_back([this]() { this->workerThread(); });
    }

    // 소멸자: 스레드 종료 처리
    ~ThreadPool() {
        // 종료 플래그 설정
        stop = true;
        // 모든 대기 중인 스레드 깨우기
        cv.notify_all();
        // 모든 스레드가 종료될 때까지 join()
        for (auto& t : workers)
            t.join();
    }

    // 작업을 추가하는 함수
    void enqueue(std::function<void()> job) {
        if (stop) throw std::runtime_error("ThreadPool 사용중지");
        {
            // 작업 큐 보호를 위한 뮤텍스 lock
            std::lock_guard<std::mutex> lock(queue_mutex);
            // 새로운 작업을 큐에 추가
            jobs.push(std::move(job));
        }
        // 하나의 스레드를 깨워서 작업을 처리하게 함
        cv.notify_one();
    }
    // 예시 작업 함수 (t초 동안 대기 후 id 출력)
    void work(int t , int id ) {
        printf("%d start\n", id);
        std::this_thread::sleep_for(std::chrono::seconds(t));
        printf("%d end after %ds\n", id, t);
    }

private:
    // 실제 워커 스레드가 수행하는 함수
    void workerThread() {
        while (true) {
            std::unique_lock<std::mutex> lock(queue_mutex);
            // 조건 변수 대기: jobs가 비어있지 않거나 stop 상태일 때 깨어남
            cv.wait(lock, [this]() { return !this->jobs.empty() || stop; });

            // 종료 조건: stop이고 jobs도 비어있으면 스레드 종료
            if (stop && this->jobs.empty())
                return;

            // 큐에서 작업을 하나 꺼냄
            std::function<void()> job = std::move(jobs.front());
            jobs.pop();

            // 작업 실행 전 뮤텍스 해제
            lock.unlock();

            // 작업 실행
            job();
        }
    }

    size_t num_thread;                       // 생성할 스레드 개수
    std::vector<std::thread> workers;        // 워커 스레드들의 컨테이너
    std::queue<std::function<void()>> jobs;  // 실행할 작업 큐
    std::mutex queue_mutex;                  // 작업 큐 보호용 뮤텍스
    std::condition_variable cv;              // 스레드 동기화를 위한 조건 변수
    bool stop = false;                       // 스레드풀 종료 여부
};

int main() {
    ThreadPool pool(5);

    for (int i = 0; i < 10; i++)
        pool.enqueue([&pool,i]() {pool.work(i % 3 + 1, i); });
        
}
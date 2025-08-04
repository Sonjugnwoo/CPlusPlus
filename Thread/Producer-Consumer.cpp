// 생산자(Producer) - 처리할 일을 생성하거나 받아와서 작업 큐에 넣는 쓰레드
// 소비자(Consumer) - 작업 큐에서 일을 꺼내 실제로 처리하는 쓰레드

#include <iostream>
#include <chrono>
#include <mutex>
#include <queue>
#include <string>
#include <vector>
#include <thread>





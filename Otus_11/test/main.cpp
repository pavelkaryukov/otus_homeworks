#include "lib/bulk_async.h" 
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>


std::condition_variable g_Condition;
std::mutex g_MutexThread;

void ThreadFunc() {
    std::cout << "Create thread id=" << std::this_thread::get_id() << std::endl;
    {
        std::unique_lock<std::mutex> locker(g_MutexThread);
        g_Condition.wait_for(locker, std::chrono::seconds(2));
    }
    std::cout << "WakeUp id=" << std::this_thread::get_id() << std::endl;
    std::string testCmd = "cmd1";
    auto handl1 = async::connect(3);
    auto handl2 = async::connect(2);
    async::receive(handl1, testCmd.data(), testCmd.size());
    async::receive(handl1, testCmd.data(), testCmd.size());

    async::receive(handl2, testCmd.data(), testCmd.size());
    async::receive(handl2, testCmd.data(), testCmd.size());
    async::receive(handl2, testCmd.data(), testCmd.size());
    async::receive(handl2, testCmd.data(), testCmd.size());

    async::receive(handl1, testCmd.data(), testCmd.size());
    async::receive(handl1, testCmd.data(), testCmd.size());
    async::disconnect(handl1);

    async::receive(handl2, testCmd.data(), testCmd.size());
    async::receive(handl2, testCmd.data(), testCmd.size());
    async::receive(handl2, testCmd.data(), testCmd.size());
    async::receive(handl2, testCmd.data(), testCmd.size());
    async::disconnect(handl2);
}

int main() {
    //Создание объектов из разных потоков, должно быть 42 bulk суммарно (42 файла)
    std::vector<std::unique_ptr<std::thread>> threads;
    for (int i = 0; i <= 6; ++i) {
        threads.emplace_back(std::make_unique<std::thread>(std::thread{ []() { ThreadFunc(); }}));
    }
    {
        std::unique_lock<std::mutex> locker(g_MutexThread);
        std::cout << "WakeUp All" << std::endl;
        g_Condition.notify_all();
    }

    for (auto& thread : threads) {
        thread->join();
    }

    return 0;
}
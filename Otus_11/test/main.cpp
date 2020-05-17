#include "lib/bulk_async.h" 
#include <condition_variable>
#include <mutex>
#include <thread>

std::condition_variable g_Condition;
std::mutex g_MutexThread;

void ThreadFunc() {
    {
        std::unique_lock<std::mutex> locker(g_MutexThread);
        g_Condition.wait(locker);
    }
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
    std::vector<std::thread> threads;
    for (int i = 0; i <= 6; ++i) {
        threads.push_back(std::move(std::thread{ []() { ThreadFunc(); }}));
    }
    {
        std::unique_lock<std::mutex> locker(g_MutexThread);
        g_Condition.notify_all();
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
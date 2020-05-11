#pragma once
#include "logger/ilogger.h"
#include <atomic>
#include <boost/format.hpp> 
#include <condition_variable>  
#include <cstring> 
#include <filesystem>
#include <fstream>
#include <string> 
#include <time.h>
#include <thread>

class LoggerFile final : public ILogger {
public:
    LoggerFile() = default;

    void Exit() override {
        m_Execute.store(false);
        {
            std::unique_lock<std::mutex> locker(m_MutexThread);
            m_Condition.notify_all();
        }
    };

    std::thread CreateThread() override {
        return std::thread([&]() { PrintFunc(); });
    }
private:
    std::condition_variable m_Condition;
    std::mutex m_MutexThread;
    ConcurentDeque<std::string> m_Deque;
    std::atomic<bool> m_Execute{ true };
   
    void PrintFunc() {
        while (m_Execute) {
            if (m_Deque.empty()) {
                std::unique_lock<std::mutex> locker(m_MutexThread);
                m_Condition.wait(locker);
            }

            if (m_Deque.empty())
                continue;

            auto head = m_Deque.front();
            SaveLogInFile(head);
            m_Deque.pop_front();
        }
    }

    void SaveLogInFile(std::string aStr) {
        auto createTime = time(nullptr);
        auto bulkTime = createTime;
        for (int i= 0; i <= 100; ++i) {
            std::string filename = boost::str(boost::format("bulk_%1%_%2%.txt")%createTime%i);
            if (std::filesystem::exists(filename))
                continue;
            std::ofstream file(filename);
            if (file.is_open()) {
                file << boost::format("thread_id=[%1%]") % std::this_thread::get_id() << std::endl;
                file << aStr;
                return;
            }
        }
    }

    void SaveLog(std::string aStr) override {
        m_Deque.push_back(aStr);
        std::unique_lock<std::mutex> locker(m_MutexThread);
        m_Condition.notify_all();
    }
};


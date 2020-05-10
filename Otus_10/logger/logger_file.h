#pragma once
#include "logger/ilogger.h"
#include <string> 
#include <boost/format.hpp>
#include <fstream>
#include <time.h> 
#include <filesystem>

class LoggerFile final : public ILogger {
public:
    LoggerFile() {
        CreateThread();
    }

    void Exit() override {
        _execute.store(false);
        {
            std::unique_lock<std::mutex> locker(_mutexThread);
            _condition.notify_all();
        }
        if (_thread.joinable())
            _thread.join();
    };

    ~LoggerFile() {
        _thread.detach();
    }

private:
    std::condition_variable _condition;
    std::mutex _mutexThread;
    ConcurentDeque<std::string> _deque;
    std::atomic<bool> _execute{ true };
    std::thread _thread;


    void PrintFunc() {
        while (_execute) {
            if (_deque.empty()) {
                std::unique_lock<std::mutex> locker(_mutexThread);
                _condition.wait(locker);
            }

            if (_deque.empty())
                continue;

            auto head = _deque.front();
            SaveLogInFile(head);
            _deque.pop_front();
        }
    }

    void CreateThread() {
        _thread = std::thread([&]() { PrintFunc(); });
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
                file << aStr;
                return;
            }
        }
    }

    void SaveLog(std::string aStr) override {
        _deque.push_back(aStr);
        std::unique_lock<std::mutex> locker(_mutexThread);
        _condition.notify_all();
    }
};


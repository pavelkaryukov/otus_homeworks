#pragma once
#include "concurrent/concurrent_deque.h" 
#include <cstring>
#include <condition_variable>  
#include <boost/format.hpp> 
#include <mutex>
#include <thread>
#include <atomic>
#include <iostream>
#include <thread>
#include <functional>

class LoggerScreen {
public:
    LoggerScreen(std::ostream& aStream, std::mutex& aMutex) : _stream(aStream), _mutexPrint(std::shared_ptr<std::mutex>(&aMutex)) {
        if (_mutexPrint)
            CreateThread(); 
    }

    void Output(std::string aStr) {
        _deque.push_back(aStr);
        std::unique_lock<std::mutex> locker(_mutexThread);
        _condition.notify_all();
    }
private:   
    LoggerScreen() {};

    std::ostream& _stream = std::cout;
    std::condition_variable _condition;
    std::mutex _mutexThread;
    std::shared_ptr<std::mutex> _mutexPrint;
    ConcurentDeque<std::string> _deque;
    std::atomic<bool> _execute = true;
    std::thread _thread;


    void PrintFunc() {
        while (_execute) {
            std::unique_lock<std::mutex> locker(_mutexThread);
            if (_deque.empty())
                _condition.wait(locker);
            if (!_execute)
                return;

            if (_deque.empty())
                continue;

            auto head = _deque.front();
            _deque.pop_front();
            {
                if (!_mutexPrint) {
                    return;
                }
                std::lock_guard<std::mutex> lockPrint(*_mutexPrint);
                std::cout << boost::format("Thread [%1%] Value=[%2%]") % std::this_thread::get_id() % head << std::endl;
            }
        }
        {
            if (!_mutexPrint) {
                return;
            }
            std::lock_guard<std::mutex> lockPrint(*_mutexPrint);
            std::cout << boost::format("Thread [%1%] Must be terminated") % std::this_thread::get_id() << std::endl;
        }
    }

    void CreateThread() {
        _thread = std::thread( [&]() { PrintFunc();});
        _thread.detach();
    }
};
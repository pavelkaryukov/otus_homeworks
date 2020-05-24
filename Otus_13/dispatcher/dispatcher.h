#pragma once
#include "concurrent/concurrent_deque.h"
#include "rsubd/cmd_performer.h"
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class DispatherSUBD{
public:
    DispatherSUBD(std::ostream& aStream, std::shared_ptr<std::mutex> aMutex) : m_Stream(aStream), m_MutexPrint(aMutex) {
        m_Thread = std::thread(&DispatherSUBD::PrintFunc, this);
    }

    void ProcessCommand(std::string aStr) {
        m_Deque.push_back(aStr);
        std::unique_lock<std::mutex> locker(m_MutexThread);
        m_Condition.notify_one();
    }

    void Exit() {
        m_Execute.store(false);
        {
            std::unique_lock<std::mutex> locker(m_MutexThread);
            m_Condition.notify_one();
        }

        if (m_Thread.joinable())
            m_Thread.join();

        m_MutexPrint.reset();
    };
private:
    DispatherSUBD() {};

    std::ostream& m_Stream = std::cout;
    std::shared_ptr<std::mutex> m_MutexPrint;
    ConcurentDeque<std::string> m_Deque;
    std::condition_variable m_Condition;
    std::mutex m_MutexThread;
    std::thread m_Thread;
    std::atomic<bool> m_Execute{ true };
    CmdPerformer m_CmdPerformer;

    void PrintFunc() {
        while (m_Execute || !m_Deque.empty()) {
            if (m_Deque.empty()) {
                std::unique_lock<std::mutex> locker(m_MutexThread);
                m_Condition.wait(locker);
            }

            if (m_Deque.empty())
                continue;

            auto head = m_Deque.front();
            m_Deque.pop_front();
            {
                //Обработка комманд, так.как работа m_CmdPerformer осуществл¤етс¤ только из этой нитки, то обойдемс¤ без mutex
                if (!m_MutexPrint || !m_Stream)
                    return;

                std::lock_guard<std::mutex> lockPrint(*m_MutexPrint);
                m_Stream << m_CmdPerformer.ProcessCommand(head) << std::endl;
            }
        }
    }
};
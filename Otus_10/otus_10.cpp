#include "dispatcher/dispatcher.h"
#include <cctype> 
#include <cstring>
#include <condition_variable>  
#include <mutex>
#include <thread>
#include <atomic>
#include <boost/format.hpp>



std::condition_variable g_condvar;
std::mutex g_mutexThread;
std::mutex g_mutexPrint;
std::atomic<bool> g_execute = true;

template<class T>
class DequeMT {
public:

    bool empty() const {
        std::lock_guard<std::mutex> guard(_mutex);
            return _deque.empty();
    }

    void push_back(T obj) {
        std::lock_guard<std::mutex> guard(_mutex);
        _deque.push_back(obj);
    }

    T front() {
        std::lock_guard<std::mutex> guard(_mutex);
        return _deque.front();
    }

    void pop_front() {
        std::lock_guard<std::mutex> guard(_mutex);
        _deque.pop_front();
    }

private:
    std::deque<T> _deque;
    mutable std::mutex    _mutex;
};


DequeMT<std::string> g_testDeque;

void TestMegaFunc() {
    
    while (g_execute) {
        std::unique_lock<std::mutex> locker(g_mutexThread);
        if (g_testDeque.empty())
            g_condvar.wait(locker);
        
        if (g_testDeque.empty())
            continue;

        auto arbuz = g_testDeque.front();
        g_testDeque.pop_front();
        {
            std::lock_guard<std::mutex> lockPrint(g_mutexPrint);
            std::cout << boost::format("Thread [%1%] Value=[%2%]") % std::this_thread::get_id() % arbuz << std::endl;
        }
    }
    {
        std::lock_guard<std::mutex> lockPrint(g_mutexPrint);
        std::cout << boost::format("Thread [%1%] Must be terminated") % std::this_thread::get_id() << std::endl;
    }
}


bool IsValidArg(const char* aStr) {
    auto len = strlen(aStr);
    const std::size_t kMaxLen = 8;
    if (len > kMaxLen)
        return false;

    for (auto i=0U; i<kMaxLen; ++i){
        if (std::isdigit(aStr[i]) == 0)
            return false;
    }
    return true;
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    std::size_t N = 0;
    if (argc == 1) {
        std::cout << " оличество команд в одной куче (bulk) не было установлено. ”становлено  значение по умолчанию = 3" << std::endl;
        N = 3;
    }
    else {
        if (IsValidArg(argv[1])) {
            N = std::atoi(argv[1]);
        }
        else {
            std::cout << " оличество команд в одной куче (bulk) имеет не валидное значение ["<<argv[1]<<"]. ”становлено  значение по умолчанию = 3" << std::endl;
            N = 3;
        }
    }

    const std::size_t kBulkSize = N > 0 ? N : 1; // кол-во команда в одной булке

    CommandDispatcher dispatcher{ kBulkSize};
    std::string str;
    //std::thread t1(TestMegaFunc);
    //t1.detach();

    std::cout << boost::format("Main Thread ID =[%1%]") % std::this_thread::get_id() << std::endl;
    //t1.join();
    while (std::getline(std::cin, str)) {
        try {
            dispatcher.ProcessCmdLine(str);
            /*{
                std::lock_guard<std::mutex> lockPrint(g_mutexPrint);
                std::cout << boost::format("Main Thread [%1%] Value=[%2%]") % std::this_thread::get_id() % str << std::endl;
            }
            if (str == "off") {
                g_execute = false;
            }
            g_testDeque.push_back(str);
            std::unique_lock<std::mutex> locker(g_mutexThread);
            g_condvar.notify_all();*/
        }
        catch (std::exception& e) {
            std::cout << "Exception:" << std::endl;
            std::cout << e.what() << std::endl;
            std::cout << "Program \"bulk\" Terminate" << std::endl;
            return 0;
        }
    }
    dispatcher.Flush(); //ѕодумать, что можно сделать, что бы программа не взрывалась
    return 0;
}

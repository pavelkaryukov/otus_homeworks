#include "bulk_async.h"
#include "dispatcher/dispatcher.h"
#include <mutex>
#include <unordered_map>
namespace {
    using namespace  async;
    class AsyncDispatcher {
    public:
        AsyncDispatcher() = default;

        handle_t Add(const std::size_t aBulkSize, std::ostream& aOutStream) {
            //if (!m_OutPrintMutex)
            //    return 0;

            //Try catch and ...
            std::lock_guard<std::mutex> locker(m_Mutex);
            ++m_Counter;
            m_Dispatchers.insert({ m_Counter, std::make_unique<CommandDispatcher>(aBulkSize, aOutStream, 2, m_OutPrintMutex) });
            return m_Counter;
        }

        void ReceiveMsg(const handle_t aHandle, const char *aData, const std::size_t aSize) {
            decltype(m_Dispatchers)::const_iterator iter;
            {
                std::lock_guard<std::mutex> locker(m_Mutex);
                iter = m_Dispatchers.find(aHandle);
            }

            if (iter == m_Dispatchers.end()) {
                //Во избежания dead lock минимизируем
                std::cout << "Cant find elem with id = " << std::endl; //TODO:: доделать вывод на экран, с блокировкой mutex
                return;
            }
            if (iter->second) {
                iter->second->ProcessCmdLine(std::string(aData, aData + aSize));
            }            
        }

        void CloseDispatcher(const handle_t aHandle) {
            decltype(m_Dispatchers)::const_iterator iter;
            {
                std::lock_guard<std::mutex> locker(m_Mutex);
                iter = m_Dispatchers.find(aHandle);
            }

            if (iter == m_Dispatchers.end()) {
                //Во избежания dead lock минимизируем
                std::cout << "Cant find elem with id = " << std::endl; //TODO:: доделать вывод на экран, с блокировкой mutex
                return;
            }

            if (iter->second) {
                iter->second->Flush();
            }
      
            {
                std::lock_guard<std::mutex> locker(m_Mutex);
                m_Dispatchers.erase(iter);
            }
        }

    private:
        std::unordered_map<handle_t, std::unique_ptr<CommandDispatcher>> m_Dispatchers;
        std::mutex m_Mutex;
        std::shared_ptr<std::mutex> m_OutPrintMutex = std::make_shared<std::mutex>();
        handle_t m_Counter = 0;
        //Задумка такая, что мьютекс контролирует вставку элементов в hashmap
    };
}

namespace async {
    AsyncDispatcher g_Dispatcher;

    handle_t connect(std::size_t bulk, std::ostream& aOutStream) {
        std::cout << "Connect method id=" << std::this_thread::get_id() << std::endl;
        return g_Dispatcher.Add(bulk, aOutStream);
    }

    void receive(handle_t handle, const char *data, std::size_t size) {
        std::cout << "Receive method id=" << std::this_thread::get_id() << std::endl;
        g_Dispatcher.ReceiveMsg(handle, data, size);
    }    
    
    void disconnect(handle_t handle) {
        std::cout << "Disconnect method id=" << std::this_thread::get_id() << std::endl;
        g_Dispatcher.CloseDispatcher(handle);
    }
}
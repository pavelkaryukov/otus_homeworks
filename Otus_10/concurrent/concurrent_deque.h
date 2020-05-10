#pragma once
#include <deque>
#include <mutex>

template<class T>
class ConcurentDeque {
public:

    bool empty() const {
        std::lock_guard<std::mutex> guard(_mutex);
        return _deque.empty();
    }

    void push_back(const T obj) {
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

    std::size_t size() const {
        std::lock_guard<std::mutex> guard(_mutex);
        return _deque.size();
    }

    void clear() {
        std::lock_guard<std::mutex> guard(_mutex);
        return _deque.clear();
    }
private:
    std::deque<T> _deque;
    mutable std::mutex    _mutex;
};
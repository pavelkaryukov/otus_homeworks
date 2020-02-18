#pragma once
#include <iostream>
#include <stdlib.h>
#include <array>
const std::size_t kMaxSize = 10;//TODO::Переделать в параметр шаблона
template<typename T>
struct MapAllocator
{
    // ИСПОЛЬЗОВАТЬ ТОЛЬКО С MAP
    using value_type = T;

    using pointer = T * ;
    using const_pointer = const T*;
    using reference = T & ;
    using const_reference = const T&;

    template<typename U>
    struct rebind
    {
        using other = MapAllocator<U>;
    };

    MapAllocator()
    {
    };
    ~MapAllocator()
    {
        //return;
        //TODO::При комите вернуть строчку
        if (m_Data != nullptr) {
            std::free(m_Data);
            m_Data = nullptr;
        }
    };

    template<typename U>
    MapAllocator(const MapAllocator<U>& aRhs)
    {    
    }

    T *allocate(std::size_t aNum)
    {
         if (m_Data == nullptr) {
             InitMemory();
         }
        const std::size_t sizeObj = sizeof(T);
        std::size_t currentPos = m_Pos;
        m_Pos += aNum;
        m_MaxCurrentPos = currentPos > m_MaxCurrentPos ? currentPos : m_MaxCurrentPos;
        if (m_Pos >= Reserved()) {
            Reserve(m_Pos);
        }
        return (T*)&m_Data[currentPos];
    }

    void deallocate(T *p, std::size_t n)
    {
        if (n > m_Pos) {
            m_Pos = 0;
            return;
        }
        m_Pos -= n;
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
        new(p) U(std::forward<Args>(args)...);
    };

    void destroy(T *p)
    {
        p->~T();
    }
    
    std::size_t Reserved() const
    {
        return m_MaxSize;
    }

    std::size_t max_size() const
    {
        return size_t(-1) / sizeof(T);
    }

private:
    pointer     m_Data = nullptr;
    std::size_t m_MaxSize = kMaxSize + 1;//Первый раз задастся на основе шаблонного параметра 
    std::size_t m_Pos = 0;
    std::size_t m_MaxCurrentPos = 0;

    void Reserve(const size_t aPos) // Выделит память, скопируют старую, освободит старую
    {
        if (aPos > max_size())
            throw std::bad_alloc();
            
        auto newMaxSize =  std::max(m_MaxSize, aPos) * 2;

        auto ptr = (pointer)std::malloc(newMaxSize * sizeof(T));;
        if (m_Data != nullptr) {
            memcpy(ptr, m_Data, m_MaxSize * sizeof(T));
            std::free(m_Data);
        }
        m_MaxSize = newMaxSize;
        m_Data = ptr;
    }

    void InitMemory()
    {
        m_Data = (pointer)std::malloc(m_MaxSize * sizeof(T));
        m_Pos = 0;
    }
};
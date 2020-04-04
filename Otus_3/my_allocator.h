#pragma once
#include <iostream>
#include <stdlib.h>
#include <array>
#include <cstring>
template<typename T, std::size_t TNum = 10>
struct MyAllocator
{
    static_assert(TNum != 0);
    using value_type = T;
    using pointer = T * ;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind
    {
        using other = MyAllocator<U, TNum>;
    };

    MyAllocator()
    {
    };
    ~MyAllocator()
    {
        if (m_Data != nullptr) {
            std::free(m_Data);
            m_Data = nullptr;
        }
    };

    template<typename U, std::size_t TNum2>
    MyAllocator(const MyAllocator<U, TNum2>& aRhs)
    {    
    }

    T *allocate(std::size_t aNum)
    {
         if (m_Data == nullptr) {
             InitMemory();
         }
        std::size_t currentPos = m_Pos;
        m_Pos += aNum;
        if (currentPos > max_size())
            throw std::bad_alloc();
       
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
        //++m_FreeData;
        new(p) U(std::forward<Args>(args)...);
    };

    template<class U>
    void destroy(U *p)
    {
        p->~U();
    }
    
    std::size_t Reserved() const
    {
        return m_MaxSize;
    }

    std::size_t max_size() const
    {
        return m_MaxSize;
    }

private:
    pointer     m_Data      = nullptr;
    pointer     m_FreeData = nullptr;

    std::size_t Constructed;

    std::size_t m_MaxSize = 2 * TNum;
    std::size_t m_Pos = 0;

    void InitMemory()
    {
        m_Data = (pointer)std::malloc(m_MaxSize * sizeof(T));
        m_Pos = 0;
    }
};
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
        //m_Data = (pointer)std::malloc(kMaxSize * sizeof(T));
    };
    ~MapAllocator()
    {
//          if (m_Data != nullptr) {
//              std::free(m_Data);
//              m_Data = nullptr;
//              
//          }
    };

    template<typename U>
    MapAllocator(const MapAllocator<U>& aRhs)
    {    
        //m_Data = (T*)aRhs.m_Data;
        //InitMemory();
        //memcpy(m_Data, aRhs.m_Data, __min(aRhs.max_size(), max_size()));


        //Похорошему перенести указатели
        //return logging_allocator<U>();
    }

    T *allocate(std::size_t n)
    {
        //std::cout << "allocate: [n = " << n << "]" << std::endl;
//         if (m_Data == nullptr) {
//             InitMemory();
//         }
        const std::size_t sizeObj = sizeof(T);
        std::size_t currentPos = m_Pos;
        m_Pos += n;
        m_MaxCurrentPos = currentPos > m_MaxCurrentPos ? currentPos : m_MaxCurrentPos;
        if (m_Pos > max_size())
            throw std::bad_alloc();
        return (T*)&m_Data[currentPos];
    }

    void deallocate(T *p, std::size_t n)
    {
        //std::cout << "deallocate: [n  = " << n << "] " << std::endl;
        if (n > m_Pos) {
            m_Pos = 0;
            return;
        }
        m_Pos -= n;
        //std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
        //std::cout << "construct" << std::endl;
        new(p) U(std::forward<Args>(args)...);
    };

    void destroy(T *p)
    {
        //std::cout << "destroy" << std::endl;
        //memset(p, 0xff, sizeof(T));
        p->~T();
    }
    std::size_t max_size() const
    {
        return m_MaxSize;
    }

    //pointer m_Data = nullptr;
    std::array<value_type, kMaxSize + 1> m_Data;
private:

    const std::size_t m_MaxSize = kMaxSize + 1;
    //pointer m_CurrentPtr = nullptr;
    std::size_t m_Pos = 0;
    std::size_t m_MaxCurrentPos = 0;
    //pointer m_CurrentPos = nullptr;
    void InitMemory()
    {
        m_Data = (pointer)std::malloc(m_MaxSize * sizeof(T));
        m_Pos = 0;
    }

};

//#pragma once
//#include <iostream>
//template<typename T, std::size_t MaxSize>
//struct logging_allocator
//{
//    using value_type = T;
//
//    using pointer = T * ;
//    using const_pointer = const T*;
//    using reference = T & ;
//    using const_reference = const T&;
//
//    template<typename U>
//    struct rebind
//    {
//        using other = logging_allocator<U, MaxSize>;
//    };
//
//    logging_allocator()
//    {
//        int stop1 = 0;
//    };
//    ~logging_allocator() = default;
//
//    template<typename U, std::size_t MaxSize2>
//    logging_allocator(const logging_allocator<U, MaxSize2>&)
//    {
//        int stop1 = 0;
//    }
//
//    T *allocate(std::size_t n)
//    {
//        std::cout << "allocate: [n = " << n << "]" << std::endl;
////         auto p = std::malloc(n * sizeof(T));
////         if (!p)
////             throw std::bad_alloc();
//        const std::size_t currentPos = m_Pos;
//        m_Pos += n;
//        return &m_Data[currentPos];
//    }
//
//    void deallocate(T *p, std::size_t n)
//    {
//        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
//        --m_Pos;
//        //std::free(p);
//    }
//
//    template<typename U, typename ...Args>
//    void construct(U *p, Args &&...args)
//    {
//        std::cout << "construct" << std::endl;
//        new(p) U(std::forward<Args>(args)...);
//    };
//
//    void destroy(T *p)
//    {
//        std::cout << "destroy" << std::endl;
//        p->~T();
//    }
//
//    std::size_t max_size() const
//    {
//        return MaxSize;
//    }
//
//private:
//
//};


///
//#pragma once
//template<typename T, std::size_t MaxSize>
//struct logging_allocator
//{
//    using value_type = T;
//
//    using pointer = T * ;
//    using const_pointer = const T*;
//    using reference = T & ;
//    using const_reference = const T&;
//
//    template<typename U>
//    struct rebind
//    {
//        using other = logging_allocator<U, MaxSize>;
//    };
//
//    logging_allocator()
//    {
//        int stop1 = 0;
//    };
//    ~logging_allocator() = default;
//
//    template<typename U, std::size_t MaxSize2>
//    logging_allocator(const logging_allocator<U, MaxSize2>&)
//    {
//        int stop1 = 0;
//    }
//
//    T *allocate(std::size_t n)
//    {
//        std::cout << "allocate: [n = " << n << "]" << std::endl;
//        auto p = std::malloc(n * sizeof(T));
//        if (!p)
//            throw std::bad_alloc();
//        return reinterpret_cast<T *>(p);
//    }
//
//    void deallocate(T *p, std::size_t n)
//    {
//        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
//
//        std::free(p);
//    }
//
//    template<typename U, typename ...Args>
//    void construct(U *p, Args &&...args)
//    {
//        std::cout << "construct" << std::endl;
//        new(p) U(std::forward<Args>(args)...);
//    };
//
//    void destroy(T *p)
//    {
//        std::cout << "destroy" << std::endl;
//        p->~T();
//    }
//
//    std::size_t max_size() const
//    {
//        return MaxSize;
//    }
//};
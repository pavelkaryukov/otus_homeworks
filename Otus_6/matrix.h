#pragma once
#include <cstddef>
#include <iostream>  
#include <map>
#include <boost/format.hpp>
#include <stdexcept>
//сделай переопределение оператора = , если значение в нем = default = erase элемент

template<class TValue, TValue _DefaultValue = TValue(-1)>
class TLine {
#pragma region Usings
    using index_t = std::uint64_t;
    using map_t = std::map<index_t, TValue>;
#pragma endregion

#pragma region Controller   
    class Controller {
        map_t*  m_Map   = nullptr;
        index_t m_Index; 
        TValue  m_Value;

    public:
        TValue Get() const {
            auto iter = m_Map->find(m_Index);
            return iter != m_Map->end() ? iter->second : _DefaultValue;
        }

#pragma region Constructors
        Controller() = delete;
        
        Controller(const index_t aIndex, map_t* aMap) : m_Index(aIndex), m_Map(aMap), m_Value(_DefaultValue){};
      
        Controller(const Controller& aRhs) : m_Value(aRhs.m_Value), m_Map(aRhs.m_Map), m_Index(aRhs.m_Index){};
#pragma endregion

        Controller& operator=(const TValue aValue) {
            m_Value = aValue;
            auto iter = m_Map->find(m_Index);
            if (aValue == _DefaultValue) {
                if (iter != m_Map->end())
                    m_Map->erase(iter);
                return *this;
            }
            (*m_Map)[m_Index] = m_Value;
            return *this;
        }

#pragma region CompareOperators
        bool operator==(const TValue aValue) const {
            return Get() == aValue;
        }

        bool operator==(const Controller aRhs) const {
            return Get() == aRhs.m_Value;
        }

        bool operator!=(const TValue aValue) const {
            return Get() != aValue;
        }

        bool operator!=(const Controller aRhs) const {
            return Get() != aRhs.m_Value;
        }

        Controller& operator++() {
            *this = Get() + 1;
            return *this;// сделать конструктор копирования
        }

        Controller operator++(int) {
            Controller controller = Controller(*this);
            *this = Get() + 1;
            return controller;// сделать конструктор копирования
        }
    };
#pragma endregion
#pragma endregion

    map_t m_MatrixMap;
public:
    TLine() {}

    std::size_t Size() const {
        return m_MatrixMap.size();
    }

    Controller  operator[](const index_t aIndex)  {
        return Controller(aIndex, &m_MatrixMap);
    }
};
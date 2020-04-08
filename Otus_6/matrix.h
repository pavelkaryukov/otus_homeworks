#pragma once
#include <cstddef>
#include <iostream>  
#include <map>
#include <boost/format.hpp>
#include <stdexcept>
#include <type_traits>
template<class TValue, TValue TDefaultValue, class = typename std::enable_if_t<std::is_integral_v<TValue>>>
class Matrix{
    using index_t = std::uint64_t;
    using pair_t  = std::pair<std::uint64_t, std::uint64_t>;
    using map_t   = std::map<pair_t, TValue>;

    #pragma region ClassInternalMatrix
    class InternalMatrix {

    #pragma region Controller   
        class Controller {
            map_t*  m_CMap = nullptr;
            pair_t  m_CIndex;
            TValue  m_CValue;

        public:
            TValue Get() const {
                auto iter = m_CMap->find(m_CIndex);
                return iter != m_CMap->end() ? iter->second : TDefaultValue;
            }

            Controller() = delete;

            Controller(const pair_t aIndex, map_t* aMap) : m_CIndex(aIndex), m_CMap(aMap), m_CValue(TDefaultValue) {};

            Controller(const Controller& aRhs) : m_CValue(aRhs.m_CValue), m_CMap(aRhs.m_CMap), m_CIndex(aRhs.m_CIndex) {};

            Controller& operator=(const TValue aValue) {
                m_CValue = aValue;
                auto iter = m_CMap->find(m_CIndex);
                if (aValue == TDefaultValue) {
                    if (iter != m_CMap->end())
                        m_CMap->erase(iter);
                    return *this;
                }
                (*m_CMap)[m_CIndex] = m_CValue;
                return *this;
            }

            bool operator==(const TValue aValue) const {
                return Get() == aValue;
            }

            bool operator==(const Controller aRhs) const {
                return Get() == aRhs.m_CValue;
            }

            bool operator!=(const TValue aValue) const {
                return Get() != aValue;
            }

            bool operator!=(const Controller aRhs) const {
                return Get() != aRhs.m_CValue;
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

            friend std::ostream& operator<<(std::ostream& aStream, const Controller& aController) {
                aStream << aController.Get();
                return aStream;
            }
        };
#pragma endregion

        map_t m_MatrixMap;
        index_t m_Index = 0;

        using iter_t =  class map_t::const_iterator;
        struct InternalIterator: public std::iterator<std::forward_iterator_tag, iter_t> {
            using tuple_t = std::tuple<index_t, index_t, TValue>;
            
            InternalIterator() {};
            
            InternalIterator(iter_t&& aMapIter) {
                m_MapIter = std::move(aMapIter);
            }

            InternalIterator(iter_t& aMapIter) {
                m_MapIter = aMapIter;
            }

            InternalIterator(const InternalIterator& aIter) {
                m_MapIter = aIter->m_MapIter;
            }

            InternalIterator& operator++() {
                ++m_MapIter;
                return *this;
            }

            InternalIterator& operator--() {
                --m_MapIter;
                return *this;
            }

            InternalIterator operator++(int) {
                auto iter = *this;
                ++(*this);
                return iter;
            }

            InternalIterator operator--(int) {
                auto iter = *this;
                --(*this);
                return iter;

            }

            bool operator==(const InternalIterator& aRhs) {
                return m_MapIter == aRhs.m_MapIter;
            }

            bool operator!=(const InternalIterator& aRhs) {
                return m_MapIter != aRhs.m_MapIter;
            }
            
            tuple_t operator*() const { 
                auto iterPtr = (iter_t*)this;
                return tuple_t((*iterPtr)->first.first, (*iterPtr)->first.second, (*iterPtr)->second);                
            }

            friend std::ostream& operator<<(std::ostream& aStream, const InternalIterator& aIter) {
                const auto[x, y, v] = *aIter;
                aStream << boost::format("[%1%][%2%]=%3%") % x % y % v;
                return aStream;
            }
        private:
            iter_t m_MapIter;
        };
    public:
        InternalMatrix() = default;

        std::size_t Size() const {
            return m_MatrixMap.size();
        }

        void SetIndex(const index_t aIndex) {
            m_Index = aIndex;
        }

        Controller  operator[](const index_t aIndex) {
            return Controller({ m_Index, aIndex }, &m_MatrixMap);
        }

        InternalIterator begin() {
            return InternalIterator(m_MatrixMap.begin());
        }

        InternalIterator end() {
            return InternalIterator(m_MatrixMap.end());
        }

        void clear() {
            m_MatrixMap.clear();
            m_Index = 0;
        }
    };
#pragma endregion

    InternalMatrix m_Matrix;
public:
    InternalMatrix& operator[](const index_t aIndex){
        m_Matrix.SetIndex(aIndex);
        return  m_Matrix;
    }

    std::size_t size() const {
        return m_Matrix.Size();
    }

    bool empty() const {
        return size() == 0;
    }

    auto begin() {
        return m_Matrix.begin();
    }

    auto end() {
        return m_Matrix.end();
    }

    void clear() {
        return m_Matrix.clear();
    }
};

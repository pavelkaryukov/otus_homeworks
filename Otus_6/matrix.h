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
                return *this;// ������� ����������� �����������
            }

            Controller operator++(int) {
                Controller controller = Controller(*this);
                *this = Get() + 1;
                return controller;// ������� ����������� �����������
            }
        };
#pragma endregion

        map_t m_MatrixMap;
        index_t m_Index = 0;

        //�������������� �� map iterator - ��������������� ���� ����� � ������
        struct InternalIterator : public map_t::iterator {
            using tuple_t = std::tuple<index_t, index_t, TValue>;
           
            tuple_t operator*() const { // ������� ������ ������������� ?:)
                map_t::const_iterator* iterPtr = (map_t::const_iterator*)this;
                auto test = tuple_t((*iterPtr)->first.first, (*iterPtr)->first.second, (*iterPtr)->second);
                return test;
            }
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

        auto begin() {
            InternalIterator iter = { m_MatrixMap.begin() };
            auto test = *iter;
            ++iter;
            //index_t x, y;
            //TValue v;
            //std::tie(x, y, v) = iter;
            //auto [a,b,c] = iter;

            return 0;//internalIterator(m_MatrixMap.begin());
            //auto matr_iter = m_MatrixMap.begin();
            //return m_MatrixMap.begin();
        }


        auto end() {
            InternalIterator iter = { m_MatrixMap.end() };
            //auto iter = InternalIterator<map_t::iterator>(m_MatrixMap.end());
            return 0;//internalIterator(m_MatrixMap.end());
            //return m_MatrixMap.end();
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

    void IteratorTest() {
        auto iter1  = m_Matrix.begin();
        auto iter2  = m_Matrix.end();
        int stop1 = 0;
        //for (auto a : m_Matrix) {
        //    int stop1 = 0;
        //}
    }
};

#pragma once
#include "big_number.h"
#include <boost/format.hpp>
#include <cstddef>
#include <iostream>  
#include <map>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

/*! \mainpage Otus_6 (Matrix)
 *
 * \r\n  Ѕесконечна€ дмумерна€ матрица
 *
 */
 /*! Matrix class */
/**
* \brief  2-мерна€ разр€женна€ бесконечна€ матрица заполненна€ значени€ми по-умолчанию.
* \details хран€тс€ только зан€тые элементы. ѕрисвоение €чейки в значение по-умолчанию освобождает €чейку.
* \tparam TValue - тип значений в €чейках матрицы
* \tparam TDefaultValue - значение €чейки по умолчанию
*/
template<class TValue, TValue TDefaultValue, class = typename std::enable_if_t<std::is_integral_v<TValue>>>
class Matrix{
    using index_t = BigNumber;
    using pair_t  = std::pair<index_t, index_t>;
    using map_t   = std::map<pair_t, TValue>;
    std::shared_ptr<map_t> m_MatrixMap;
    #pragma region RowClass
    class Row {
        Row() {}
    #pragma region CellClass   
        class Cell {
            friend class Row;
            map_t*  m_CMap = nullptr;
            pair_t  m_CIndex;
        public:
            TValue Get() const {
                auto iter = m_CMap->find(m_CIndex);
                return iter != m_CMap->end() ? iter->second : TDefaultValue;
            }

            Cell& operator=(const TValue& aValue) {
                if (aValue == TDefaultValue) {
                    auto iter = m_CMap->find(m_CIndex);
                    if (iter != m_CMap->end())
                        m_CMap->erase(iter);
                    return *this;
                }
                (*m_CMap)[m_CIndex] = aValue;
                auto& test = (*m_CMap)[m_CIndex];
                return *this;
            }

            bool operator==(const Cell& aRhs) const {
                return Get() == aRhs.Get();
            }

            bool operator!=(const Cell& aRhs) const {
                return !(*this == aRhs);
            }

            friend bool operator==(const Cell& aCell , const TValue aValue) {
                return aCell.Get() == aValue;
            }
            
            friend bool operator==(const TValue aValue, const Cell& aCell) {
                return aCell == aValue;
            }

            friend bool operator!=(const Cell& aCell, const TValue aValue){
                return !(aCell == aValue);
            }

            friend bool operator!=(const TValue aValue, const Cell& aCell) {
                return aCell != aValue;
            }

            operator TValue() const {
                return Get();
            }

            Cell& operator+=(const TValue aNum) {
                Get() += aNum;
                return *this;
            }

            Cell& operator-=(const TValue aNum) {
                Get() -= aNum;
                return *this;
            }

            friend TValue operator+(const Cell& aCell, const TValue aNum) {
                return aCell.Get() + aNum;
            }

            friend TValue operator+(const TValue aNum, const Cell& aCell) {
                return aCell.Get() + aNum;
            }

            friend TValue operator+(const Cell& aCell1, const Cell& aCell2) {
                return aCell1.Get() + aCell2.Get();
            }

            friend TValue operator-(const Cell& aCell, const TValue aNum) {
                return aCell.Get() - aNum;
            }

            friend TValue operator-(const TValue aNum, const Cell& aCell) {
                return aCell.Get() - aNum;
            }

            friend TValue operator-(const Cell& aCell1, const Cell& aCell2) {
                return aCell1.Get() - aCell2.Get();
            }

            Cell& operator++() {
                *this = Get() + 1;
                return *this;
            }

            TValue operator++(int) {
                auto res = Get();
                ++*this;
                return res;
            }

            Cell& operator--() {
                *this = Get() - 1;
                return *this;
            }

            TValue operator--(int) {
                auto res = Get();
                --*this;
                return res;
            }

            friend std::ostream& operator<<(std::ostream& aStream, const Cell& aController) {
                aStream << aController.Get();
                return aStream;
            }
            private:
                Cell() = default;

                Cell(const pair_t aIndex, map_t* aMap) : m_CIndex(aIndex), m_CMap(aMap) {
                };

                Cell(const Cell& aRhs) : m_CMap(aRhs.m_CMap), m_CIndex(aRhs.m_CIndex) {};

                //–еализаци€ через этот метод не позвол€ет контролировать переход сквозь TDefaultValue у операторов ++ --
                /*TValue& Get() {
                    auto iter = m_CMap->find(m_CIndex);
                    if (iter == m_CMap->end()) {
                        auto[insIter, insRes] = m_CMap->insert({ m_CIndex, TDefaultValue });
                        if (!insRes)
                            throw std::logic_error("TValue& Get(), can\'t insert element in  m_CMap");
                        iter = insIter;
                    }
                    return iter->second;
                }*/
        };
#pragma endregion
        index_t m_Index = 0;

        using iter_t =  class map_t::const_iterator;
        struct InternalIterator : public std::iterator<std::forward_iterator_tag, iter_t> {
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

            bool operator==(const InternalIterator& aRhs) const {
                return m_MapIter == aRhs.m_MapIter;
            }

            bool operator!=(const InternalIterator& aRhs) const {
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

        std::shared_ptr<map_t> m_MapPtr = std::make_shared<map_t>();
    public:
        Row(std::shared_ptr<map_t> aMap){
            m_MapPtr = aMap;
        }

        std::size_t Size() const {
            return m_MapPtr->size();
        }

        void SetIndex(const index_t aIndex) {
            m_Index = aIndex;
        }

        Cell operator[](const index_t aIndex) {
            return Cell({ m_Index, aIndex }, &(*m_MapPtr));
        }

        InternalIterator begin() {
            return InternalIterator(m_MapPtr->begin());
        }

        InternalIterator end() {
            return InternalIterator(m_MapPtr->end());
        }

        InternalIterator begin() const {
            return InternalIterator(m_MapPtr->cbegin());
        }

        InternalIterator end() const {
            return InternalIterator(m_MapPtr->cend());
        }

        void clear() {
            m_MatrixMap.clear();
            m_Index = 0;
        }
    };
#pragma endregion

    Row m_Row = {nullptr};
public:

    Matrix() {
        m_MatrixMap = std::make_shared<map_t>();
        m_Row = { m_MatrixMap };
    }
    /**
    * \brief  оператор [] возращает внутреннюю матрицу.
    * \details повторный вызов оператора [] даст доступ к €чейке матрицы
    * \param[in] aIndex - номер строки матрицы
    * \return - ссылка на  внутреннюю матрицу
    */
    Row operator[](const index_t aIndex){
        m_Row.SetIndex(aIndex);
        return  m_Row;
    }

    /**
    * \brief  размер матрицы.
    * \details вернет количество €чеек с не дефолтным значением
    * \return количество €чеек с не дефолтным значением
    */
    std::size_t size() const {
        return m_Row.Size();
    }

    /**
    * \brief  матрица разр€жена.
    * \return вернет true если все €чейки в матрицы имеют значение по-умолчанию
    */
    bool empty() const {
        return size() == 0;
    }

    /**
    * \brief  итератор на начало.
    */
    auto begin() {
        return m_Row.begin();
    }

    /**
    * \brief  итератор на конец.
    */
    auto end() {
        return m_Row.end();
    }

    /**
    * \brief  итератор на начало.
    */
    auto begin() const {
        return m_Row.begin();
    }

    /**
    * \brief  итератор на конец.
    */
    auto end() const {
        return m_Row.end();
    }

    /**
    * \brief  сбросить сост€ние матрицы.
    * \derails всем €чейкам будет присвоено значение по-умолчанию
    */
    void clear() {
        return m_Row.clear();
    }
};

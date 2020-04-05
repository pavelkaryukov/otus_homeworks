#pragma once
#include <cstddef>
#include <iostream>  
#include <map>
#include <boost/format.hpp>
#include <stdexcept>
//������ ��������������� ��������� = , ���� �������� � ��� = default = erase �������

template<class TValue, TValue _DefaultValue = TValue(-1)>
class Matrix {
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
                return iter != m_CMap->end() ? iter->second : _DefaultValue;
            }

#pragma region Constructors
            Controller() = delete;

            Controller(const pair_t aIndex, map_t* aMap) : m_CIndex(aIndex), m_CMap(aMap), m_CValue(_DefaultValue) {};

            Controller(const Controller& aRhs) : m_CValue(aRhs.m_CValue), m_CMap(aRhs.m_CMap), m_CIndex(aRhs.m_CIndex) {};
#pragma endregion

            Controller& operator=(const TValue aValue) {
                m_CValue = aValue;
                auto iter = m_CMap->find(m_CIndex);
                if (aValue == _DefaultValue) {
                    if (iter != m_CMap->end())
                        m_CMap->erase(iter);
                    return *this;
                }
                (*m_CMap)[m_CIndex] = m_CValue;
                return *this;
            }

#pragma region CompareOperators
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
#pragma endregion
        map_t m_MatrixMap;
        index_t m_Index = 0;
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
};

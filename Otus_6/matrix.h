#pragma once
#include <cstddef>
#include <iostream>  
#include <map>
#include <boost/format.hpp>
#include <stdexcept>
//сделай переопределение оператора = , если значение в нем = default = erase элемент

template<class TValue, TValue DefaultValue = TValue(-1)>
class TMatrix {
    using index_t = std::uint64_t;
    TValue m_Value = DefaultValue;
public:
    TMatrix() {}

//     TValue  operator[](index_t aIndex) {
//         return m_Value;
//     }

    const TValue&  operator[](index_t) const {
        std::cout << "ReadOperator\r\n";
        int stop1 = 0;
        return m_Value;
    }

    TValue&  operator[](index_t)  {
        std::cout << "WriteOperator\r\n";
        int stop1 = 0;
        return m_Value;
    }
};
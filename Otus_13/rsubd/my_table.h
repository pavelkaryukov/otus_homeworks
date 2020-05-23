#pragma once
#include "rsubd/cortej.h"    
#include "rsubd/code_result.h"
#include <set>

class MyTable {
    using iter_t = std::set<Cortej>::iterator;
public:

    std::pair<ResultCode, iter_t> Add(Cortej aCortej) {
        if (m_Table.find(aCortej) != m_Table.end())
            return { { ResultCode::Codes::Exist}, m_Table.end() };

        auto [iter, res] = m_Table.insert(aCortej);
        if (!res)
            return { { ResultCode::Codes::CantInsert }, m_Table.end() };

        return { { ResultCode::Codes::Succes },  iter};
    }
    
   /* ResultCode Erase(Cortej&& aCortej) {
        if (m_Table.find(aCortej) == m_Table.end())
            return ResultCode{ ResultCode::Codes::NotExist };

        auto res = m_Table.erase(aCortej);

        if (res == 1)
            return ResultCode{ ResultCode::Codes::Succes };                                          
        else                                             
            return ResultCode{ ResultCode::Codes::Error  };
    }*/

    std::size_t Size() const {
        return m_Table.size();
    }

    void Clear() {
        m_Table.clear();
    }

    bool MarkDuplicate(const Cortej& aCortej) {
        auto iter = m_Table.find(aCortej);
        if (iter == m_Table.end())
            return false;

        iter->HaveIdent = true;
        aCortej.HaveIdent = true;
    }

    auto begin() const {
        return m_Table.begin();
    }

    auto end() const {
        return m_Table.end();
    }

    std::pair<bool, iter_t> Find(const Cortej& aCortej) const {
        auto iter = m_Table.find(aCortej);
        if (iter == m_Table.end())
            return { false, end() };
        return { true, iter };
    }
private:
    std::set<Cortej> m_Table;
};

#pragma once
#include "rsubd/my_table.h"
#include "rsubd/code_result.h"
#include <unordered_map>

class RSUBD {
public:

    CodeResults Insert(const std::string aTableName, const Cortej&& aCortej) {
        auto [res, table] = GetTable(aTableName);
        if (res.IsSucces())
            return res;

        auto [code, iter] = table->Add(aCortej);

        if (!code.IsSucces())
            return res;

        GetAnother(table)->MarkDuplicate(*iter);// Взведет  флажки у обоих элементов, если id идетичен       
        return res;
    }

private:
    std::pair< ResultCode, MyTable*> GetTable(const std::string& aName) {
        if (aName == "A")
            return { { ResultCode::Code::Succes}, &m_TableA };
        if (aName == "B")
            return { { ResultCode::Code::Succes}, &m_TableB };
        return
            return{ { ResultCode::Code::TableNotExist }, nullptr };
    }

    MyTable* GetAnother(MyTable* aTablePtr) {
        if (m_TableA == aTablePtr)
            return &m_TableB;
        else
            return &m_TableA;
    }

    //INTERSECTION - выдаст все пересекающиеся
    //SYMMETRIC_DIFFERENCE - все не пересеющиеся
    //std::unordered_map<std::string, MyTable> m_Tables;
    MyTable m_TableA;
    MyTable m_TableB;
};
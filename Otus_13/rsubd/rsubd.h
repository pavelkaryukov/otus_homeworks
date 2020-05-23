#pragma once
#include <boost/format.hpp>
#include "rsubd/my_table.h"
#include "rsubd/code_result.h" //TODO:: стереть

class RSUBD {
public:
    ResultCode Insert(const std::string aTableName, const Cortej&& aCortej) {
        auto [res, table] = GetTable(aTableName);
        if (!res.IsSucces())
            return res;

        auto [insertRes, iter] = table->Add(aCortej);

        if (!insertRes.IsSucces())
            return insertRes;

        GetAnother(table)->MarkDuplicate(*iter);// Взведет  флажки у обоих элементов, если id идетичен       
        return res;
    }

    ResultCode Truncate(const std::string aTableName) {
        auto[res, table] = GetTable(aTableName);
        if (!res.IsSucces())
            return res;

        table->Clear();
        return { ResultCode::Codes::Succes };
    }

    std::string Intersection() const { 
        std::string str;
        for (auto& elemA : m_TableA) {
            if (!elemA.HaveIdent)
                continue;
            auto [res, iterB]= m_TableB.Find(elemA);
            if (!res || iterB == m_TableB.end())
                continue;
            str += boost::str(boost::format("%1%,%2%,%3%\n") % elemA.Data.id % elemA.Data.name % iterB->Data.name);
        }
        return str;
    }

    std::string SimmetricDifference() const {
        std::string res;
        FillStrSymmetricDiff(res, m_TableA, 'A');
        FillStrSymmetricDiff(res, m_TableB, 'B');
        return res;
    }

private:
    std::pair<ResultCode, MyTable*> GetTable(const std::string& aName) {
        if (aName == "A")
            return { { ResultCode::Codes::Succes}, &m_TableA };
        
        if (aName == "B")
            return { { ResultCode::Codes::Succes}, &m_TableB };
        
        return { { ResultCode::Codes::TableNotExist }, nullptr };
    }

    MyTable* GetAnother(MyTable* aTablePtr) {
        if (&m_TableA == aTablePtr)
            return &m_TableB;
        else
            return &m_TableA;
    }

    void FillStrSymmetricDiff(std::string& aStr, const MyTable& aTable, const char aName) const {
        for (const auto& elem : aTable) {
            if (elem.HaveIdent)
                continue;
            if (aName == 'A')
                aStr += boost::str(boost::format("%1%,%2%,\n") % elem.Data.id % elem.Data.name);
            else
                aStr += boost::str(boost::format("%1%,,%2%\n") % elem.Data.id % elem.Data.name);
        }
    }

    MyTable m_TableA;
    MyTable m_TableB;
};
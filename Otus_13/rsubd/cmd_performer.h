#pragma once
#include "rsubd/rsubd.h"
#include <boost/tokenizer.hpp>

class CmdPerformer {
    using separator_t  = boost::char_separator<char>;
    using tokenizer_t = boost::tokenizer<separator_t>;

public:
    CmdPerformer() = default;
    std::string ProcessCommand(const std::string& aCmd) {
        tokenizer_t tokenizer(aCmd, m_Separator);
        std::vector<std::string> tokens(tokenizer.begin(), tokenizer.end());
        if (tokens.empty())
            return "";

        return ProcessCommand(tokens);
    }

private:
    std::string ProcessCommand(std::vector<std::string>& aTokens) {
        if (aTokens.empty())
            return "";
        auto cmd = aTokens[0];
        aTokens.erase(aTokens.begin());

        if (cmd == "INSERT")
            return ProcessCmd_Insert(aTokens);
        
        if (cmd == "TRUNCATE")
            return ProcessCmd_Truncate(aTokens);

        if (cmd == "INTERSECTION")
            return ProcessCmd_Intersection();

        if (cmd == "SYMMETRIC_DIFFERENCE")
            return ProcessCmd_SymmetricDiffernce();
        
        return boost::str(boost::format("ERROR: Unknown command [%1%]") % cmd);
    }

    std::string ProcessCmd_Insert(std::vector<std::string>& aTokens) {
        const std::size_t minSize = 2;
        if (aTokens.size() < minSize)
            return "ERROR: Нет id элемента для вставки";
        int id = 0;
        
        try {
            id = std::stoi(aTokens[1]);
        }
        catch (std::exception& exc) {
            return boost::str(boost::format("ERROR: не корректный ID = [%1%]") % aTokens[1]);
        }
        
        if (id < 0)
            return boost::str(boost::format("ERROR: не корректный ID = [%1%]")%aTokens[1]);
        
        std::string value = (aTokens.size() >= 3) ? aTokens[2] : "";
        auto res = m_Rsubd.Insert(aTokens[0], { {id, value} });
        if (!res.IsSucces()) 
            return boost::str(boost::format("ERROR: [%1%]") % res.What());

        return "OK";
    }

    std::string ProcessCmd_Truncate(std::vector<std::string>& aTokens) {
        if (aTokens.empty())
            return "ERROR: Не указана таблица для отчистки";

        auto res = m_Rsubd.Truncate(aTokens[0]);
        if (!res.IsSucces())            
            return boost::str(boost::format("ERROR: [%1%]") % res.What());

        return "OK";
    }

    std::string ProcessCmd_Intersection() {
        auto str = m_Rsubd.Intersection();
        return str + "OK";
    }

    std::string ProcessCmd_SymmetricDiffernce() {
        auto str = m_Rsubd.SimmetricDifference();     
        return str + "OK";
    }

    separator_t m_Separator = separator_t(" \r\n");
    RSUBD m_Rsubd;
};

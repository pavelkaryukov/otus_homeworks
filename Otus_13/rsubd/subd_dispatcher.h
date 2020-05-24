#pragma once
#include "rsubd/rsubd.h"
#include <boost/tokenizer.hpp>

class SubdDispatcher {
    using separator_t  = boost::char_separator<char>;
    using tokenizer_t = boost::tokenizer<separator_t>;

public:
    SubdDispatcher() = default;
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
            return ProcessCmdINSERT(aTokens);
        
        if (cmd == "TRUNCATE")
            return "Command not IMPLEMENTED";

        if (cmd == "INTERSECTION")
            return "Command not IMPLEMENTED";

        if (cmd == "SYMMETRIC_DIFFERENCE")
            return "Command not IMPLEMENTED";
    }

    std::string ProcessCmdINSERT(std::vector<std::string>& aTokens) {
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

    separator_t m_Separator = separator_t(" \r\n");
    RSUBD m_Rsubd;
};

#pragma once
#include <string>
struct RawData {
    int id;
    std::string name;

    bool operator<(const RawData& aRhs) const {
        return id < aRhs.id;
    }
};

struct Cortej  {
    Cortej(RawData&& aData) : Data(aData), HaveIdent(false) {}

    RawData Data;
    mutable bool HaveIdent = false;

    bool operator<(const Cortej& aRhs) const {
        return Data < aRhs.Data;
    }

private:
    Cortej() = default;
};


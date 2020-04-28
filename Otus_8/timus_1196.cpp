#include <list>
#include <functional>
#include <cctype>
#include <map>
#include <vector>
#include <string>
#include <iostream>
enum class ResCode {
    Full,
    NeadMoreData,
    Error,
    Unsorted
};

template<class T>
struct MyMap {
    using map_t = std::map<T, std::size_t>;

    ResCode Add(const T aNum){
        m_Map[aNum] += 1;
        if (aNum < m_Last)
            m_Sorted = false;
        m_Last = aNum;
        ++m_Counter;
        return m_ExpectedSize == m_Counter ? ResCode::Full : ResCode::NeadMoreData;
    }

    std::size_t Size() const  {
        return m_Counter;
    }

    void Clear() {
        m_Map.clear();
        m_Counter = 0;
        m_ExpectedSize = 0;
        m_Sorted = true;
        m_Last = {};
    }

    std::size_t operator[](const T aIndex) const {
        auto iter = m_Map.find(aIndex);
        return iter != m_Map.end() ? iter->second : 0;
    }
    
    const map_t& GetMap() const {
        return m_Map;
    }

    void SetExpected(const std::size_t aSize) {
        m_ExpectedSize = aSize;
    }

    std::size_t ExpectedSize() const {
        return m_ExpectedSize;
    }

    bool IsFull() const {
        return m_ExpectedSize == m_Counter;
    }

    bool IsSorted() const {
        return m_Sorted;
    }
private:
    map_t m_Map;
    std::size_t m_ExpectedSize = 0;
    std::size_t m_Counter = 0;
    T m_Last {};
    bool m_Sorted = true;
};


bool IsValid(const std::size_t aNum, const std::size_t aLeft, const std::size_t aRight) {
    if (aRight < aLeft)
        throw std::logic_error("method IsValid: LeftBorder More RightBorder");
    return aNum >= aLeft && aNum <= aRight;
}

bool IsValidSizeTeacher(const std::size_t aNum) {
    return IsValid(aNum, 1, 15'000);
}

bool IsValidSizeStudent(const std::size_t aNum) {
    return IsValid(aNum, 1, 1'000'000);
}

template<class T>
ResCode FillYearList(MyMap<T>& aYearList, const std::size_t aNum, std::function<bool(const std::size_t)> aIsValid) {
    if (aIsValid == nullptr)
        throw std::logic_error("method FillYearList: aIsValid == nullptr");
    
    if (aYearList.ExpectedSize() == 0) {
        if (!aIsValid(aNum))
            return ResCode::Error;
        aYearList.SetExpected(aNum);
        return ResCode::NeadMoreData;
    }


    if (aYearList.Size() < aYearList.ExpectedSize()) {
        if (!IsValid(aNum, 1, 1'000'000'000))
            return ResCode::Error;
        return aYearList.Add(aNum);
    }

    return ResCode::Error;
}

template<class T>
std::size_t RepeatedNumbersCount2(const MyMap<T>& aTeacher, const MyMap<T>& aStudent) {
    std::size_t count = 0;
    for (auto& elem : aTeacher.GetMap()) {
        auto weight = aTeacher[elem.first] * elem.second;
        count += weight;
    }
    return count;
}

template<class T>
std::size_t RepeatedNumbersCount(const MyMap<T>& aTeacher, const MyMap<T>& aStudent) {
    std::size_t count = 0;
    for (auto& elem : aStudent.GetMap()) {
        if (aTeacher[elem.first]!=0)
        count += elem.second;
    }
    return count;
}

int main() {
    MyMap<std::size_t> condTeacher, condStudent;
    std::size_t number = 0;
    bool teacher = true;
    auto Clear = [&]() {
        condTeacher.Clear();
        condStudent.Clear();
        number      = 0;
    };

    while (std::cin >> number) {
        ResCode res = ResCode::Error;
        if (condTeacher.ExpectedSize() == 0 || !condTeacher.IsFull()) {
            res = FillYearList<std::size_t>(condTeacher, number, IsValidSizeTeacher);
        } else if (condStudent.ExpectedSize() == 0 || !condStudent.IsFull()) {
            res = FillYearList<std::size_t>(condStudent, number, IsValidSizeStudent);
            if (res == ResCode::Full) {
                std::cout << RepeatedNumbersCount<std::size_t>(condTeacher, condStudent);
                Clear();
                continue;
            }
        }
        if (res == ResCode::Error || !condTeacher.IsSorted())
            Clear();
    }
    return 0;
}

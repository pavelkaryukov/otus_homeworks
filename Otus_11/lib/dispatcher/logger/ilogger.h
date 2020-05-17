#pragma once
#include <cctype>
/**
* \brief  ��������� ������� ��������
*/
class ILogger {
    /**
    * \brief  ���������� ������������ ������ � ������
    */
    struct Stat {
        std::size_t Commands = 0;
        std::size_t Bulks = 0;

        /**
        * \brief  �������� ������ � ���������� �������
        * \details ���-�� ������ ���������� �� 1, ��� �� ������ �� aCommands
        * \param[in] aCommands - ���-�� ����������� ������
        */
        void Add(const std::size_t aCommands) {
            Commands += aCommands;
            Bulks += 1;
        }
    };
public:
    /**
    * \brief  ���������� ����
    * \details � ����������� �� ���������� ������� ����� ����������� ���������� ����
    * \param[in] aStr - ��� ���������� � ���-�� ��������� ������
    * \param[in] aCommands - ���-�� ������, �����������
    */
    void Save(std::string aStr, const std::size_t aCommands) {
        m_Statistic.Add(aCommands);
        SaveLog(aStr);
    }

    /**
    * \brief  ������������ �������� �������
    * \details ������������ �������� �������, ���������� �������� ������ ���� �������������� �� �����
    */
    virtual void Exit() = 0;

    virtual ~ILogger() {}


    /**
    * \brief  �������� ���������� �������
    * \details ������ ���-�� ������ � ���-�� ������
    */
    const Stat GetStat() {
        return m_Statistic;
    }

    /**
    * \brief  �������� �������� ���� �������
    */
    virtual std::string GetType() const = 0;
private:
    /**
    * \brief  ���������� ����
    * \details � ����������� �� ���������� ������� ����� ����������� ���������� ����
    * \param[in] aStr - ��� ���������� � ���-�� ��������� ������
    */
    virtual void SaveLog(std::string aStr) = 0;
    
    /**
    * \brief  ���������� �������
    */
    Stat m_Statistic = {};
};


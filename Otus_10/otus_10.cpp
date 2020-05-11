#include "dispatcher/dispatcher.h"
#include <cctype> 
#include <cstring>
#include <condition_variable>  
#include <mutex>
#include <thread>
#include <atomic>
#include <boost/format.hpp>

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    std::size_t N = 0;
    if (argc == 1) {
        std::cout << "���������� ������ � ����� ���� (bulk) �� ���� �����������. �����������  �������� �� ��������� = 3" << std::endl;
        N = 3;
    }
    else {
        N = std::atoi(argv[1]);
        if (N <= 0) {
            std::cout << "���������� ������ � ����� ���� (bulk) ����� �� �������� �������� [" << argv[1] << "]. �����������  �������� �� ��������� = 3" << std::endl;
            N = 3;
        }
    }

    const std::size_t kBulkSize = N > 0 ? N : 1; // ���-�� ������� � ����� �����

    CommandDispatcher dispatcher{ kBulkSize};
    std::string str;
    std::cout << boost::format("Main Thread ID =[%1%]") % std::this_thread::get_id() << std::endl;
    while (std::getline(std::cin, str)) {
        try {
            dispatcher.ProcessCmdLine(str);
        }
        catch (std::exception& e) {
            std::cout << "Exception:" << std::endl;
            std::cout << e.what() << std::endl;
            std::cout << "Program \"bulk\" Terminate" << std::endl;
            return 0;
        }
    }
    dispatcher.Flush(); //��������, ��� ����� �������, ��� �� ��������� �� ����������
    return 0;
}

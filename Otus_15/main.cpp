#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    std::string str;
    std::ofstream file("test.txt");
    if (!file || !file.is_open()) {
        return 1;
    }

    while (std::getline(std::cin, str)){
        file << str << std::endl;
    }
    file << "file end"<< std::endl;

    return 0;
}
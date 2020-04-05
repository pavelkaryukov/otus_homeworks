#include "matrix.h"
#include <string>

void TestMatrix() {
    std::string str = "Damka";
    str[0] = 'Z';
    char test = str[0];
    TLine<int, -1> matrix;
    //auto test = myLine[5];
   // std::cout << matrix[5u] << std::endl;
    matrix[5] = 22;
    matrix[2] = 13;
    matrix[7] = 2;
    matrix[5] = -1;
    matrix[2] = -1;
    matrix[88] = -1;

    (((matrix[88] = -1) = 2) = -1) = 3;

    auto test1 = matrix[12];
//     int test2 = matrix[1];
//     int test3 = matrix[7];
    //matrix[7] = -5;
    int stop1 = 0;
}

int main() {
    TestMatrix();
    return 0;
}
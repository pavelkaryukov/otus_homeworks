#include "matrix.h"
#include <string>

void TestMatrix() {
    std::string str = "Damka";
    str[0] = 'Z';
    char test = str[0];
    TMatrix<int, -1> matrix;
    //auto test = myLine[5];
    std::cout << matrix[5] << std::endl;
    int test1 = matrix[5];
    int test2 = matrix[1];
    int test3 = matrix[7];
    matrix[7] = -5;
    int stop1 = 0;
}

int main() {
    TestMatrix();
    return 0;
}
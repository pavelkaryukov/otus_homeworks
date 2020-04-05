#include "matrix.h"
#include <string>

void TestMatrix() {
    Matrix<int, -1> matrix;
    matrix[1][3] = 22;
    matrix[2][4] = 13;
    matrix[3][5] = 2;
    matrix[3][5] = 101;

    (((matrix[1][0] = 101) = 0) = -1) =2;
    matrix[1][0] = -1;
    matrix[2][4] = -1;

    auto size1 = matrix.size();
}

int main() {
    TestMatrix();
    return 0;
}
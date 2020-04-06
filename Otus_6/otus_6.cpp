#include "matrix.h"
#include <string>

void TestMatrixOld() {
    Matrix<int, -1> matrix;  

    // Matrix<std::string> strMatrix;

    matrix[1][3] = 22;
    matrix[2][4] = 13;
    matrix[3][5] = 2;
    matrix[3][5] = 101;

    (((matrix[1][0] = 101) = 0) = -1) =2;
    matrix[1][0] = 122;
    matrix[2][4] = 2232;

//     for (auto a : matrix) {
//         int stop1 = 0;
//     }

    matrix.IteratorTest();
    auto size1 = matrix.size();
}

void TestMatrix() {
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0);
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);

    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);

    matrix[100][100] = -1;
    assert(a == -1);
    assert(matrix.size() == 0);




}

int main() {
    TestMatrixOld();
    return 0;
}
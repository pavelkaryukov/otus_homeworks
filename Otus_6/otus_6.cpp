#include "matrix.h"
int main() {
    Matrix<int, 0> matrix;
    const int startPos = 0;
    const int endPos = 9;
    for (int i = startPos; i <= endPos; ++i) {
        matrix[i][i] = i;
        matrix[i][endPos - i] = endPos - i;
    }

    std::cout << "matrix fragment [1,1] for [8,8];" << std::endl;
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            std::cout << boost::format("%1% ") % matrix[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << boost::format("Matrix size = %1%") % matrix.size() << std::endl;

    std::cout << "Matrix cout: " << std::endl;
    for (const auto elem : matrix) {
        const auto[x, y, v] = elem;
        std::cout << boost::format("[%1%][%2%] = %3%") % x % y % v << std::endl;
    }
    ((matrix[100][100] = 314) = 0) = 217;
    assert(matrix[100][100] == 217);
    return 0;
}
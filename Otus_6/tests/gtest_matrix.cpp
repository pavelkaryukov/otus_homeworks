#include "matrix.h"
#include <gtest/gtest.h> // googletest header file

void FillMatrixTest(Matrix<int, -1>& aMatrix) {
    aMatrix[1][1] = 12;
    aMatrix[1][2] = 22;
    aMatrix[1][3] = 32;
    aMatrix[1][4] = 42;
}

TEST(test_matrix, AddElement) {
    Matrix<int, -1> matrix;
    FillMatrixTest(matrix);
    ASSERT_EQ(matrix.size(), 4);
}

TEST(test_matrix, EraseElement) {
    Matrix<int, -1> matrix;
    FillMatrixTest(matrix);
    ASSERT_EQ(matrix.size(), 4);
    matrix[1][1] = -1;
    ASSERT_EQ(matrix.size(), 3);
}

TEST(test_matrix, CanonicalAssignmentOperator) {
    Matrix<int, -1> matrix;
    ((((matrix[100][2] = 8) = -1) = 8) = 0) = 3;
    ASSERT_EQ(matrix[100][2], 3);
}

TEST(test_matrix, DetourMatrix) {
    Matrix<int, -1> matrix;
    FillMatrixTest(matrix);
    std::string str;
    for (auto [x, y, v] : matrix) {
        str += std::to_string(x) + std::to_string(y) + std::to_string(v);
    }
    const std::string testStr = "1112122213321442";
    ASSERT_EQ(str, testStr);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
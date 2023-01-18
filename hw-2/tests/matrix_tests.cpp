#include "vector.h"
#include "matrix.h"
#include <gtest/gtest.h>

static constexpr double EPS = 1e-10;

TEST(matrix, default_constructor) {
    Matrix m {3, 2};
    EXPECT_EQ(3, m.row());
    EXPECT_EQ(2, m.col());
    for (size_t i = 0; i < m.row(); i++) {
        for (size_t j = 0; j < m.col(); j++) {
            EXPECT_NEAR(m.at(i, j), 0, EPS);
        }
    }
}

TEST(matrix, copy_constructor) {
    Matrix ori {{1, 2, 3, 0, 4, -3}, 2, 3};
    std::vector<double> true_res = {1, 2, 3, 0, 4, -3};
    Matrix m {ori};
    ori.at(0, 0) = 100;
    ori.at(1, 2) = -10;
    EXPECT_EQ(2, m.row());
    EXPECT_EQ(3, m.col());
    for (size_t i = 0; i < m.row(); i++) {
        for (size_t j = 0; j < m.col(); j++) {
            EXPECT_NEAR(m.at(i, j), true_res[i * m.col() + j], EPS);
        }
    }
}

TEST(matrix, constructor_by_numbers) {
    Matrix m {{1, 2, 3, 4, 5, -1, 0, 4, 5}, 3, 3};
    std::vector<double> true_res = {1, 2, 3, 4, 5, -1, 0, 4, 5};
    EXPECT_EQ(3, m.row());
    EXPECT_EQ(3, m.col());
    for (size_t i = 0; i < m.row(); i++) {
        for (size_t j = 0; j < m.col(); j++) {
            EXPECT_NEAR(m.at(i, j), true_res[i * m.col() + j], EPS);
        }
    }
}

TEST(matrix, constructor_by_vectors) {
    Vector a {{1, 2}};
    Vector b {{4, 0}};
    Vector c {{-3, 2}};
    Matrix m {{a, b, c}};
    std::vector<double> true_res = {1, 2, 4, 0, -3, 2};
    EXPECT_EQ(3, m.row());
    EXPECT_EQ(2, m.col());
    for (size_t i = 0; i < m.row(); i++) {
        for (size_t j = 0; j < m.col(); j++) {
            EXPECT_NEAR(m.at(i, j), true_res[i * m.col() + j], EPS);
        }
    }
}

TEST(matrix, assign_operator) {
    Matrix ori {{1, 2, 3, 7, 2, 0}, 2, 3};
    std::vector<double> true_res = {1, 2, 3, 7, 2, 0};
    Matrix m;
    m = ori;
    ori.at(0, 0) = 100;
    ori.at(1, 1) = -10;
    EXPECT_EQ(2, m.row());
    EXPECT_EQ(3, m.col());
    for (size_t i = 0; i < m.row(); i++) {
        for (size_t j = 0; j < m.col(); j++) {
            EXPECT_NEAR(m.at(i, j), true_res[i * m.col() + j], EPS);
        }
    }
}

TEST(matrix, get_row) {
    Matrix m {{4, 2, -5, 7, 2, 0}, 3, 2};
    Vector res_1 = m.get_row(0);
    Vector res_2 = m.get_row(1);
    EXPECT_EQ(2, res_1.size());
    EXPECT_EQ(2, res_2.size());
    EXPECT_NEAR(res_1[0], 4, EPS);
    EXPECT_NEAR(res_1[1], 2, EPS);
    EXPECT_NEAR(res_2[0], -5, EPS);
    EXPECT_NEAR(res_2[1], 7, EPS);
}

TEST(matrix, get_col) {
    Matrix m {{4, 2, -5, 7, 2, 0, 5, 32}, 4, 2};
    Vector res_1 = m.get_col(0);
    Vector res_2 = m.get_col(1);
    EXPECT_EQ(4, res_1.size());
    EXPECT_EQ(4, res_2.size());
    EXPECT_NEAR(res_1[0], 4, EPS);
    EXPECT_NEAR(res_1[1], -5, EPS);
    EXPECT_NEAR(res_1[2], 2, EPS);
    EXPECT_NEAR(res_1[3], 5, EPS);
    EXPECT_NEAR(res_2[0], 2, EPS);
    EXPECT_NEAR(res_2[1], 7, EPS);
    EXPECT_NEAR(res_2[2], 0, EPS);
    EXPECT_NEAR(res_2[3], 32, EPS);
}

TEST(matrix, get_diag) {
    Vector a {{1, 2, 3, 4}};
    Vector b {{7, 9, 11, 5}};
    Vector c {{-8, 13, 21, 9}};
    Matrix m {{a, b, c}};
    Vector res = m.get_diag();
    EXPECT_EQ(3, res.size());
    EXPECT_NEAR(res[0], 1, EPS);
    EXPECT_NEAR(res[1], 9, EPS);
    EXPECT_NEAR(res[2], 21, EPS);
}

TEST(matrix, sum_matrix) {
    Matrix a {{1, 2, 3, 7, 2, 0}, 2, 3};
    Matrix b {{0, 3, -31, 4, 8, 2}, 2, 3};
    std::vector<double> true_res = {1, 5, -28, 11, 10, 2};
    Matrix c = a + b;
    EXPECT_EQ(2, c.row());
    EXPECT_EQ(3, c.col());
    for (size_t i = 0; i < c.row(); i++) {
        for (size_t j = 0; j < c.col(); j++) {
            EXPECT_NEAR(c.at(i, j), true_res[i * c.col() + j], EPS);
        }
    }
    a += b;
    EXPECT_EQ(2, a.row());
    EXPECT_EQ(3, a.col());
    for (size_t i = 0; i < a.row(); i++) {
        for (size_t j = 0; j < a.col(); j++) {
            EXPECT_NEAR(a.at(i, j), true_res[i * a.col() + j], EPS);
        }
    }
}

TEST(matrix, sub_matrix) {
    Matrix a {{7, 1, 3, -4, 8, 1}, 2, 3};
    Matrix b {{20, 33, 9, 0, -8, 16}, 2, 3};
    std::vector<double> true_res = {-13, -32, -6, -4, 16, -15};
    Matrix c = a - b;
    EXPECT_EQ(2, c.row());
    EXPECT_EQ(3, c.col());
    for (size_t i = 0; i < c.row(); i++) {
        for (size_t j = 0; j < c.col(); j++) {
            EXPECT_NEAR(c.at(i, j), true_res[i * c.col() + j], EPS);
        }
    }
    a -= b;
    EXPECT_EQ(2, a.row());
    EXPECT_EQ(3, a.col());
    for (size_t i = 0; i < a.row(); i++) {
        for (size_t j = 0; j < a.col(); j++) {
            EXPECT_NEAR(a.at(i, j), true_res[i * a.col() + j], EPS);
        }
    }
}

TEST(matrix, mult_matrix_by_elem) {
    Matrix a {{11, 0, 4, -1, 12, 1}, 2, 3};
    Matrix b {{5, 3, 92, 5, 1, -100}, 2, 3};
    std::vector<double> true_res = {55, 0, 368, -5, 12, -100};
    Matrix c = a * b;
    EXPECT_EQ(2, c.row());
    EXPECT_EQ(3, c.col());
    for (size_t i = 0; i < c.row(); i++) {
        for (size_t j = 0; j < c.col(); j++) {
            EXPECT_NEAR(c.at(i, j), true_res[i * c.col() + j], EPS);
        }
    }
    a *= b;
    EXPECT_EQ(2, a.row());
    EXPECT_EQ(3, a.col());
    for (size_t i = 0; i < a.row(); i++) {
        for (size_t j = 0; j < a.col(); j++) {
            EXPECT_NEAR(a.at(i, j), true_res[i * a.col() + j], EPS);
        }
    }
}

TEST(matrix, add_vector) {
    Matrix m {{7, 2, 1, -3, 10, 15}, 2, 3};
    Vector v_row = Vector({3, 2, 8});
    Vector v_col = Vector({-1, 30});
    Matrix res_row = m.add(v_row, 0);
    Matrix res_col = m.add(v_col, 1);
    std::vector<double> true_res_row = {10, 4, 9, 0, 12, 23};
    std::vector<double> true_res_col = {6, 1, 0, 27, 40, 45};
    EXPECT_EQ(2, res_row.row());
    EXPECT_EQ(3, res_row.col());
    for (size_t i = 0; i < res_row.row(); i++) {
        for (size_t j = 0; j < res_row.col(); j++) {
            EXPECT_NEAR(res_row.at(i, j), true_res_row[i * res_row.col() + j], EPS);
        }
    }
    EXPECT_EQ(2, res_col.row());
    EXPECT_EQ(3, res_col.col());
    for (size_t i = 0; i < res_col.row(); i++) {
        for (size_t j = 0; j < res_col.col(); j++) {
            EXPECT_NEAR(res_col.at(i, j), true_res_col[i * res_col.col() + j], EPS);
        }
    }

    m.add_assign(v_row, 0);
    EXPECT_EQ(2, m.row());
    EXPECT_EQ(3, m.col());
    for (size_t i = 0; i < m.row(); i++) {
        for (size_t j = 0; j < m.col(); j++) {
            EXPECT_NEAR(m.at(i, j), true_res_row[i * m.col() + j], EPS);
        }
    }
    m = {{7, 2, 1, -3, 10, 15}, 2, 3};
    m.add_assign(v_col, 1);
    EXPECT_EQ(2, m.row());
    EXPECT_EQ(3, m.col());
    for (size_t i = 0; i < m.row(); i++) {
        for (size_t j = 0; j < m.col(); j++) {
            EXPECT_NEAR(m.at(i, j), true_res_col[i * m.col() + j], EPS);
        }
    }
}

TEST(matrix, sub_vector) {
    Matrix m {{10, 0, 4, 2, -5, 7}, 2, 3};
    Vector v_row = Vector({3, -9, 0});
    Vector v_col = Vector({10, -13});
    Matrix res_row = m.sub(v_row, 0);
    Matrix res_col = m.sub(v_col, 1);
    std::vector<double> true_res_row = {7, 9, 4, -1, 4, 7};
    std::vector<double> true_res_col = {0, -10, -6, 15, 8, 20};
    EXPECT_EQ(2, res_row.row());
    EXPECT_EQ(3, res_row.col());
    for (size_t i = 0; i < res_row.row(); i++) {
        for (size_t j = 0; j < res_row.col(); j++) {
            EXPECT_NEAR(res_row.at(i, j), true_res_row[i * res_row.col() + j], EPS);
        }
    }
    EXPECT_EQ(2, res_col.row());
    EXPECT_EQ(3, res_col.col());
    for (size_t i = 0; i < res_col.row(); i++) {
        for (size_t j = 0; j < res_col.col(); j++) {
            EXPECT_NEAR(res_col.at(i, j), true_res_col[i * res_col.col() + j], EPS);
        }
    }

    m.sub_assign(v_row, 0);
    EXPECT_EQ(2, m.row());
    EXPECT_EQ(3, m.col());
    for (size_t i = 0; i < m.row(); i++) {
        for (size_t j = 0; j < m.col(); j++) {
            EXPECT_NEAR(m.at(i, j), true_res_row[i * m.col() + j], EPS);
        }
    }
    m = {{10, 0, 4, 2, -5, 7}, 2, 3};
    m.sub_assign(v_col, 1);
    EXPECT_EQ(2, m.row());
    EXPECT_EQ(3, m.col());
    for (size_t i = 0; i < m.row(); i++) {
        for (size_t j = 0; j < m.col(); j++) {
            EXPECT_NEAR(m.at(i, j), true_res_col[i * m.col() + j], EPS);
        }
    }
}

TEST(matrix, mult_by_vector) {
    Matrix m {{3, 2, 4, -1, 5, -10, 3, 0, 43, -20, 12, 2}, 3, 4};
    Vector v {{7, 5, 3, 0}};
    Vector res = m.mult(v);
    EXPECT_EQ(3, res.size());
    EXPECT_NEAR(res[0], 43, EPS);
    EXPECT_NEAR(res[1], -6, EPS);
    EXPECT_NEAR(res[2], 237, EPS);
}

TEST(matrix, add_number) {
    Matrix a {{11, 0, 4, -1, 12, 1}, 2, 3};
    double num = -10;
    Matrix c = a + num;
    std::vector<double> true_res = {1, -10, -6, -11, 2, -9};
    EXPECT_EQ(2, c.row());
    EXPECT_EQ(3, c.col());
    for (size_t i = 0; i < c.row(); i++) {
        for (size_t j = 0; j < c.col(); j++) {
            EXPECT_NEAR(c.at(i, j), true_res[i * c.col() + j], EPS);
        }
    }

    a += num;
    EXPECT_EQ(2, a.row());
    EXPECT_EQ(3, a.col());
    for (size_t i = 0; i < a.row(); i++) {
        for (size_t j = 0; j < a.col(); j++) {
            EXPECT_NEAR(a.at(i, j), true_res[i * a.col() + j], EPS);
        }
    }

    a = {{11, 0, 4, -1, 12, 1}, 2, 3};
    Matrix c_left = num + a;
    EXPECT_EQ(2, c_left.row());
    EXPECT_EQ(3, c_left.col());
    for (size_t i = 0; i < c_left.row(); i++) {
        for (size_t j = 0; j < c_left.col(); j++) {
            EXPECT_NEAR(c_left.at(i, j), true_res[i * c_left.col() + j], EPS);
        }
    }
}

TEST(matrix, sub_number) {
    Matrix a {{1, -2, 32, 10, 100, -51}, 2, 3};
    double num = 21;
    Matrix c = a - num;
    std::vector<double> true_res = {-20, -23, 11, -11, 79, -72};
    EXPECT_EQ(2, c.row());
    EXPECT_EQ(3, c.col());
    for (size_t i = 0; i < c.row(); i++) {
        for (size_t j = 0; j < c.col(); j++) {
            EXPECT_NEAR(c.at(i, j), true_res[i * c.col() + j], EPS);
        }
    }

    a -= num;
    EXPECT_EQ(2, a.row());
    EXPECT_EQ(3, a.col());
    for (size_t i = 0; i < a.row(); i++) {
        for (size_t j = 0; j < a.col(); j++) {
            EXPECT_NEAR(a.at(i, j), true_res[i * a.col() + j], EPS);
        }
    }

    a = {{1, -2, 32, 10, 100, -51}, 2, 3};
    true_res = {20, 23, -11, 11, -79, 72};
    Matrix c_left = num - a;
    EXPECT_EQ(2, c_left.row());
    EXPECT_EQ(3, c_left.col());
    for (size_t i = 0; i < c_left.row(); i++) {
        for (size_t j = 0; j < c_left.col(); j++) {
            EXPECT_NEAR(c_left.at(i, j), true_res[i * c_left.col() + j], EPS);
        }
    }
}

TEST(matrix, mult_number) {
    Matrix a {{0, 5, -3, 4, 34, -10}, 2, 3};
    double num = 4;
    Matrix c = a * num;
    std::vector<double> true_res = {0, 20, -12, 16, 136, -40};
    EXPECT_EQ(2, c.row());
    EXPECT_EQ(3, c.col());
    for (size_t i = 0; i < c.row(); i++) {
        for (size_t j = 0; j < c.col(); j++) {
            EXPECT_NEAR(c.at(i, j), true_res[i * c.col() + j], EPS);
        }
    }

    a *= num;
    EXPECT_EQ(2, a.row());
    EXPECT_EQ(3, a.col());
    for (size_t i = 0; i < a.row(); i++) {
        for (size_t j = 0; j < a.col(); j++) {
            EXPECT_NEAR(a.at(i, j), true_res[i * a.col() + j], EPS);
        }
    }

    a = {{0, 5, -3, 4, 34, -10}, 2, 3};
    Matrix c_left = num * a;
    EXPECT_EQ(2, c_left.row());
    EXPECT_EQ(3, c_left.col());
    for (size_t i = 0; i < c_left.row(); i++) {
        for (size_t j = 0; j < c_left.col(); j++) {
            EXPECT_NEAR(c_left.at(i, j), true_res[i * c_left.col() + j], EPS);
        }
    }
}

TEST(matrix, mult_matrix) {
    Matrix a {{3, 2, 4, -1, 5, -10, 3, 0, 43, -20, 12, 2}, 3, 4};
    Matrix b {{4, 3, 0, -10, 100, -3, 4, 7}, 4, 2};
    Matrix c = a.mult_matrix(b);
    std::vector<double> true_res = {408, -30, 320, 106, 1380, 307};
    EXPECT_EQ(3, c.row());
    EXPECT_EQ(2, c.col());
    for (size_t i = 0; i < c.row(); i++) {
        for (size_t j = 0; j < c.col(); j++) {
            EXPECT_NEAR(c.at(i, j), true_res[i * c.col() + j], EPS);
        }
    }
}

TEST(matrix, transpose_matrix) {
    Matrix a {{3, 2, 4, -1, 5, -10, 3, 0, 43, -20, 12, 2}, 3, 4};
    Matrix res = a.transpose();
    std::vector<double> true_res = {3, 5, 43, 2, -10, -20, 4, 3, 12, -1, 0 ,2};
    EXPECT_EQ(4, res.row());
    EXPECT_EQ(3, res.col());
    for (size_t i = 0; i < res.row(); i++) {
        for (size_t j = 0; j < res.col(); j++) {
            EXPECT_NEAR(res.at(i, j), true_res[i * res.col() + j], EPS);
        }
    }

    res = res.transpose();
    EXPECT_EQ(3, res.row());
    EXPECT_EQ(4, res.col());
    for (size_t i = 0; i < res.row(); i++) {
        for (size_t j = 0; j < res.col(); j++) {
            EXPECT_NEAR(res.at(i, j), a.at(i, j), EPS);
        }
    }
}

TEST(matrix, determinant_matrix) {
    Matrix A {{3, 2, 4, -1, 5, -10, 3, 0, 43}, 3, 3};
    EXPECT_NEAR(A.determinant(), 611, EPS);

    Matrix M_dim_4 {{1, 4, -10, 8, 4, 0, -1, 54, 11, 28, 0, -100, 0, 1, 2, 3}, 4, 4};
    EXPECT_NEAR(M_dim_4.determinant(), -19880, EPS);

    Matrix M_dim_5 {{1, 2, -1, 4, 0, 4, 0, 2, 4, 65, 21, 205, 0,
     -100, 7, 0, 1, 2, 3, 4, 0, 43, 0, -81, 1}, 5, 5};
    EXPECT_NEAR(M_dim_5.determinant(), 190390, EPS);
}

TEST(matrix, inverse_matrix) {
    Matrix A {{1, 2, 3, 4}, 2, 2};
    std::vector<double> true_res = {-2, 1, 1.5, -0.5};
    Matrix res = A.inverse();
    EXPECT_EQ(2, res.row());
    EXPECT_EQ(2, res.col());
    for (size_t i = 0; i < res.row(); i++) {
        for (size_t j = 0; j < res.col(); j++) {
            EXPECT_NEAR(res.at(i, j), true_res[i * res.col() + j], EPS);
        }
    }

    Matrix B = {{3, 4, 2, 2, -1, -3, 1, 5, 1}, 3, 3};
    true_res = {14./44, 6./44, -10./44, -5./44, 1./44, 13./44, 11./44, -11./44, -11./44};
    Matrix res_b = B.inverse();
    EXPECT_EQ(3, res_b.row());
    EXPECT_EQ(3, res_b.col());
    for (size_t i = 0; i < res_b.row(); i++) {
        for (size_t j = 0; j < res_b.col(); j++) {
            EXPECT_NEAR(res_b.at(i, j), true_res[i * res_b.col() + j], EPS);
        }
    }

    Matrix M_dim_4 {{1, 4, -10, 8, 4, 0, -1, 54, 11, 28, 0, -100, 0, 1, 2, 3}, 4, 4};
    true_res = {-401./2485, 386./2485, 122./2485, -1812./2485, 2021./19880, -353./9940,
     73./19880, 1219./2485, -19./284, 1./142, 1./284, 12./71, 3./280, 1./140, -1./280, 2./35};
    Matrix M_dim_4_inv = M_dim_4.inverse();
    EXPECT_EQ(4, M_dim_4_inv.row());
    EXPECT_EQ(4, M_dim_4_inv.col());
    for (size_t i = 0; i < M_dim_4_inv.row(); i++) {
        for (size_t j = 0; j < M_dim_4_inv.col(); j++) {
            EXPECT_NEAR(M_dim_4_inv.at(i, j), true_res[i * M_dim_4_inv.col() + j], EPS);
        }
    }
}

TEST (matrix, ind_validation) {
    Matrix A {{1, -4, 0, 7}, 2, 2};
    EXPECT_EQ(-4, A.at(0, 1));
    EXPECT_THROW(A.at(0, 3), std::out_of_range);
    EXPECT_THROW(A.at(5, 1), std::out_of_range);
    EXPECT_THROW(A.at(-2, -1), std::out_of_range);
}

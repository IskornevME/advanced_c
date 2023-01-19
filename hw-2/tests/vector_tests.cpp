#include "vector.h"
#include "matrix.h"
#include <gtest/gtest.h>

static constexpr double EPS = 1e-10;

TEST(vector, default_constructor) {
    Vector v {3};
    EXPECT_EQ(3, v.size());
    EXPECT_NEAR(v[0], 0, EPS);
    EXPECT_NEAR(v[1], 0, EPS);
    EXPECT_NEAR(v[2], 0, EPS);
}

TEST(vector, constructor_by_vector) {
    Vector v {{1, 2, 3, 4}};
    EXPECT_EQ(4, v.size());
    EXPECT_NEAR(v[0], 1, EPS);
    EXPECT_NEAR(v[1], 2, EPS);
    EXPECT_NEAR(v[2], 3, EPS);
    EXPECT_NEAR(v[3], 4, EPS);
}

TEST(vector, copy_constructor) {
    Vector ori {{1, 2}};
    Vector v {ori};
    ori[0] = 10;
    EXPECT_EQ(2, v.size());
    EXPECT_NEAR(v[0], 1, EPS);
    EXPECT_NEAR(v[1], 2, EPS);
}

TEST(vector, assign_operator) {
    Vector ori {{1, 2}};
    Vector v;
    v = ori;
    ori[0] = 10;
    EXPECT_EQ(2, v.size());
    EXPECT_NEAR(v[0], 1, EPS);
    EXPECT_NEAR(v[1], 2, EPS);
}

TEST(vector, sum_vector) {
    Vector a {{1, 2}};
    Vector b {{5, 7}};
    Vector c = a + b;
    EXPECT_EQ(2, c.size());
    EXPECT_NEAR(c[0], 6, EPS);
    EXPECT_NEAR(c[1], 9, EPS);
    a += b;
    EXPECT_EQ(2, a.size());
    EXPECT_NEAR(a[0], 6, EPS);
    EXPECT_NEAR(a[1], 9, EPS);
}

TEST(vector, sub_vector) {
    Vector a {{1, 2, 3}};
    Vector b {{5, 7, -4}};
    Vector c = a - b;
    EXPECT_EQ(3, c.size());
    EXPECT_NEAR(c[0], -4, EPS);
    EXPECT_NEAR(c[1], -5, EPS);
    EXPECT_NEAR(c[2], 7, EPS);
    a -= b;
    EXPECT_EQ(3, a.size());
    EXPECT_NEAR(a[0], -4, EPS);
    EXPECT_NEAR(a[1], -5, EPS);
    EXPECT_NEAR(a[2], 7, EPS);
}

TEST(vector, mult_vector) {
    Vector a {{4, 2, 1}};
    Vector b {{7, -3, 0}};
    Vector c = a * b;
    EXPECT_EQ(3, c.size());
    EXPECT_NEAR(c[0], 28, EPS);
    EXPECT_NEAR(c[1], -6, EPS);
    EXPECT_NEAR(c[2], 0, EPS);
    a *= b;
    EXPECT_EQ(3, a.size());
    EXPECT_NEAR(a[0], 28, EPS);
    EXPECT_NEAR(a[1], -6, EPS);
    EXPECT_NEAR(a[2], 0, EPS);
}

TEST(vector, add_number) {
    Vector a {{4, 2, 1, 9}};
    double num = -10;
    Vector c = a + num;
    EXPECT_EQ(4, c.size());
    EXPECT_NEAR(c[0], -6, EPS);
    EXPECT_NEAR(c[1], -8, EPS);
    EXPECT_NEAR(c[2], -9, EPS);
    EXPECT_NEAR(c[3], -1, EPS);
    a += num;
    EXPECT_EQ(4, a.size());
    EXPECT_NEAR(a[0], -6, EPS);
    EXPECT_NEAR(a[1], -8, EPS);
    EXPECT_NEAR(a[2], -9, EPS);
    EXPECT_NEAR(a[3], -1, EPS);
    Vector c_left = num + a;
    EXPECT_EQ(4, c_left.size());
    EXPECT_NEAR(c_left[0], -16, EPS);
    EXPECT_NEAR(c_left[1], -18, EPS);
    EXPECT_NEAR(c_left[2], -19, EPS);
    EXPECT_NEAR(c_left[3], -11, EPS);

}

TEST(vector, sub_number) {
    Vector a {{-3, 5, 1}};
    double num = 4;
    Vector c = a - num;
    EXPECT_EQ(3, c.size());
    EXPECT_NEAR(c[0], -7, EPS);
    EXPECT_NEAR(c[1], 1, EPS);
    EXPECT_NEAR(c[2], -3, EPS);
    a -= num;
    EXPECT_EQ(3, a.size());
    EXPECT_NEAR(a[0], -7, EPS);
    EXPECT_NEAR(a[1], 1, EPS);
    EXPECT_NEAR(a[2], -3, EPS);
    Vector c_left = num - a;
    EXPECT_EQ(3, c_left.size());
    EXPECT_NEAR(c_left[0], 11, EPS);
    EXPECT_NEAR(c_left[1], 3, EPS);
    EXPECT_NEAR(c_left[2], 7, EPS);
}

TEST(vector, mult_number) {
    Vector a {{2, 0, -7}};
    double num = 3;
    Vector c = a * num;
    EXPECT_EQ(3, c.size());
    EXPECT_NEAR(c[0], 6, EPS);
    EXPECT_NEAR(c[1], 0, EPS);
    EXPECT_NEAR(c[2], -21, EPS);
    a *= num;
    EXPECT_EQ(3, a.size());
    EXPECT_NEAR(a[0], 6, EPS);
    EXPECT_NEAR(a[1], 0, EPS);
    EXPECT_NEAR(a[2], -21, EPS);
    Vector c_left = num * a;
    EXPECT_EQ(3, c_left.size());
    EXPECT_NEAR(c_left[0], 18, EPS);
    EXPECT_NEAR(c_left[1], 0, EPS);
    EXPECT_NEAR(c_left[2], -63, EPS);
}

TEST(vector, mult_matrix) {
    Vector a {{1, 2}};
    Matrix B {{3, 4, 5, 6, 7, 8}, 2, 3};
    Vector c = a.mult(B);
    EXPECT_EQ(3, c.size());
    EXPECT_NEAR(c[0], 15, EPS);
    EXPECT_NEAR(c[1], 18, EPS);
    EXPECT_NEAR(c[2], 21, EPS);
}

TEST(vector, ind_validation) {
    Vector a {{1, 3, 0}};
    EXPECT_THROW(a[-1], std::out_of_range);
    EXPECT_NEAR(a[0], 1, EPS);
    EXPECT_NEAR(a[2], 0, EPS);
    EXPECT_THROW(a[3], std::out_of_range);
}
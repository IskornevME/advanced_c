#include <gtest/gtest.h>
#include "set.h"
#include <vector>


TEST(my_tests, const_iterators) {
    std::vector<int> v = {1, 2, 5};
    Set<int> a{ v.begin(), v.end() };
    auto it = a.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 5);
    ++it;
    ASSERT_EQ(it, a.end());
}

TEST(my_test, increment_iterator) {
    std::vector<int> v = {1, 2, 5};
    Set<int> a{ v.begin(), v.end() };
    auto it = a.begin();
    ASSERT_EQ(*(it++), 1);
    ASSERT_EQ(*it, 2);
    ASSERT_EQ(*(++it), 5);
    ASSERT_EQ(*it, 5);
}

TEST(my_tests, const_list) {
    Set<int> a = {1, 2, 3};
    auto it = a.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(it, a.end());
}

TEST(my_tests, const_copy) {
    Set<int> a = {1, 2, 3};
    Set<int> b { a };
    auto it = b.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(it, b.end());
}

TEST(my_tests, operator_assign) {
    Set<int> a;
    Set<int> b;
    b = a;
    ASSERT_EQ(b.begin(), b.end());
}

TEST(my_tests, empty_size) {
    Set<int> a = {1, 2, 3};
    ASSERT_FALSE(a.empty() == 1);
    ASSERT_EQ(a.size(), 3);
}

/* check if class provides correct interface
 * in terms of constness */
TEST(base_tests, constness) {
    const Set<int> s{-4, 5, 3, 0, 7};
    // if (s.find(3) == s.end())
    //     fail("3 not found, incorrect find");
    ASSERT_FALSE(s.find(3) == s.end());
    // if (*s.lower_bound(2) != 3 || s.lower_bound(8) != s.end() || *s.lower_bound(-2) != 0)
    //     fail("incorrect lower_bound");
    ASSERT_FALSE(*s.lower_bound(2) != 3);
    ASSERT_FALSE(s.lower_bound(8) != s.end());
    ASSERT_FALSE(*s.lower_bound(-2) != 0);
    // if (s.empty())
    //     fail("incorrect empty");
    ASSERT_FALSE(s.empty());
    // if (s.size() != 5)
    //     fail("incorrect size");
    ASSERT_FALSE(s.size() != 5);
    auto first = s.begin();
    Set<int>::iterator last = s.end();
    // if (*first != -4 || *(--last) != 7)
    //     fail("incorrect begin or end");
    ASSERT_FALSE(*first != -4);
    ASSERT_FALSE(*(--last) != 7);
    // std::cerr << "ok!\n";
}

#include <gtest/gtest.h>
#include "set.h"
#include <vector>
#include <set>


TEST(my_tests, constructor_iterators) {
    std::vector<int> v = {1, 2, 5};
    Set<int> a {v.begin(), v.end()};
    auto it = a.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 5);
    ++it;
    ASSERT_EQ(it, a.end());
    ASSERT_EQ(a.size(), 3);
    ASSERT_FALSE(a.empty());
}


TEST(my_tests, increment_iterator) {
    std::vector<int> v = {1, 2, 5};
    Set<int> a {v.begin(), v.end()};
    auto it = a.begin();
    ASSERT_EQ(*(it++), 1);
    ASSERT_EQ(*it, 2);
    ASSERT_EQ(*(++it), 5);
    ASSERT_EQ(*it, 5);

    std::vector<int> v2 = {3, 0, 1, 4};
    Set<int> b {v2.begin(), v2.end()};
    auto it2 = b.end();
    --it2;
    ASSERT_EQ(*it2, 4);
    ASSERT_EQ(*(--it2), 3);
    ASSERT_EQ(*(it2--), 3);
    ASSERT_EQ(*it2, 1);
    ASSERT_EQ(*(--it2), 0);
    ASSERT_EQ(b.size(), 4);
    ASSERT_FALSE(b.empty());
}


TEST(my_tests, constructor_list) {
    Set<int> a = {1, 2, 3};
    auto it = a.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(it, a.end());
    ASSERT_EQ(a.size(), 3);
    ASSERT_FALSE(a.empty());
}


TEST(my_tests, constructor_copy) {
    Set<int> a = {1, 2, 3};
    Set<int> b {a};
    ASSERT_EQ(*a.begin(), *b.begin());
    ASSERT_EQ(*(--a.end()), *(--b.end()));
    auto it = b.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(it, b.end());
    ASSERT_EQ(b.size(), a.size());

    Set<int> c = {5, 3, 2, 100, 7, -1, 0};
    Set<int> d {c};
    d.insert(4);
    d.insert(-10);
    c.erase(100);
    auto it_c = c.begin();
    auto it_d = d.begin();
    while (it_c != c.end() || it_d != d.end()) {
        if (*it_d == 4 || *it_d == -10 || *it_d == 100) {
            ++it_d;
            continue;
        }
        ASSERT_EQ(*it_c, *it_d);
        ++it_c;
        ++it_d;
    }
    std::set<int> true_set_c {5, 3, 2, 7, -1, 0};
    it_c = c.begin();
    auto it_ts_c = true_set_c.begin();
    while (it_c != c.end() || it_ts_c != true_set_c.end()) {
        ASSERT_EQ(*it_c, *it_ts_c);
        ++it_c;
        ++it_ts_c;
    }
    std::set<int> true_set_d {5, 3, 2, 100, 7, -1, 0, 4, -10};
    it_d = d.begin();
    auto it_ts_d = true_set_d.begin();
    while (it_d != d.end() || it_ts_d != true_set_d.end()) {
        ASSERT_EQ(*it_d, *it_ts_d);
        ++it_d;
        ++it_ts_d;
    }
}


TEST(my_tests, operator_assign) {
    Set<int> a;
    Set<int> b;
    b = a;
    ASSERT_EQ(a.begin(), a.end());
    ASSERT_EQ(b.begin(), b.end());
    ASSERT_EQ(a.size(), b.size());
    ASSERT_TRUE(b.empty());

    Set<int> c = {3, 8, 0, 4};
    Set<int> d;
    d = c;
    ASSERT_EQ(d.size(), c.size());
    ASSERT_EQ(*d.begin(), *c.begin());
    ASSERT_EQ(*(--d.end()), *(--c.end()));
    ASSERT_FALSE(d.empty());
    std::vector<int> true_values_c = {0, 3, 4, 8};
    int i = 0;
    auto it = d.begin();
    while (it != d.end()) {
        ASSERT_EQ(*it, true_values_c[i]);
        ++it;
        ++i;
    }
    auto it_c = c.begin();
    auto it_d = d.begin();
    while (it_c != c.end() || it_d != d.end()) {
        ASSERT_EQ(*it_d, *it_c);
        ++it_d;
        ++it_c;
    }
}


TEST(my_tests, empty_and_size) {
    Set<int> a = {1, 2, 3};
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(a.size(), 3);

    Set<std::string> b;
    ASSERT_TRUE(b.empty());
    ASSERT_EQ(b.size(), 0);

    Set<int> c;
    ASSERT_EQ(c.begin(), c.end());
    ASSERT_EQ(c.size(), 0);

    c.insert(10);
    ASSERT_FALSE(c.empty());
    ASSERT_EQ(c.size(), 1);

    Set<std::string> d {b};
    ASSERT_TRUE(d.empty());
    ASSERT_EQ(d.size(), 0);

    c.erase(10);
    Set<int> f = {4, 2, 7};
    f = c;
    ASSERT_TRUE(f.empty());
    ASSERT_EQ(f.size(), 0);
}


TEST(my_tests, iterators) {
    Set<int> a = {0};
    ASSERT_EQ(*a.begin(), 0);
    ASSERT_EQ(*a.begin(), *(--a.end()));

    Set<int> b = {4, 3, 2, 5, 6, 100, -10, 27};
    ASSERT_EQ(*b.begin(), -10);
    ASSERT_EQ(*(--b.end()), 100);
    ASSERT_TRUE(b.begin() != b.end());
    auto first = b.begin();
    auto last = b.end();
    while (first != last) {
        ++first;
        --last;
    }
    ASSERT_EQ(*first, *last);
    ASSERT_TRUE(first == last);

    Set<std::string> c = {"abba", "boo", "ggg", "foo"};
    auto c_first = c.begin();
    auto c_last = c.end();
    c.erase("foo");
    c.erase("ggg");
    c_first++;
    c_last--;
    ASSERT_EQ(c_first, c_last);
}


TEST(my_tests, insert) {
    Set<int> a;
    a.insert(1);
    ASSERT_EQ(a.size(), 1);
    a.insert(5);
    ASSERT_EQ(a.size(), 2);
    a.insert(2);
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(a.size(), 3);
    a.insert(7);
    a.insert(3);
    a.insert(0);
    ASSERT_EQ(a.size(), 6);
    auto first = a.begin();
    auto last = a.end();
    ASSERT_EQ(*first, 0);
    ASSERT_EQ(*(--last), 7);
    a.insert(9);
    std::vector<int> true_values_a = {0, 1, 2, 3, 5, 7, 9};
    int i = 0;
    while (first != a.end()) {
        ASSERT_EQ(*first, true_values_a[i]);
        ++first;
        ++i;
    }

    Set<int> b {a};
    b.insert(10);
    b.insert(-1);
    b.insert(6);
    first = b.begin();
    last = b.end();
    ASSERT_EQ(b.size(), 10);
    ASSERT_EQ(*first, -1);
    ASSERT_EQ(*(--last), 10);

    std::vector<int> v = {1, 2};
    Set<int> c {v.begin(), v.end()};
    c.insert(5);
    c.insert(0);
    c.insert(12);
    auto c_first = c.begin();
    auto c_last = c.end();
    ASSERT_EQ(c.size(), 5);
    ASSERT_EQ(*c_first, 0);
    ASSERT_EQ(*(--c_last), 12);
    c_last = c.end();
    std::set<int> true_set {1, 2, 5, 0, 12};
    auto ts_first = true_set.begin();
    auto ts_last = true_set.end();
    while (c_first != c_last || ts_first != ts_last) {
        ASSERT_EQ(*c_first, *ts_first);
        ++c_first;
        ++ts_first;
    }
}


TEST(my_tests, erase) {
    Set<int> a = {1, 5, 3, 7, 4};
    ASSERT_EQ(a.size(), 5);
    a.erase(3);
    auto last = a.end();
    ASSERT_EQ(a.size(), 4);
    ASSERT_EQ(*a.begin(), 1);
    ASSERT_EQ(*(++a.begin()), 4);
    ASSERT_EQ(*(--last), 7);
    ASSERT_EQ(*(--last), 5);
    a.erase(10);
    ASSERT_EQ(a.size(), 4);
    std::vector<int> true_values_a = {1, 4, 5, 7};
    int i = 0;
    auto it = a.begin();
    while (it != a.end()) {
    ASSERT_EQ(*it, true_values_a[i]);
        ++it;
        ++i;
    }

    Set<int> b = {4, 0, 7};
    b.erase(4);
    b.erase(0);
    b.erase(7);
    b.erase(-10);
    b.erase(1000);
    ASSERT_EQ(b.size(), 0);
    ASSERT_TRUE(b.empty());

    Set<std::string> c = {"abc", "alpha", "beta"};
    c.insert("gamma");
    c.insert("delta");
    ASSERT_EQ(c.size(), 5);
    ASSERT_FALSE(c.empty());
    c.erase("gamma");
    c.erase("delta");
    ASSERT_EQ(c.size(), 3);
    ASSERT_FALSE(c.empty());
    c.erase("alpha");
    c.erase("epsilon");
    c.erase("omega");
    ASSERT_EQ(*c.begin(), "abc");
    ASSERT_EQ(*(--c.end()), "beta");
    ASSERT_EQ(c.size(), 2);
    ASSERT_FALSE(c.empty());
}


TEST(my_tests, erase_from_empty) {
    Set<std::string> a;
    a.erase("hello");
    a.erase("world");
    ASSERT_EQ(a.size(), 0);
    ASSERT_EQ(a.begin(), a.end());
    ASSERT_TRUE(a.empty());
}


TEST(my_tests, find) {
    Set<int> a = {4, 2, 0, 1, 3, 7};
    ASSERT_EQ(*a.find(2), 2);
    ASSERT_FALSE(a.find(3) == a.end());
    ASSERT_EQ(a.find(5), a.end());
    ASSERT_EQ(a.size(), 6);
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(*a.begin(), 0);
    ASSERT_EQ(*(--a.end()), 7);

    ASSERT_EQ(a.find(6), a.end());
    a.insert(6);
    ASSERT_EQ(*a.find(6), 6);
    ASSERT_EQ(a.size(), 7);
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(*a.begin(), 0);
    ASSERT_EQ(*(--a.end()), 7);

    ASSERT_EQ(*a.find(2), 2);
    a.erase(2);
    ASSERT_EQ(a.find(2), a.end());
    ASSERT_EQ(a.size(), 6);
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(*a.begin(), 0);
    ASSERT_EQ(*(--a.end()), 7);

    Set<std::string> b = {"Brazil", "Croatia", "Netherlands"};
    Set<std::string> c {b};
    c.insert("Argentina");
    ASSERT_FALSE(c.find("Argentina") == c.end());
    ASSERT_EQ(*c.find("Argentina"), "Argentina");
    c = b;
    ASSERT_EQ(c.find("Argentina"), c.end());

    Set<int> d;
    ASSERT_EQ(d.find(3), d.end());
    ASSERT_EQ(d.size(), 0);
    ASSERT_TRUE(d.empty());
}


TEST(my_tests, lower_bound) {
    Set<int> a = {5, 0, 2, 3};
    ASSERT_EQ(*a.lower_bound(1), 2);
    ASSERT_EQ(*a.lower_bound(2), 2);
    ASSERT_EQ(*a.lower_bound(-1), 0);
    ASSERT_EQ(a.lower_bound(6), a.end());
    ASSERT_EQ(a.size(), 4);
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(*a.begin(), 0);
    ASSERT_EQ(*(--a.end()), 5);
    auto it_a = a.lower_bound(4);
    ASSERT_EQ(++it_a, a.end());

    Set<std::string> b;
    b.insert("Moscow");
    ASSERT_EQ(*b.lower_bound("Kazan"), "Moscow");
    ASSERT_EQ(b.size(), 1);
    ASSERT_FALSE(b.empty());
    b.insert("Kazan");
    ASSERT_EQ(*b.lower_bound("Kazan"), "Kazan");
    ASSERT_EQ(b.size(), 2);
    ASSERT_FALSE(b.empty());
    ASSERT_EQ(*b.begin(), "Kazan");
    ASSERT_EQ(*(--b.end()), "Moscow");

    Set<int> c = {4, 1, 2, 5, 6, 7};
    ASSERT_EQ(*c.lower_bound(5), 5);
    c.erase(5);
    ASSERT_EQ(*c.lower_bound(5), 6);
    c.erase(6);
    ASSERT_EQ(*c.lower_bound(5), 7);
    c.erase(7);
    ASSERT_EQ(c.lower_bound(5), c.end());
    ASSERT_EQ(c.size(), 3);
    ASSERT_FALSE(c.empty());
    ASSERT_EQ(*c.begin(), 1);
    ASSERT_EQ(*(--c.end()), 4);

    Set<int> d = {2, 0, 5, 3};
    Set<int> f {d};
    f.insert(100);
    ASSERT_FALSE(f.lower_bound(7) == f.end());
    ASSERT_EQ(*f.lower_bound(7), 100);
    f = d;
    ASSERT_EQ(f.lower_bound(7), f.end());

    Set<int> g;
    ASSERT_EQ(g.lower_bound(3), g.end());
    ASSERT_EQ(g.size(), 0);
    ASSERT_TRUE(g.empty());
}

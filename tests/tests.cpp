#include <gtest/gtest.h>

extern "C" {
    #include "task.h"
    #include "structure.h"
}


TEST(task, no_lessons) {
    LessonInfo data[2];
    data[0] = LessonInfo {.week_day = 1, .auditorium = 402, .group = 101};
    data[1] = LessonInfo {.week_day = 2, .auditorium = 405, .group = 204};
    Location *result;
    size_t size_result;
    int ret = task(data, 2, 203, &result, &size_result);
    EXPECT_EQ(0, ret);
    EXPECT_EQ(0, size_result);
    free(result);
}

TEST(task, two_aud_in_one_day) {
    LessonInfo data[2];
    data[0] = LessonInfo {.week_day = 1, .auditorium = 402, .group = 101};
    data[1] = LessonInfo {.week_day = 1, .auditorium = 402, .group = 101};
    Location *result;
    size_t size_result;
    int ret = task(data, 2, 101, &result, &size_result);
    EXPECT_EQ(0, ret);
    EXPECT_EQ(1, size_result);
    EXPECT_EQ(1, result[0].day);
    EXPECT_EQ(402, result[0].auditorium);
    free(result);
}

TEST(task, two_aud_in_diff_day) {
    LessonInfo data[2];
    data[0] = LessonInfo {.week_day = 1, .auditorium = 402, .group = 101};
    data[1] = LessonInfo {.week_day = 2, .auditorium = 402, .group = 101};
    Location *result;
    size_t size_result;
    int ret = task(data, 2, 101, &result, &size_result);
    EXPECT_EQ(0, ret);
    EXPECT_EQ(2, size_result);
    EXPECT_EQ(1, result[0].day);
    EXPECT_EQ(402, result[0].auditorium);
    EXPECT_EQ(2, result[1].day);
    EXPECT_EQ(402, result[1].auditorium);
    free(result);
}

TEST(task, no_problem) {
    LessonInfo data[2];
    data[0] = LessonInfo {.week_day = 1, .auditorium = 402, .group = 101};
    data[1] = LessonInfo {.week_day = 1, .auditorium = 503, .group = 101};
    Location *result;
    size_t size_result;
    int ret = task(data, 2, 101, &result, &size_result);
    EXPECT_EQ(0, ret);
    EXPECT_EQ(2, size_result);
    EXPECT_EQ(1, result[0].day);
    EXPECT_EQ(402, result[0].auditorium);
    EXPECT_EQ(1, result[1].day);
    EXPECT_EQ(503, result[1].auditorium);
    free(result);
}

TEST(task, diff_groups) {
    LessonInfo data[4];
    data[0] = LessonInfo {.week_day = 1, .auditorium = 402, .group = 101};
    data[1] = LessonInfo {.week_day = 2, .auditorium = 503, .group = 101};
    data[2] = LessonInfo {.week_day = 2, .auditorium = 605, .group = 203};
    data[3] = LessonInfo {.week_day = 3, .auditorium = 307, .group = 101};
    Location *result;
    size_t size_result;
    int ret = task(data, 4, 101, &result, &size_result);
    EXPECT_EQ(0, ret);
    EXPECT_EQ(3, size_result);
    EXPECT_EQ(1, result[0].day);
    EXPECT_EQ(402, result[0].auditorium);
    EXPECT_EQ(2, result[1].day);
    EXPECT_EQ(503, result[1].auditorium);
    EXPECT_EQ(3, result[2].day);
    EXPECT_EQ(307, result[2].auditorium);
    free(result);
}
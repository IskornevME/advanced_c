#ifndef TASK_TASK_H_
#define TASK_TASK_H_

#include <stddef.h>
#include "structure.h"

struct Location {
    int day;
    int auditorium;
};

int task(const struct LessonInfo *array, size_t size, int group, struct Location **res, size_t *size_res);

#endif  // TASK_TASK_H_

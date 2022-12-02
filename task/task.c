#include "io.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

int task(const struct LessonInfo *array, size_t size, int group, struct Location **res, size_t *size_res) {
    size_t prev = 0;
    *size_res = 0;

    if (array == NULL || size == 0) {
        return -1;
    }

    *res = malloc(size * sizeof(struct Location));

    if (*res == NULL) {
        return -1;
    }

    while (prev < size && array[prev].group != group) {
        prev++;
    }

    if (prev == size) {
        return 0;
    }

    (*res)[*size_res].day = array[prev].week_day;
    (*res)[*size_res].auditorium = array[prev].auditorium;
    (*size_res)++;

    for (size_t i = prev + 1; i < size; i++) {
        if (array[i].group != group) {
            continue;
        }

        if (array[i].week_day != array[prev].week_day) {
            (*res)[*size_res].day = array[i].week_day;
            (*res)[*size_res].auditorium = array[i].auditorium;
            (*size_res)++;

        } else if (array[i].auditorium != array[prev].auditorium) {
            (*res)[*size_res].day = array[i].week_day;
            (*res)[*size_res].auditorium = array[i].auditorium;
            (*size_res)++;
        }

        prev = i;
    }

    return 0;
}

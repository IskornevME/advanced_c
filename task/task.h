#ifndef TASK_H
#define TASK_H

#include <stddef.h>

struct Location {
    int day;
    int auditorium;
}; 

void task(struct Structure *array, size_t size, int group, struct Location *res, size_t *size_res);


#endif // TASK_H
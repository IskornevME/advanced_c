#ifndef DATABASE_IO_H_
#define DATABASE_IO_H_

#include "structure.h"
#include <stddef.h>

int input_from_file(const char *filename, struct LessonInfo **array, size_t *size);
void delete_memory(struct LessonInfo *array, size_t size);
// void print(struct LessonInfo structure);

#endif  // DATABASE_IO_H_

#ifndef IO_H
#define IO_H

#include "structure.h"
#include <stddef.h>

int input_from_file(const char *filename, struct Structure **array, size_t *size);
void delete_memory(struct Structure *array, size_t size);
void print(struct Structure structure);

#endif // IO_H 
#include "io.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct Structure *array;
    size_t size;
    int group = atoi(argv[2]);
    size_t size_res = 0;
    struct Location *res;
    
    if (argc == 1) {
        return -1;
    }

    if (input_from_file(argv[1], &array, &size) != 0) {
        return -1;
    }

    res = malloc(size * sizeof(struct Location));
    task(array, size, group, res, &size_res);

    for (size_t i = 0; i < size_res; i++) {
        printf("%d %d\n", res[i].day, res[i].auditorium);
    }

    delete_memory(array, size);
    free(res);
}
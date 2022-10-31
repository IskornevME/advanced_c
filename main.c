#include "io.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct LessonInfo *array;
    size_t size;
    int group;
    size_t size_res = 0;
    struct Location *res;

    if (argc != 3) {
        printf("Use: %s filename group\n", argv[0]);
        return -1;
    }

    group = atoi(argv[2]);

    if (input_from_file(argv[1], &array, &size) != 0) {
        return -1;
    }

    if (task(array, size, group, &res, &size_res) != 0) {
        printf("Something went wrong\n");
    } else {
        for (size_t i = 0; i < size_res; i++) {
            printf("%d %d\n", res[i].day, res[i].auditorium);
        }

        free(res);
    }

    delete_memory(array, size);
}

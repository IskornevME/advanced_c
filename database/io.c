#include "io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_LEN 1234

int input_from_file(const char *filename, struct LessonInfo **array, size_t *size) {
    FILE *file = fopen(filename, "r");
    char buf[BUF_LEN];
    int cur_pos = 0;

    if (file == NULL) {
        return -1;
    }

    *size = 0;

    while (fgets(buf, BUF_LEN, file) != NULL) {
        (*size)++;
    }

    *array = malloc((*size) * sizeof(struct LessonInfo));

    if (*array == NULL) {
        fclose(file);
        return -1;
    }

    rewind(file);

    while (fgets(buf, BUF_LEN, file) != NULL) {
        char *token;

        token = strtok(buf, ",");
        (*array)[cur_pos].week_day = atoi(token);

        token = strtok(NULL, ",");
        (*array)[cur_pos].start_time.hour = atoi(token) / 100;
        (*array)[cur_pos].start_time.min = atoi(token) % 100;

        token = strtok(NULL, ",");
        if (strcmp(token, "LEC") == 0) {
            (*array)[cur_pos].type = LECTURE;
        } else {
            (*array)[cur_pos].type = SEMINAR;
        }

        token = strtok(NULL, ",");
        (*array)[cur_pos].duration = atoi(token);

        token = strtok(NULL, ",");
        (*array)[cur_pos].name = malloc(strlen(token) + 1);
        strcpy((*array)[cur_pos].name, token);

        token = strtok(NULL, ",");
        (*array)[cur_pos].teacher = malloc(strlen(token) + 1);
        strcpy((*array)[cur_pos].teacher, token);

        token = strtok(NULL, ",");
        (*array)[cur_pos].auditorium = atoi(token);

        token = strtok(NULL, ",");
        (*array)[cur_pos].course = atoi(token);

        token = strtok(NULL, ",");
        (*array)[cur_pos].group = atoi(token);

        cur_pos++;
    }

    fclose(file);
    return 0;
}

void delete_memory(struct LessonInfo *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        free(array[i].name);
        free(array[i].teacher);
    }
    free(array);
}

// void print(struct LessonInfo structure) {
//     printf("Week day: %d\n", structure.week_day);
//     printf("Start time: %d:%02d\n", structure.start_time.hour, structure.start_time.min);
//     printf("Type of lesson: %s\n", structure.type == LECTURE ? "LECTURE" : "SEMINAR");
//     printf("Duration: %d\n", structure.duration);
//     printf("Name: %s\n", structure.name);
//     printf("teacher: %s\n", structure.teacher);
//     printf("auditorium: %d\n", structure.auditorium);
//     printf("course: %d\n", structure.course);
//     printf("group: %d\n", structure.group);
//     printf("\n");
// }

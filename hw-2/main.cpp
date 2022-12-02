#include "io.h"
// #include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

// int input_from_file(const char *filename, double *a, double *b);

int main(int argc, char *argv[]) {
    double a = 0;
    double b = 0;

    if (argc != 2) {
        printf("Use: %s filename\n", argv[0]);
        return -1;
    }


    if (input_from_file(argv[1], &a, &b) != 0) {
        return -1;
    }

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;


    // if (task(array, size, group, &res, &size_res) != 0) {
    //     printf("Something went wrong\n");
    // } else {
    //     for (size_t i = 0; i < size_res; i++) {
    //         printf("%d %d\n", res[i].day, res[i].auditorium);
    //     }

    //     free(res);
    // }

    // delete_memory(array, size);
}
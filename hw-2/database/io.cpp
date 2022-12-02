#include "io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


int input_from_file(const char *filename, double *a, double *b) {
    // FILE *file = fopen(filename, "r");
    // if (file == NULL) {
    //     return -1;
    // }
    ifstream file(filename); // окрываем файл для чтения
    if (file.is_open()){
        // getline(file, a);
        // getline(file, b);
        file >> *a;
        file >> *b;

        // cout << a << endl;
        // cout << b << endl;
    }
    else {
        cout << "File is not open" << endl;
    }

    file.close();     // закрываем файл
    // cout << "End of program" << endl;
    // fclose(file);
    return 0;
}
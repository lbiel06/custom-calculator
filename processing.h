#ifndef PROCESSING_H
#define PROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int lineLength(FILE *file) {
    int length = 0;
    int ch;
    long currentPos = ftell(file);
    while ((ch = fgetc(file)) != EOF && ch != '\n') {
        length++;
    }
    fseek(file, currentPos, SEEK_SET);
    return length;
}

size_t charToNumber(const char *a, int lenA, int base) {
    unsigned int result = 0;
    for (int i = 0; i < lenA; i++) {
        result = result * base + a[i];
    }
    return result;
}


#endif //PROCESSING_H

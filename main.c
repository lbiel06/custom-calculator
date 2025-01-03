#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arithmetic.h"
#include "processing.h"
#include "error.h"
#include "power.h"
#include "convertBase.h"


void writeNumber(FILE *f, char *number, int length) {
    for (int i = 0; i < length; i++) {
        if (number[i] < 10) {
            fprintf(f, "%c", '0' + number[i]); //  0-9
        } else {
            fprintf(f, "%c", 'A' + (number[i] - 10)); // A-F
        }
    }
    fprintf(f, "\n\n");
}

char *readNumberInBase(FILE *file, int base) {
    // Get the length of the current line
    int length = lineLength(file);
    if (length <= 0) {
        printf("nie udalo sie wczytac liczby\n");
        return NULL;
    }

    char *number = (char *)malloc((length + 1) * sizeof(char));
    if (!number) {
        perror("nie udalo sie zarezerowac pamieci");
        return NULL;
    }

    number[0] = 0;

    for (int i = 0; i < length; i++) {
        int ch = fgetc(file);

        if (ch == EOF || ch == '\n') {
            printf("nie udalo sie wczytac liczby\n");
            free(number);
            return NULL;
        }

        int value = -1;

        if (ch >= '0' && ch <= '9') value = ch - '0';          // '0'-'9'
        else if (ch >= 'A' && ch <= 'F') value = 10 + (ch - 'A'); // 'A'-'F'
        else if (ch >= 'a' && ch <= 'f') value = 10 + (ch - 'a'); // 'a'-'f'

        if (value == -1 || value >= base) {
            printf("nieprawidlowa cyfra '%c' dla liczby o podstawie %d\n", ch, base);
            free(number);
            return NULL;
        }

        number[i + 1] = value;
    }

    int ch = fgetc(file);
    if (ch != '\n' && ch != EOF) {
        while (ch != '\n' && ch != EOF) {
            ch = fgetc(file);
        }
    }

    return number;
}



int expectBlankLine(FILE *file) {
    int length = lineLength(file);
    if (length != 0) {
        printf("brak wymaganej pustej linii.\n");
        return 0;
    }
    fgetc(file);
    return 1;
}

void handleAdd(char *a, int lenA, char *b, int lenB, int base, FILE *out) {
    int lenAns = (lenA > lenB ? lenA : lenB);
    char *ans = (char *)calloc(lenAns,  sizeof(char));
    add(a, lenA, b, lenB, ans, lenAns, base);
    // display(ans, lenAns);
    writeNumber(out, ans, lenAns);
    free(ans);
}

void handleMul(char *a, int lenA, char *b, int lenB, int base, FILE *out) {
    int lenAns = lenA + lenB;
    char *ans = (char *)calloc(lenAns,  sizeof(char));
    mul(a, lenA, b, lenB, ans, lenAns, base);
    // display(ans, lenAns);
    writeNumber(out, ans, lenAns);
    free(ans);
}


int processBlock(FILE *file, FILE *out) {
    int base;
    char firstChar;

    if ((firstChar = fgetc(file)) == EOF) {
        return 0;
    }

    if (isdigit(firstChar)) {
        ungetc(firstChar, file); // Put the character back for fscanf
        if (fscanf(file, "%d", &base) == 1) {

            int ch;
            while ((ch = fgetc(file)) != '\n' && ch != EOF);

            if (base < 2 || base > 16) {
                printf("nieprawidlowa podstawa systemu");
                return 0;
            }

            if (!expectBlankLine(file)) return 0;

            int len1 = lineLength(file) + 1;
            char *num1 = readNumberInBase(file, base);
            if (!num1) return 0;


            int resultSize = len1 * ((int)log10(base) + 2);
            char *result = (char*)calloc(resultSize, sizeof(char));

            int resultLen = convertToBase10(num1, len1, base, result, resultSize);\

            // display(result, resultSize);
            writeNumber(out, result, resultSize);

            // Expect three blank lines after processing this block
            for (int i = 0; i < 3; i++) {
                if (!expectBlankLine(file)) return 0;
            }

            return 1;
        }
    } else {
        // Put back the character if it's not a digit
        ungetc(firstChar, file);
    }
    char line[10];

    if (!fgets(line, sizeof(line), file)) {
        // printf("Nieprawidlowe dane dzialania.\n");
        printf("nieprawidlowe dane dzialania\n");
        return 0;
    }

    char op;
    // int base;
    if (sscanf(line, "%c %d", &op, &base) != 2) {
        printf("nieprawidlowe dane dzialania\n");
        return 0;
    }

    if (base < 2 || base > 16) {
        printf("nieprawidlowa podstawa systemu");
        return 0;
    }

    if (!expectBlankLine(file)) return 0;

    int len1 = lineLength(file) + 1;
    char *num1 = readNumberInBase(file, base);
    if (!num1) return 0;

    if (!expectBlankLine(file)) {
        free(num1);
        return 0;
    }

    int len2 = lineLength(file) +1;
    char *num2 = readNumberInBase(file, base);
    if (!num2) {
        free(num1);
        return 0;
    }
    char *ans = NULL, *l = NULL, *m = NULL, *r = NULL, *h = NULL;
    int lenAns;

    switch (op) {
        case '+':
            handleAdd(num1, len1, num2, len2, base, out);
            break;
        case '*':
            handleMul(num1, len1, num2, len2, base, out);
            break;
        case '/':
            lenAns = len1;
            ans = (char *)calloc((lenAns),  sizeof(char));
            l = (char*)calloc(lenAns, sizeof(char));
            m = (char*)calloc(lenAns, sizeof(char));
            r = (char*)calloc(lenAns, sizeof(char));
            h = (char*)calloc(lenAns, sizeof(char));
            for (int i = 0; i < lenAns; i++) r[i] = num1[i];
            fulldiv(num1, len1, num2, len2, l, m, r, h, ans, base);
            // display(ans, lenAns);
            writeNumber(out, ans, lenAns);
            free(l);
            free(m);
            free(r);
            free(h);
            break;
        case '%':
            lenAns = len1;
            ans = (char *)calloc((lenAns),  sizeof(char));
            l = (char*)calloc(lenAns, sizeof(char));
            m = (char*)calloc(lenAns, sizeof(char));
            r = (char*)calloc(lenAns, sizeof(char));
            h = (char*)calloc(lenAns, sizeof(char));
            for (int i = 0; i < lenAns; i++) r[i] = num1[i];
            fulldiv(num1, len1, num2, len2, l, m, r, h, ans, base);
            char *t = (char*)calloc(len1, sizeof(char));
            char *t2 = (char*)calloc(len1, sizeof(char));
            mul(ans, lenAns, num2, len2, t, len1, base);
            sub(num1, len1, t, len1, t2, len1, base);
            // display(t2, len1);
            writeNumber(out, t2, len1);
        break;
        case '^':
            size_t x = charToNumber(num2, len2, base);
            lenAns = len1 * x;
            char *p = power(num1, len1, x, base);
            // display(p, lenAns);
            writeNumber(out, p, lenAns);
            break;

        default:
            printf("nieprawidlowy typ dzialania\n");
            free(num1);
            free(num2);
            free(ans);
            return 0;
    }

    free(num1);
    free(num2);
    free(ans);

    for (int i = 0; i < 3; i++) {
        if (!expectBlankLine(file)) {
            return 0;
        }
    }

    return 1;
}

void processInput(FILE *file, FILE *out) {
    while (processBlock(file, out)) {
        printf("wykonano dzialanie\n");
    }
}

int main(int argc, char *argv[]) {
    // const char *inputFileName = "input.txt";
    // const char *outputFileName = "out.txt";

    if (argc != 3) {
        printf("nieprawidlowe argumenty");
        return 1;
    }

    char inputFileName = argv[1];
    char outputFileName = argv[2];

    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("nie udalo sie otworzyc pliku\n");
        return EXIT_FAILURE;
    }

    FILE *outputFile = fopen(outputFileName, "w+");

    // Process the input
    processInput(inputFile, outputFile);

    // Close the file
    fclose(inputFile);
    fclose(outputFile);

    // int baseSystem = 10; // Decimal base
    // const char num[] = {3}; // Base number "3"
    // int lenBase = 1;
    //
    // const char exp[] = {4}; // Exponent "2"
    // int lenExp = 1;
    //
    // int lenResult = lenBase * 10; // Ensure enough space for the result
    // char *result = (char *)malloc(lenResult * sizeof(char));
    // if (result == NULL) {
    //     fprintf(stderr, "Memory allocation failed\n");
    //     return 1;
    // }
    //
    // power(num, lenBase, exp, lenExp, result, lenResult, baseSystem);
    //
    // display(result, lenResult);

    return EXIT_SUCCESS;
}

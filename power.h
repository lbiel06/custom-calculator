#include <string.h>
#include "arithmetic.h"

void initialize_one(char *num, int lenNum) {
    zeros(num, lenNum);
    num[lenNum - 1] = 1; // Set the last digit to 1
}
// void display(char *number, int length) {
//     for (int i = 0; i < length; i++) {
//         if (number[i] < 10) {
//             printf("%c", '0' + number[i]); //  0-9
//         } else {
//             printf("%c", 'A' + (number[i] - 10)); // A-F
//         }
//     }
//     printf("\n");
// }

void customMul(const char *a, int lenA, const char *b, int lenB, char *ans, int lenAns, int base) {
    // Alternatywna funkcja mnozenia wykorzystywania w potegowaniu
    for (int i = 0; i < lenAns; i++) ans[i] = 0;

    for (int i = 0; i < lenB; i++) {
        int carry = 0;
        for (int j = 0; j < lenA; j++) {
            int ansPos = lenAns - i - j - 1;
            if (ansPos < 0) continue;

            int next = b[lenB - i - 1] * a[lenA - j - 1] + ans[ansPos] + carry;
            ans[ansPos] = next % base;
            carry = next / base;
        }

        int ansPos = lenAns - i - lenA - 1;
        if (ansPos >= 0) ans[ansPos] += carry;
    }
}

char *power(char *num1, int lenNum1, int exp, int baseSystem) {
    int lenResult = lenNum1 * exp;

    char *normalizedNum1 = (char *)malloc(lenResult * sizeof(char));
    zeros(normalizedNum1, lenResult);
    memcpy(normalizedNum1 + (lenResult - lenNum1), num1, lenNum1);

    char *x = (char *)malloc(lenResult * sizeof(char));
    char *t = (char *)malloc(lenResult * sizeof(char));
    if (!x || !t) {
        exit(1);
    }

    memcpy(x, normalizedNum1, lenResult);


    for (int i = 1; i < exp; i++) {

        zeros(t, lenResult);
        customMul(x, lenResult, normalizedNum1, lenResult, t, lenResult, baseSystem);

        char *temp = x;
        x = t;
        t = temp;

    }


    free(normalizedNum1);
    free(t);

    return x;
}

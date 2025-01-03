#ifndef CONVERTBASE_H
#define CONVERTBASE_H

#include <stdio.h>
#include <string.h>

void add2(char *a, int lenA, char *b, int lenB, char *ans, int lenAns, int base) {
    for (int i = 1; i < lenAns; i++) {
        char nextA = 0, nextB = 0;
        if (i <= lenA)
            nextA = a[lenA - i];
        if (i <= lenB)
            nextB = b[lenB - i];
        char sum = nextA + nextB + ans[lenAns - i];
        ans[lenAns - i] = sum % base;
        ans[lenAns - i - 1] = sum / base;
    }
}

void mul2(char *a, int lenA, char *b, int lenB, char *ans, int lenAns, int base) {
    // Alternatywna funkcja mnozenia
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

static void copyNumber(const char *src, int srcLen, char *dest, int *destLen) {
    for (int i = 0; i < srcLen; i++) dest[i] = src[i];
    *destLen = srcLen;
}

int findLength(const char *num, int maxLen) {
    int i = maxLen - 1;
    while (i > 0 && num[i] == 0) i--;
    return i + 1;
}

int computeLength(char *arr, int maxLen) {
    int i = maxLen - 1;
    while (i > 0 && arr[i] == 0) i--;
    return i + 1;
}

int convertToBase10(char *src, int srcLen, int sBase, char *result, int resultSize) {
    char sBaseArr[64];
    memset(sBaseArr, 0, sizeof(sBaseArr));
    int sBaseLen = 0;

    {
        char tempArr[64];
        int tempLen = 0;
        int x = sBase;

        if (x == 0) {
            tempArr[0] = 0;
            tempLen = 1;
        } else {
            while (x > 0) {
                tempArr[tempLen++] = x % 10;
                x /= 10;
            }
        }

        for (int i = 0; i < tempLen; i++) {
            sBaseArr[tempLen - 1 - i] = tempArr[i];
        }
        sBaseLen = tempLen;
    }

    for (int i = 0; i < resultSize; i++) result[i] = 0;
    int resultLen = 1;

    char *temp = (char*)calloc(resultSize, sizeof(char));
    char *multiplied = (char*)calloc(resultSize, sizeof(char));
    char *digitArr = (char*)calloc(1, sizeof(char));

    for (int i = 0; i < srcLen; i++) {
        for (int j = 0; j < resultSize; j++) multiplied[j] = 0;
        mul2(result, resultLen, sBaseArr, sBaseLen, multiplied, resultSize, 10);
        int multipliedLen = computeLength(multiplied, resultSize);

        digitArr[0] = src[i];
        for (int j = 0; j < resultSize; j++) temp[j] = 0;
        add2(multiplied, multipliedLen, digitArr, 1, temp, resultSize, 10);
        int tempLen = computeLength(temp, resultSize);

        for (int j = 0; j < resultSize; j++) result[j] = 0;
        memcpy(result, temp, tempLen);
        resultLen = tempLen;
    }

    free(temp);
    free(multiplied);
    free(digitArr);

    return resultLen;
}

#endif //CONVERTBASE_H

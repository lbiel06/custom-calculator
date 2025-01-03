#ifndef ARITHMETIC_H
#define ARITHMETIC_H

void display(char *number, int length) {
    for (int i = 0; i < length; i++) {
        if (number[i] < 10) {
            printf("%c", '0' + number[i]); //  0-9
        } else {
            printf("%c", 'A' + (number[i] - 10)); // A-F
        }
    }
    printf("\n");
}

void add(char *a, int lenA, char *b, int lenB, char *ans, int lenAns, int base) {
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

void sub(char *a, int lenA, char *b, int lenB, char *ans, int lenAns, int base) {
    int borrow = 0;
    for (int i = 1; i < lenAns; i++) {
        char nextA = 0, nextB = 0;
        if (i <= lenA)
            nextA = a[lenA - i];
        if (i <= lenB)
            nextB = b[lenB - i];
        char diff = nextA - nextB - borrow;
        if (diff < 0) { // -1
            borrow = 1;;
            diff += base;
        } else borrow = 0;
        ans[lenAns - i] = diff;
    }
}

void mul(char *a, int lenA, char *b, int lenB, char *ans, int lenAns, int base) {
    for (int i = 0; i < lenB; i++) {
        for (int j = 0; j < lenA; j++) {
            char next = b[lenB - i - 1] * a[lenA - j - 1] + ans[lenAns - i - j - 1];
            ans[lenAns - i - j - 1] = next % base;
            ans[lenAns - i - j - 2] = (next / base) + ans[lenAns - i - j - 2];
        }
    }
}

void rsh(char *a, int lenA) {
    // Right shift in any base
    char next = 0;
    char t;
    for (int i = 0; i < lenA; i++) {
        t = a[i];
        a[i] = next;
        next = t;
    }
}

void div2(char *a, int lenA, char *ans, int lenAns, int base) {
    // Integer division by 2
    char b = base / 2;
    mul(a, lenA, &b, 1, ans, lenAns, base);


    rsh(ans, lenAns);
}

void copyArray(char *a, char *b, int len) {
    // Copy digits from a to b
    for (int i = 0; i < len; i++)
        b[i] = a[i];
}

void zeros(char *a, int lenA) {
    for (int i = 0; i < lenA; i++)
        a[i] = 0;
}


int firstDigit(char *a, int lenA) {
    for (int i = 0; i < lenA; i++) {
        if (a[i] != 0)
            return i;
    }
    return lenA;
}

int le(char *a, int lenA, char *b, int lenB) {
    // Less equal operator
    int firstA = firstDigit(a, lenA);
    int firstB = firstDigit(b, lenB);
    if (lenA - firstA > lenB - firstB) return 0;
    if (lenA - firstA < lenB - firstB) return 1;
    for (int i = 0; i < lenA - firstA; i++) {
        if (a[firstA + i] > b[firstB + i])
            return 0;
        if (a[firstA + i] < b[firstB + i])
            return 1;
    }
    return 1;
}

void fulldiv(char *a, int lenA, char *b, int lenB, char *left, char *mid, char *right, char *h, char *ans, int base) {
    while (le(left, lenA, right, lenA) == 1) {
        zeros(h, lenA);
        add(left, lenA, right, lenA, h, lenA, base);
        zeros(mid, lenA);
        div2(h, lenA, mid, lenA, base);
        zeros(h, lenA);
        mul(mid, lenA, b, lenB, h, lenA, base);
        char x = 1;
        if (le(h, lenA, a, lenA) == 1) {
            copyArray(mid, ans, lenA);
            zeros(left, lenA);
            add(mid, lenA, &x, 1, left, lenA, base);
        } else {
            zeros(right, lenA);
            sub(mid, lenA, &x, 1, right, lenA, base);
        }
    }
}


#endif //ARITHMETIC_H

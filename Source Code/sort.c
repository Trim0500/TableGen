#include "generate.h"
#include "sort.h"

int CompareStrings(const void *a, const void *b) {
    char *arg1 = (char *)a;
    char *arg2 = (char *)b;

    int arg1Size = 0;
    for (int i = 0; arg1[i] != '\0'; i++)
    {
        arg1Size = i + 1;
    }

    int arg2Size = 0;
    for (int i = 0; arg1[i] != '\0'; i++)
    {
        arg2Size = i + 1;
    }

    int sizeDifference = (arg1Size - arg2Size);
    if(sizeDifference != 0) {
        return sizeDifference;
    }
    else {
        for (int i = 0; i < arg1Size; i++)
        {
            int compareResult = (arg1[i] - arg2[i]);
            if(compareResult != 0) {
                return compareResult;
            }
        }

        return 0;
    }
}

int CompareStructUserId(const void *a, const void *b) {
    struct TableRow *arg1 = (struct TableRow *)a;
    struct TableRow *arg2 = (struct TableRow *)b;

    return (arg1->UserId - arg2->UserId);
}

int CompareStructFirstName(const void *a, const void *b) {
    struct TableRow *arg1 = (struct TableRow *)a;
    struct TableRow *arg2 = (struct TableRow *)b;

    return CompareStrings(arg1->FirstName, arg2->FirstName);
}

int CompareStructLastName(const void *a, const void *b) {
    struct TableRow *arg1 = (struct TableRow *)a;
    struct TableRow *arg2 = (struct TableRow *)b;

    return CompareStrings(arg1->LastName, arg2->LastName);
}

int CompareStructCountry(const void *a, const void *b) {
    struct TableRow *arg1 = (struct TableRow *)a;
    struct TableRow *arg2 = (struct TableRow *)b;

    return CompareStrings(arg1->Country, arg2->Country);
}

int CompareStructPhoneNum(const void *a, const void *b) {
    struct TableRow *arg1 = (struct TableRow *)a;
    struct TableRow *arg2 = (struct TableRow *)b;

    return CompareStrings(arg1->PhoneNum, arg2->PhoneNum);
}

int CompareStructEmail(const void *a, const void *b) {
    struct TableRow *arg1 = (struct TableRow *)a;
    struct TableRow *arg2 = (struct TableRow *)b;

    return CompareStrings(arg1->Email, arg2->Email);
}

int CompareStructSIN(const void *a, const void *b) {
    struct TableRow *arg1 = (struct TableRow *)a;
    struct TableRow *arg2 = (struct TableRow *)b;

    return (arg1->SIN - arg2->SIN);
}

int CompareStructPassword(const void *a, const void *b) {
    struct TableRow *arg1 = (struct TableRow *)a;
    struct TableRow *arg2 = (struct TableRow *)b;

    return CompareStrings(arg1->Password, arg2->Password);
}

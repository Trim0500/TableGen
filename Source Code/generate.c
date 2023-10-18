#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "generate.h"
#include "io.h"
#include "sort.h"

#define STRING_MAX_LIMIT 2048

#define FIRST_NAME_FILE_LOCATION "..\\..\\Resources\\first_names.txt"
#define LAST_NAME_FILE_LOCATION "..\\..\\Resources\\last_names.txt"
#define COUNTRY_NAME_FILE_LOCATION "..\\..\\Resources\\countries.txt"
#define EMAIL_SUFFIX_FILE_LOCATION "..\\..\\Resources\\email_suffixes.txt"

#define NAME_LOWER_RANGE 0
#define NAME_UPPER_RANGE 999

#define COUNTRY_LOWER_RANGE 0
#define COUNTRY_UPPER_RANGE 194

#define EMAIL_SUFFIX_LOWER_RANGE 0
#define EMAIL_SUFFIX_UPPER_RANGE 99

#define PHONE_INDEX_LOWER_RANGE 0
#define PHONE_INDEX_UPPER_RANGE 9
#define PHONE_LINE_LOWER_RANGE 1000
#define PHONE_LINE_UPPER_RANGE 9999

#define SIN_LOWER_RANGE 100000000
#define SIN_UPPER_RANGE 999999999

#define PASSWORD_LENGTH_LOWER_RANGE 6
#define PASSWORD_LENGTH_UPPER_RANGE 16
#define PASSWORD_CHARACTER_LOWER_RANGE 33
#define PASSWORD_CHARACTER_UPPER_RANGE 126

void SortStructs(struct TableRow *structList, int listSize, int sortByNumber) {
    switch (sortByNumber)
    {
        case 1:
            qsort(structList, listSize, sizeof(struct TableRow), CompareStructUserId);
            
            break;
        case 2:
            qsort(structList, listSize, sizeof(struct TableRow), CompareStructFirstName);

            break;
        case 3:
            qsort(structList, listSize, sizeof(struct TableRow), CompareStructLastName);

            break;
        case 4:
            qsort(structList, listSize, sizeof(struct TableRow), CompareStructCountry);

            break;
        case 5:
            qsort(structList, listSize, sizeof(struct TableRow), CompareStructPhoneNum);

            break;
        case 6:
            qsort(structList, listSize, sizeof(struct TableRow), CompareStructEmail);

            break;
        case 7:
            qsort(structList, listSize, sizeof(struct TableRow), CompareStructSIN);

            break;
        case 8:
            qsort(structList, listSize, sizeof(struct TableRow), CompareStructPassword);

            break;
        default:
            break;
    }
}

char* ToLowerString(char* targetString) {
    static char lowerCaseString[STRING_MAX_LIMIT];
    for(int i = 0; lowerCaseString[i] != '\0'; i++) {
        lowerCaseString[i] = '\0';
    }
    

    for (int i = 0; targetString[i] != '\0'; i++)
    {
        char lowerCaseLetter = tolower(targetString[i]);
        lowerCaseString[i] = lowerCaseLetter;
    }
    
    return lowerCaseString;
}

struct TableRow* BuildStructs(int *columnOptionsSelected,
                            int sizeOfList,
                            int rowCount,
                            char **firstNameList,
                            char **lastNameList,
                            char **countryNameList,
                            char **emailSuffixList) {
    int phoneIndexArray[10] = { 398, 270, 925, 867, 209, 429, 908, 997, 444, 219 };

    struct TableRow *recordList = (struct TableRow *)malloc(rowCount * sizeof(struct TableRow));

    for (int i = 0; i < rowCount; i++)
    {
        recordList[i].UserId = 0;
        recordList[i].FirstName = NULL;
        recordList[i].LastName = NULL;
        recordList[i].Country = NULL;
        recordList[i].PhoneNum = NULL;
        recordList[i].Email = NULL;
        recordList[i].SIN = 0;
        recordList[i].Password = NULL;

        bool emailColumnChosen = false;

        for (int j = 0; j < sizeOfList; j++)
        {
            switch (columnOptionsSelected[j]) {
                case 1:
                    recordList[i].UserId = i + 1;

                    break;
                case 2:
                    int firstNameRandomIndex = (rand() % (NAME_UPPER_RANGE - NAME_LOWER_RANGE + 1)) + NAME_LOWER_RANGE;
                    recordList[i].FirstName = firstNameList[firstNameRandomIndex];

                    break;
                case 3:
                    int lastNameRandomIndex = (rand() % (NAME_UPPER_RANGE - NAME_LOWER_RANGE + 1)) + NAME_LOWER_RANGE;
                    recordList[i].LastName = lastNameList[lastNameRandomIndex];

                    break;
                case 4:
                    int countryRandomIndex = (rand() % (COUNTRY_UPPER_RANGE - COUNTRY_LOWER_RANGE + 1)) + COUNTRY_LOWER_RANGE;
                    recordList[i].Country = countryNameList[countryRandomIndex];

                    break;
                case 5:
                    int randomPhoneIndex = (rand() % (PHONE_INDEX_UPPER_RANGE - PHONE_INDEX_LOWER_RANGE + 1)) + PHONE_INDEX_LOWER_RANGE;
                    int phoneIndexChosen = phoneIndexArray[randomPhoneIndex];

                    int randomPhoneLine = (rand() % (PHONE_LINE_UPPER_RANGE - PHONE_LINE_LOWER_RANGE + 1)) + PHONE_LINE_LOWER_RANGE;

                    char phoneIndex[10];
                    sprintf(phoneIndex, "%d", phoneIndexChosen);

                    char phoneLine[10];
                    sprintf(phoneLine, "%d", randomPhoneLine);

                    char *phoneNum = (char *)calloc(9, sizeof(char));

                    for(int i = 0; i < 8; i++) {
                        if(i >= 0 && i < 3) {
                            phoneNum[i] = phoneIndex[i];
                        }
                        else if(i == 3) {
                            phoneNum[i] = '-';
                        }
                        else {
                            phoneNum[i] = phoneLine[i - 4];
                        }
                    }
                    
                    recordList[i].PhoneNum = phoneNum;

                    break;
                case 6:
                    emailColumnChosen = true;

                    break;
                case 7:
                    int randomSIN = (rand() % (SIN_UPPER_RANGE - SIN_LOWER_RANGE + 1)) + SIN_LOWER_RANGE;
                    recordList[i].SIN = randomSIN;

                    break;
                case 8:
                    int randomPasswordLength = (rand() % (PASSWORD_LENGTH_UPPER_RANGE - PASSWORD_LENGTH_LOWER_RANGE + 1)) + PASSWORD_LENGTH_LOWER_RANGE;

                    char *randomPasswordPointer = (char *)calloc(randomPasswordLength + 1, sizeof(char));

                    for (int k = 0; k < randomPasswordLength; k++)
                    {
                        char randomCharacter;
                        do {
                            int randomNumber = (rand() % (PASSWORD_CHARACTER_UPPER_RANGE - PASSWORD_CHARACTER_LOWER_RANGE + 1)) + PASSWORD_CHARACTER_LOWER_RANGE;
                            randomCharacter = randomNumber;
                        } while (randomCharacter == 44);

                        randomPasswordPointer[k] = randomCharacter;
                    }

                    recordList[i].Password = randomPasswordPointer;

                    break;
                default:
                    break;
            }
        }

        if(emailColumnChosen) {
            int randomEmailSuffixIndex = (rand() % (EMAIL_SUFFIX_UPPER_RANGE - EMAIL_SUFFIX_LOWER_RANGE + 1)) + EMAIL_SUFFIX_LOWER_RANGE;
            char *emailSuffix = emailSuffixList[randomEmailSuffixIndex];

            char *email = (char *)calloc(STRING_MAX_LIMIT, sizeof(char));

            if(recordList[i].FirstName != NULL && recordList[i].LastName != NULL) {
                char lowerCaseNameCharacter = tolower(recordList[i].FirstName[0]);

                char *lowerCaseLastName = ToLowerString(recordList[i].LastName);

                email[0] = lowerCaseNameCharacter;
                strcat(email, lowerCaseLastName);
            }
            else if(recordList[i].FirstName != NULL) {
                int lastNameRandomIndex = (rand() % (NAME_UPPER_RANGE - NAME_LOWER_RANGE + 1)) + NAME_LOWER_RANGE;
                char *randomLastName = lastNameList[lastNameRandomIndex];

                char lowerCaseNameCharacter = tolower(recordList[i].FirstName[0]);

                char *lowerCaseLastName = ToLowerString(randomLastName);

                email[0] = lowerCaseNameCharacter;
                strcat(email, lowerCaseLastName);
            }
            else if(recordList[i].LastName != NULL) {
                int firstNameRandomIndex = (rand() % (NAME_UPPER_RANGE - NAME_LOWER_RANGE + 1)) + NAME_LOWER_RANGE;
                char randomFirstNameCharacter = firstNameList[firstNameRandomIndex][0];
                char lowerCaseNameCharacter = tolower(randomFirstNameCharacter);

                char *lowerCaseLastName = ToLowerString(recordList[i].LastName);

                email[0] = lowerCaseNameCharacter;
                strcat(email, lowerCaseLastName);
            }
            else {
                int firstNameRandomIndex = (rand() % (NAME_UPPER_RANGE - NAME_LOWER_RANGE + 1)) + NAME_LOWER_RANGE;
                char randomFirstNameCharacter = firstNameList[firstNameRandomIndex][0];

                int lastNameRandomIndex = (rand() % (NAME_UPPER_RANGE - NAME_LOWER_RANGE + 1)) + NAME_LOWER_RANGE;
                char *randomLastName = lastNameList[lastNameRandomIndex];

                char lowerCaseNameCharacter = tolower(randomFirstNameCharacter);

                char *lowerCaseLastName = ToLowerString(randomLastName);

                email[0] = lowerCaseNameCharacter;
                strcat(email, lowerCaseLastName);
            }

            strcat(email, "@");
            strcat(email, emailSuffix);
            recordList[i].Email = email;
        }
    }

    int sortByColumnNumber = columnOptionsSelected[0];
    SortStructs(recordList, rowCount, sortByColumnNumber);

    return recordList;
}

void BuildCSVOutputAndWriteToFile(int recordSize, int optionCount, int *optionList, struct TableRow *tableRowList, char *fileName) {
    char *headerString = (char *)calloc(STRING_MAX_LIMIT, sizeof(char));

    for (int i = -1; i < recordSize; i++)
    {
        char *stringRecordOutput;
        if(i != -1) {
            stringRecordOutput = (char *)calloc(STRING_MAX_LIMIT, sizeof(char));
        }

        for (int j = 0; j < optionCount; j++)
        {
            switch (optionList[j]) {
                case 1:
                    if(i != -1) {
                        char stringUserId[9];
                        sprintf(stringUserId, "%d", tableRowList[i].UserId);

                        strcat(stringUserId, ", ");

                        strcat(stringRecordOutput, stringUserId);
                    }
                    else {
                        strcat(headerString, "UserId, ");                     
                    }
                    
                    break;
                case 2:
                    if(i != -1) {
                        char stringFirstName[STRING_MAX_LIMIT];
                        strcpy(stringFirstName, tableRowList[i].FirstName);

                        strcat(stringFirstName, ", ");

                        strcat(stringRecordOutput, stringFirstName);
                    }
                    else {
                        strcat(headerString, "FirstName, ");
                    }

                    break;
                case 3:
                    if(i != -1) {
                        char stringLastName[STRING_MAX_LIMIT];
                        strcpy(stringLastName, tableRowList[i].LastName);

                        strcat(stringLastName, ", ");

                        strcat(stringRecordOutput, stringLastName);
                    }
                    else {
                        strcat(headerString, "LastName, ");
                    }

                    break;
                case 4:
                    if(i != -1) {
                        char stringCountry[STRING_MAX_LIMIT];
                        strcpy(stringCountry, tableRowList[i].Country);

                        strcat(stringCountry, ", ");

                        strcat(stringRecordOutput, stringCountry);
                    }
                    else {
                        strcat(headerString, "Country, ");
                    }

                    break;
                case 5:
                    if(i != -1) {
                        char stringPhoneNum[10];
                        strcpy(stringPhoneNum, tableRowList[i].PhoneNum);

                        strcat(stringPhoneNum, ", ");

                        strcat(stringRecordOutput, stringPhoneNum);

                        free(tableRowList[i].PhoneNum);
                    }
                    else {
                        strcat(headerString, "PhoneNum, ");
                    }

                    break;
                case 6:
                    if(i != -1) {
                        char stringEmail[STRING_MAX_LIMIT];
                        strcpy(stringEmail, tableRowList[i].Email);

                        strcat(stringEmail, ", ");

                        strcat(stringRecordOutput, stringEmail);

                        free(tableRowList[i].Email);
                    }
                    else {
                        strcat(headerString, "Email, ");
                    }

                    break;
                case 7:
                    if(i != -1) {
                        char stringSIN[11];
                        sprintf(stringSIN, "%d", tableRowList[i].SIN);

                        strcat(stringSIN, ", ");

                        strcat(stringRecordOutput, stringSIN);
                    }
                    else {
                        strcat(headerString, "SIN, ");
                    }

                    break;
                case 8:
                    if(i != -1) {
                        char stringPassword[18];
                        strcpy(stringPassword, tableRowList[i].Password);

                        strcat(stringPassword, ", ");

                        strcat(stringRecordOutput, stringPassword);

                        free(tableRowList[i].Password);
                    }
                    else {
                        strcat(headerString, "Password, ");
                    }

                    break;
                default:
                    break;
            }
        }

        if(i != -1) {
            strcat(stringRecordOutput, "\n");

            WriteToFile(fileName, stringRecordOutput, "a");

            free(stringRecordOutput);
        }
        else {
            strcat(headerString, "\n");

            WriteToFile(fileName, headerString, "w");

            free(headerString);
        }
    }
}

void InitColumnOptionsMenu() {
    printf("Column Options\n");

    printf("--------------\n");

    printf("1. User ID\t\t5. Phone Number\n");
    printf("2. First name\t\t6. Email address\n");
    printf("3. Last name\t\t7. SIN\n");
    printf("4. Country\t\t8. Password\n\n");

    printf("Enter column list (comma-seperated, no spaces): ");

    char keyboardOptionsSelectionList[15];
    do {
        scanf("%s", keyboardOptionsSelectionList);
    } while (keyboardOptionsSelectionList[0] == '\n');

    char *columnOptionListCopy = (char *)calloc(STRING_MAX_LIMIT, sizeof(char));
    strcat(columnOptionListCopy, keyboardOptionsSelectionList);

    int sizeOfOptionList = 0;
    for (int i = 0; keyboardOptionsSelectionList[i] != '\0'; i++) {
        if(keyboardOptionsSelectionList[i] != ',') {
            sizeOfOptionList++;
        }
    }
    int *parsedOptionList = (int *)malloc(sizeof(int) * sizeOfOptionList);
    
    char *token = strtok(keyboardOptionsSelectionList, ",");
    int parsedValue = atoi(token);

    int i = 0;
    parsedOptionList[i] = parsedValue;
    while(token != NULL) {
        i++;

        token = strtok(NULL, ",");
        if(token == NULL) {
            break;
        }

        parsedValue = atoi(token);
        parsedOptionList[i] = parsedValue;
    }

    printf("\nEnter row count (1 < n < 1M): ");

    char keyboardRowCountInput[7];
    do {
        scanf("%s", keyboardRowCountInput);
    } while (keyboardRowCountInput[0] == '\n');
    int rowCountInput = atoi(keyboardRowCountInput);

    printf("\nEnter a file name (no suffix): ");

    char keyboardFileNameInput[STRING_MAX_LIMIT];
    do {
        scanf("%s", keyboardFileNameInput);
    } while (keyboardFileNameInput[0] == '\n');

    printf("\nSummary of properties:\n");

    printf(" Columns: %s\n Row count: %d\n File name: %s\n\n", columnOptionListCopy, rowCountInput, keyboardFileNameInput);

    free(columnOptionListCopy);

    // Note that these directories will absolutely have to change for the docker build
    char **firstNameList = ReadFileContent(FIRST_NAME_FILE_LOCATION, 1000);

    char **lastNameList = ReadFileContent(LAST_NAME_FILE_LOCATION, 1000);

    char **countryNameList = ReadFileContent(COUNTRY_NAME_FILE_LOCATION, 195);

    char **emailSuffixList = ReadFileContent(EMAIL_SUFFIX_FILE_LOCATION, 100);
    struct TableRow *tableRows = BuildStructs(parsedOptionList, sizeOfOptionList, rowCountInput, firstNameList, lastNameList, countryNameList, emailSuffixList);

    BuildCSVOutputAndWriteToFile(rowCountInput, sizeOfOptionList, parsedOptionList, tableRows, keyboardFileNameInput);

    for (int i = 0; i < 1000; i++)
    {
        free(firstNameList[i]);
        free(lastNameList[i]);
    }

    for(int i = 0; i < 195; i++) {
        free(countryNameList[i]);
    }
    
    for(int i = 0; i < 100; i++) {
        free(emailSuffixList[i]);
    }

    free(firstNameList);
    free(lastNameList);
    free(countryNameList);
    free(emailSuffixList);

    free(tableRows);
    free(parsedOptionList);

    printf("Table written successfully to %s.csv\n\n", keyboardFileNameInput);
    
    printf("Press 'c' or 'C' to continue: ");

    char keyboardContinueInput[1];
    do{
        scanf("%s", keyboardContinueInput);
    } while (keyboardContinueInput[0] != 'c' && keyboardContinueInput[0] != 'C');

    system("cls");

    InitTableGenMenu();
}

void InitTableGenMenu() {
    printf("TableGen Menu\n");

    printf("-------------\n");

    printf("1. Generate new table\n");
    printf("2. Exit\n\n");

    printf("Selection: ");

    char keyboardSelection[1];
    do {
        scanf("%s", keyboardSelection);
    } while (keyboardSelection[0] == '\n');
    int menuSelection = atoi(keyboardSelection);

    if(menuSelection == 2) {
        printf("Goodbye and thanks for using TableGen\n\n");

        printf("Press any key to exit...");

        char keyboardExitCharacter[1];
        do {
            scanf("%s", keyboardExitCharacter);
        } while (keyboardExitCharacter[0] == '\n');
    }
    else {
        system("cls"); // Might have to change to clear when doing the docker build

        InitColumnOptionsMenu();
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

#define STRING_MAX_LIMIT 2048

#define FILE_LOCATION_PREFIX "..\\..\\Output\\"

char** ReadFileContent(char* fileLocation, int stringCount) {
    char **stringListPointer = malloc(stringCount * sizeof(char *));

    FILE* filePointer = fopen(fileLocation, "r");
    if(filePointer == NULL) {
        printf("[TableGen/InitTableGenMenu] Failed to find the file for first names, exiting");

        exit(0);
    }
    else {
        for(int i = 0; i < stringCount; i++) {
            char *tempStringPointer = (char *)malloc(STRING_MAX_LIMIT * sizeof(char));

            char stringText[STRING_MAX_LIMIT];
            fgets(stringText, STRING_MAX_LIMIT, filePointer);
            strcpy(tempStringPointer, strtok(stringText, "\n"));

            stringListPointer[i] = tempStringPointer;
        }

        fclose(filePointer);

        return stringListPointer;
    }
}

void WriteToFile(char *fileName, char *outputToWrite, char *fileOpenMode) {
    char fileLocation[STRING_MAX_LIMIT];
    strcpy(fileLocation, FILE_LOCATION_PREFIX);
    strcat(fileLocation, fileName);
    strcat(fileLocation, ".csv");
    FILE *filePointer = fopen(fileLocation, fileOpenMode);

    fprintf(filePointer, "%s", outputToWrite);

    fclose(filePointer);
}
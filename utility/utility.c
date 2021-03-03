#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *addExtentitonToFileName(char *fileName)
{
    char *fileNameWithExtantion = NULL;
    int extentionLength = 4; /* .as + \0*/
    int fileNameLength = strlen(fileName);

    fileNameWithExtantion = (char *)malloc(fileNameLength + extentionLength);
    strcpy(fileNameWithExtantion, fileName);
    return strcat(fileNameWithExtantion, ".as");
}

/*
Thia function checks if a file can be opend and that it has .as extention.
return -1 if error opening the file otherwise returns 1
*/
int checkFiles(int length, char **fileNames)
{
    int i = 1;
    FILE *fp;

    for (; i < length; i++)
    {
        char *fileNameWithAsExtention = addExtentitonToFileName(*(fileNames + i));
        fp = fopen(fileNameWithAsExtention, "r");
        if (fp == NULL)
        {
            printf("Error: File %s, cant be opend. make sure that the file: %s exist and has .as extention\n", *(fileNames + i), *(fileNames + i));
            free(fileNameWithAsExtention);
            return -1;
        }
        free(fileNameWithAsExtention);
        fclose(fp);
    }

    return 1;
}

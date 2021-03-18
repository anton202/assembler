#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *addExtentitonToFileName(char *fileName)
{
    char *fileNameWithExtantion = NULL;
    int extentionLength = 4; /* .as + \0*/
    int fileNameLength = strlen(fileName);

    fileNameWithExtantion = (char *)malloc(fileNameLength + extentionLength);
    strcpy(fileNameWithExtantion, fileName);
    return strcat(fileNameWithExtantion, ".as");
}

static int checkForFileExtention(char *fileName)
{
    if (strchr(fileName, '.') != NULL)
    {
        return 1;
    }
    return 0;
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
        char *fileNameWithAsExtention = NULL;

        if (checkForFileExtention(*(fileNames + i)))
        {
            printf("\nError: Please enter file name without extention.\n");
            return -1;
        }

        fileNameWithAsExtention = addExtentitonToFileName(*(fileNames + i));
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

char *convertToBinary(int number)
{
    int i = 11;
    char *numArray = (char *)malloc(12);

    if (numArray == NULL)
    {
        printf("Error: allocating memory space");
        exit(0);
    }

    do
    {
        numArray[i] = number % 2;
        i--;
    } while ((number /= 2) > 0);

    return numArray;
}

char *twosComplement(char *number)
{
    int numberLength = 12;
    int i = 0;

    for (; i < numberLength; i++)
    {
        if (number[i] == 0)
        {
            number[i] = 1;
        }
        else
        {
            number[i] = 0;
        }
    }

    for (i = 11; i >= 0; i--)
    {
        if (number[i] == 0)
        {
            number[i] = 1;
            return number;
        }
        else
        {
            number[i] = 0;
        }
    }
    return number;
}

char *convertNumberToBinary(int number)
{
    char *pNumber = NULL;

    if (number > 0)
    {
        return convertToBinary(number);
    }
    pNumber = convertToBinary(-(number));
    return twosComplement(pNumber);
}


int isImmedtiateOperand(char *operand, int lineNumber)
{
    int i = 1;
    int sign = 1;
    int k = 0;
    char numberString[80];

    if (*operand != '#')
    {
        return -1;
    }

    if (*(operand + i) == '-')
    {
        sign = -1;
        i++;
    }
    else if (*(operand + i) == '+')
    {
        i++;
    }

    while (isdigit(*(operand + i)))
    {
        numberString[k] = *(operand + i);
        i++;
        k++;
    }

    numberString[k] = '\0';

    if(*(operand + i) != '\0')
    {
        printf("number line %d: Error: Iligal number %s",lineNumber, operand);
        return -1;
    }

    if(atoi(numberString) > 2047 || atoi(numberString) < -2047)
    {
         printf("number line %d: Error: number %d is to big or to small",lineNumber, atoi(numberString));
        return -1;
    }

    return sign * atoi(numberString);

}

int getOperandsAddressingMode(char *operand,int lineNumber)
{
    if (isImmedtiateOperand(operand,lineNumber) >= 0)
    {
        return 0; /*addressing mode 0*/
    }
    return 0;
}


char *readOperand(char *line, int *lineIndex, int lineNumber)
{
    int i = *lineIndex;
    int c, k = 0;
    char *operand = (char *)malloc(80);

    while (isspace(*(line + i)))
    {
        i++;
    }

    while ((c = *(line + i)) != ' ' && c != ',' && c != '\0')
    {
        operand[k++] = c;
    }

    operand[k] = '\0';
    *lineIndex = i;
    return operand;
}


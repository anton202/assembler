#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../tables/tables.h"
#include "../tables/symbolTable/symbolTable.h"

#define MAX_NUMBER 2047
#define MIN_NUMBER -2047
#define NUMBER_LENGTH 4
#define MAX_SYMBOL_LENGTH 31

/*
check if first input in the given line is a symbol decleration.
if its a symbol decleration, the function saves the symbol and advances the line pointer
to the end of the decleration.
return: NULL if no symbol decleration otherwise retrun the symbol.
*/
char *isSymbol(char *line, int *lineIndex)
{
    int c, i = 0;
    int k = 0;
    int j = 0;
    char *symbol;

    /*skip white space*/
    while (isspace(*(line + k)))
    {
        k++;
    }
    /*add && != EOF becuse you might get a file that containes only one word*/
    while ((c = *(line + k)) != ' ' && c != ':')
    {
        i++;
        k++;
    }

    if (c != ':')
    {
        return NULL;
    }

    i -= 1;
    k -= 1;
    symbol = (char *)malloc(i + 1);

    if (symbol != NULL)
    {
        k -= i;
        while ((c = *(line + k)) != ':')
        {
            *(symbol + j) = c;
            j++;
            k++;
        }
        *(symbol + j) = '\0';
        *lineIndex = k + 1;
    }
    else
    {
        exit(0);
    }
    return symbol;
}

int isSymbolValid(char *symbol, int lineNumber)
{
    if (strlen(symbol) > MAX_SYMBOL_LENGTH)
    {
        printf("\n line number: %d :Error: symbol name must be less than 31 characters.", lineNumber);
        free(symbol);
        return 0;
    }
    if (!isalpha(*symbol))
    {
        printf("\nline number: %d Error: symbol name must start with an alphabetic letter.", lineNumber);
        free(symbol);
        return 0;
    }
    if (!strcmp(symbol, "data") || !strcmp(symbol, "string") || !strcmp(symbol, "entry") || !strcmp(symbol, "extern"))
    {
        printf("line number: %d Error: %s is a saved word in assembly", lineNumber, symbol);
        free(symbol);
        return 0;
    }
    if (isdigit(*symbol))
    {
        printf("\nline number: %d Error: symbol name can`t begin with a digit.", lineNumber);
        free(symbol);
        return 0;
    }
    if (searchOpperation(symbol) != NULL)
    {
        printf("\nline number: %d Error: symbol name can`t be assembly operation name.", lineNumber);
        free(symbol);
        return 0;
    }
    if (searchSymbol(symbol) != NULL)
    {
        printf("line number: %d Error: symbol name already defined.", lineNumber);
        free(symbol);
        return 0;
    }

    if (searchRegisterName(symbol))
    {
        printf("line number: %d Error: symbol name can`t be saved register name", lineNumber);
        free(symbol);
        return 0;
    }
    return 1;
}

/*
This function checks if there is .data / .string directive in the curent line.
return: returns 0 if .data, returns 1 if .string.
*/
int checkIfDataDirective(char *line, int *lineIndex)
{
    int i = *lineIndex;
    int c, k = 0;
    char data[7];

    while (isspace(*(line + i)))
    {
        i++;
    }

    if (*(line + i) != '.')
    {

        return -1;
    }

    while ((c = *(line + i)) != ' ' && c != EOF && k < 7)
    {
        data[k] = c;
        i++;
        k++;
    }
    data[k] = '\0';

    if (!strcmp(".data", data))
    {
        *lineIndex = i;
        return 0;
    }

    if (!strcmp(".string", data))
    {
        *lineIndex = i;
        return 1;
    }

    return -1;
}

/*
This function gets the data from a given line and check if data is valid.
if data is valid it saves it to a give pointer.
return: 0 if error otherwise return 1.
*/
/*int checkDataFormat(char *line, int *lineIndex, int *saveNumber, int lineNumber)
{
    int c, i = *lineIndex;
    int k = 0;
    char numberString[NUMBER_LENGTH + 2];
    int number;

    if(*(line +i ) == '\0')
    {
        return 0;
    }

    if(*(line + i + 1) == '\0')
    {
        printf("\nline number: %d Error: .data line defenition can`t end with:\'%c\'\n",lineNumber,*(line + (i - 1)));
        return 0;
    }

    while (isspace(*(line + i)))
    {
        i++;
    }

    if ((c = *(line + i)) != '-' && c != '+' && !isdigit(c))
    {
        printf("line number: %d Error: Iligal start of number", lineNumber);
        return 0;
    }

    numberString[k] = c;
    k++;
    i++;

    while ((c = *(line + i)) != ' ' && c != ',' && c != '\0')
    {
        if (!isdigit(c))
        {
            numberString[k++] = c;
            numberString[k] = '\0';
            printf("line number:%d Error: %s not a ligal number", lineNumber, numberString);
            return 0;
        }

        if (k > (NUMBER_LENGTH + 1))
        {
            numberString[k++] = c;
            numberString[k] = '\0';
            printf("line number: %d Error: Number: %s is to long ", lineNumber, numberString);
            return 0;
        }

        numberString[k++] = c;
        i++;
    }

    numberString[k] = '\0';
    number = atoi(numberString);

    if (number > MAX_NUMBER || number < MIN_NUMBER)
    {
        printf("line number: %d Error: Number %d is to big or to small. max number allowed is: %d, min number allowed is:%d ", lineNumber, number, MAX_NUMBER, MIN_NUMBER);
        return 0;
    }

    if (c == '\0')
    {
        *lineIndex = i;
        *saveNumber = number;
        return 0;
    }

    *lineIndex = i;
    *saveNumber = number;

    return 1;
}*/
/*returns 0 if valid number else returns the char that encounterd*/
int getNumber(char *line,int *number, int *lineIndex)
{
    char numberString[75];
    int k = 0;
    int i = *lineIndex;
    int c;

    while(isdigit(*(line + i)))
    {
        numberString[k] = *(line + i);
        i++;
        k++;
    }

    numberString[k] = '\0';
    c = *(line + i);

    if(c != ',' && c != ' ')
    {
        return c;
    }

    *number = atoi(numberString);
    *lineIndex = i;
    return -1;
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../tables/tables.h"
#include "../tables/symbolTable/symbolTable.h"
#include "../hellper/hellper.h"
#include "../machineCode/machineCode.h"

#define MAX_NUMBER 2047
#define MIN_NUMBER -2047
#define NUMBER_LENGTH 4
#define MAX_SYMBOL_LENGTH 31
#define MAX_STRING_LENGTH 70

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

/*returns 0 if valid number else returns the char that encounterd*/
int getNumber(char *line, int *number, int *lineIndex)
{
    char numberString[75];
    int k = 0;
    int i = *lineIndex;
    int c, sign = 1;

    if (*(line + i) == '-')
    {
        sign = -1;
        i++;
    }
    else if (*(line + i) == '+')
    {
        i++;
    }

    while (isdigit(*(line + i)))
    {
        numberString[k] = *(line + i);
        i++;
        k++;
    }

    numberString[k] = '\0';
    c = *(line + i);

    if (c != ',' && c != ' ')
    {
        return c;
    }

    *number = sign * atoi(numberString);
    *lineIndex = i;
    return -1;
}

int readAndSaveDataDirective_Data(char *line, int *lineIndex)
{
    int getNumberStatus = 0;
    int number;
    /*check if there is at least on space betwen .data and a number*/
    if (*(line + *lineIndex) != ' ')
    {
        printf("line number %d Erorr: there must be at least one space between .data and the data itself", 1);
        return 0;
    }

    /*skip all the white space between .data and the first argument*/
    while (isspace(*(line + *lineIndex)))
    {
        *lineIndex += 1;
    }

    do
    {
        getNumberStatus = getNumber(line, &number, lineIndex);
        if (getNumberStatus > -1)
        {
            /*hnadle error*/
            printf("\nline number:%d Erorr: %c is not a valid number\n", 1, getNumberStatus);
            return 0;
        }
        if (number > -2047 && number < 2047)
        {
            addData(number);
            printf("\nnumber read: %d", number);
        }
        else
        {
            printf("\nnumber line %d Error: number %d is to big\n", 1, number);
            return 0;
        }

    } while (checkIfSemicolon(line, lineIndex, 1) != -1);

    return 1;
}

int readAndSaveString(char *line, int *lineIndex, int lineNmber)
{
    int i = *lineIndex;
    Data *test;
    int c, k;

    if ((c = *(line + i)) != '"')
    {
        printf("line Number: %d Erorr: strign argument must start with \" ", lineNmber);
        return 0;
    }

    i++;

    while ((c = *(line + i)) != '"')
    {
        if (c == '\0')
        {
            printf("line number: %d Erorr: string argument must end with \" ", lineNmber);
            return 0;
        }

        test = addData(c);
        /*T E S T DELETE THIS*/

       /* for ( k = 0; k < 12; k++)
        {
            printf(" %d ", *(test->data+k));
        }
    putchar('\n');*/

    /*UNTIL HERE*/
        i++;
    }

    addData(0);
    *lineIndex = ++i;
    return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../tables/tables.h"
#include "../tables/symbolTable/symbolTable.h"

#define MAX_SYMBOL_LENGTH 31

/*
check if first input in the given lne is a symbol decleration.
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